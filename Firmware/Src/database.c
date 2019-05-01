/*
 * database.c
 *
 *  Created on: 12 avr. 2019
 *      Author: corentin
 */
#include "database.h"

enum DatabaseConnectionState DBState = INIT;
enum DatabaseQueryState QueryState = ADDSCAN;

sqlc_descriptor Sqlc_d;
const char hostname[] = "192.168.1.5";
const char username[] = "root";
const char password[] = "root";

#define CONNECTION_TIMEOUT 40
#define DHCP_TIMEOUT 20

uint8_t connection_timeout_counter = 0;
uint8_t dhcp_timeout_counter = 0;

void DB_AddScan(Scan *sc)
{
	u16_t ret;
	char badgeUidStr[15]="";
	char query[200]="";
	for(uint8_t i=0; i<sizeof(sc->card_uid); i++)
		sprintf(badgeUidStr, "%s%02X", badgeUidStr, sc->card_uid[i]);

	sprintf(query, SQL_ADD_SCAN_QUERY, (uint8_t)((sc->timestamp >> 20) & 0x7F), (uint8_t)((sc->timestamp >> 16) & 0x0F), (uint8_t)((sc->timestamp >> 11) & 0x1F), (uint8_t)((sc->timestamp >> 6) & 0x1F), (uint8_t)((sc->timestamp) & 0x3F), badgeUidStr, CARD_READER_UUID);
	printf("%s\r\n", query);
	ret = sqlc_execute(&Sqlc_d,query);
	if(!ret){
		LWIP_DEBUGF(LWIP_DBG_ON, ("Inserting...\n\r"));
	}

}
/*void DB_Select_Return()
{
	u16_t ret;
	ret = sqlc_execute(&Sqlc_d,SQL_SELECT_RETURN_QUERY);
	if(!ret){
		QueryState = READ_RETURN;
		LWIP_DEBUGF(LWIP_DBG_ON, ("Select return...\n\r"));
	}
}*/
void DB_Query_Process()
{
	Scan sc;
	switch(QueryState) {
	case ADDSCAN:
		fifoScanFirst(&sc);
		DB_AddScan(&sc);
		break;/*
	case SELECT_RETURN:
		DB_Select_Return();
		break;*/
	}
}
void DB_Response_Process()
{
	//column_names* columns = NULL;
	//row_values* row;
	switch(QueryState)
	{
	case ADDSCAN:
		fifoScanGet(NULL);
		//QueryState = SELECT_RETURN;
		if(fifoScanNbr() > 0)
			DBState = CONNECTED;
		else
			DBState = DISCONNECT;
		break;
	/*case SELECT_RETURN:
		QueryState = READ_RETURN;
		break;
	case READ_RETURN:
		columns = mysqlc_get_columns(&Sqlc_d);
		if(columns){
			row = mysqlc_get_next_row(&Sqlc_d);
			if (row != NULL) {
				long value;
				LWIP_DEBUGF(LWIP_DBG_ON, ("number of fields is  %d\r\n",columns->num_fields));
				for ( int i = 0 ; i < columns->num_fields ; i++){
					LWIP_DEBUGF(LWIP_DBG_ON, ("%s, ",row->values[i]));
					//d[i-1] = atol(row->values[i]);
				}
			}

			//*****
			if(fifoScanNbr() > 0)
				DBState = CONNECTED;
			else
				DBState = DISCONNECT;
			break;
		}*/

	}
}
void DB_Process()
{
	static uint32_t time_ref_connected=0;
	static uint32_t time_ref_disconnected=0;
	enum state sqlc_state;
	u16_t ret;
	char connected;
	switch(DBState)
	{
	case INIT:
		LWIP_DEBUGF(LWIP_DBG_ON, ("DB : INIT\n\r"));
		ret = sqlc_create(&Sqlc_d);
		if(!ret){
			mark_CYC_Timer(&time_ref_disconnected);
			DBState = DISCONNECTED;
		}
		else
		{
			printf("Init Error\r\n");
		}
		break;
	case CONNECT:
		LWIP_DEBUGF(LWIP_DBG_ON, ("DB : CONNECT\n\r"));
		ret = sqlc_connect(&Sqlc_d,hostname,3306,username,password);
		if(!ret)
		{
			DBState = CONNECTING;
			connection_timeout_counter=0;
			mark_CYC_Timer(&time_ref_connected);
		}
		else{
			sqlc_delete(&Sqlc_d);
			DBState = INIT;
		}
		break;
	case CONNECTING:
		if(CYC_TO_US(elapsed_CYC_Timer(time_ref_connected))>=100000)
		{
			LWIP_DEBUGF(LWIP_DBG_ON, ("DB : CONNECTING\n\r"));
			ret = sqlc_is_connected(&Sqlc_d, &connected);
			if(ret)
				DBState = INIT;// No connector then recreate it
			else if(!connected){
				enum state state;
				ret = sqlc_get_state(&Sqlc_d,&state);
				if(ret)
					DBState = INIT;// No connector then recreate it
				else if(state != CONNECTOR_STATE_CONNECTING){
					LWIP_DEBUGF(LWIP_DBG_ON, ("DB : Not Connected\n\r"));
					DBState = CONNECT;
				}

				if(connection_timeout_counter >= CONNECTION_TIMEOUT)
				{
					sqlc_abort(&Sqlc_d);
					DBState = CONNECT;
				}
				else
					connection_timeout_counter++;
			}else{
				connection_timeout_counter=0;
				DBState = CONNECTED;
			}
			mark_CYC_Timer(&time_ref_connected);
		}
		break;
	case CONNECTED:
		LWIP_DEBUGF(LWIP_DBG_ON, ("DB : CONNECTED\n\r"));
		ret = sqlc_is_connected(&Sqlc_d,&connected);
		if(ret)
			DBState = INIT;
		else if(!connected){
			LWIP_DEBUGF(LWIP_DBG_ON, ("insert_periodic_handler():Not Connected\n\r"));
			DBState = CONNECT;
		}else{
			ret = sqlc_get_state(&Sqlc_d,&sqlc_state);
			if(!ret){
				if(sqlc_state == CONNECTOR_STATE_IDLE)
				{
					DB_Query_Process();
					DBState = WAITING_FOR_RESPONSE;

				}
				else if(sqlc_state == CONNECTOR_STATE_CONNECTOR_ERROR)
				{
					enum error_state es;
					ret = sqlc_get_error_state(&Sqlc_d,&es);
					printf("Error while connected : %d\n", es);
					sqlc_abort(&Sqlc_d);
					DBState = CONNECT;
				}

			}else{
				DBState = INIT;
			}
		}
		break;
	case WAITING_FOR_RESPONSE:
		ret = sqlc_get_state(&Sqlc_d,&sqlc_state);
		if(!ret){
			if(sqlc_state == CONNECTOR_STATE_IDLE)
			{
				DB_Response_Process();
			}
			else if(sqlc_state == CONNECTOR_STATE_CONNECTOR_ERROR)
			{
				enum error_state es;
				ret = sqlc_get_error_state(&Sqlc_d,&es);
				printf("Error while sending: %d\n", es);
				sqlc_abort(&Sqlc_d);
				DBState =  CONNECT;
			}
		}
		break;
	case DISCONNECT:
		LWIP_DEBUGF(LWIP_DBG_ON, ("DB : DISCONNECT\n\r"));
		ret = sqlc_disconnect(&Sqlc_d);
		if(!ret)
		{
			mark_CYC_Timer(&time_ref_disconnected);
			DBState = DISCONNECTED;
		}
		break;
	case DISCONNECTED:
		QueryState = ADDSCAN;
		if(CYC_TO_US(elapsed_CYC_Timer(time_ref_disconnected))>=1000000)
		{
			if(fifoScanNbr() > 0)
			{
				if(dhcp_supplied_address(&gnetif))
				{
					dhcp_timeout_counter=0;
					DBState = CONNECT;
				}
				if(dhcp_timeout_counter >= DHCP_TIMEOUT)
				{
					//netif_set_up(&gnetif);
					//dhcp_start(&gnetif);
					HAL_NVIC_SystemReset();
					dhcp_timeout_counter=0;
				}
				else
					dhcp_timeout_counter++;
			}
			mark_CYC_Timer(&time_ref_disconnected);
		}
		break;
	}
}



