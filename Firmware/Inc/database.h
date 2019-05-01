/*
 * database.h
 *
 *  Created on: 12 avr. 2019
 *      Author: corentin
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "lwip.h"
#include "sql_connector.h"
#include "card_reader.h"
#include "scan_fifo.h"
#include "timer.h"

#define SQL_ADD_SCAN_QUERY "CALL badgeuse.addScan(STR_TO_DATE('20%02d%02d%02d%02d%02d', '%%Y%%m%%d%%H%%i'), UNHEX('%s'), UNHEX('%s'), @res);"
#define SQL_SELECT_RETURN_QUERY "SELECT @res;"
enum DatabaseConnectionState
{
	INIT,
	CONNECT,
	CONNECTING,
	CONNECTED,
	WAITING_FOR_RESPONSE,
	DISCONNECT,
	DISCONNECTED
};

enum DatabaseQueryState
{
	ADDSCAN,
	//SELECT_RETURN,
	//READ_RETURN
};

void DB_Process();


#endif /* DATABASE_H_ */
