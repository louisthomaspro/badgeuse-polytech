/*
 * card_reader.c
 *
 *  Created on: 24 janv. 2019
 *      Author: corentin
 */
#include "card_reader.h"

uint8_t getCardUid(uint8_t *card_uid, uint8_t *size)
{
	uint8_t piccType;
	if(PICC_IsNewCardPresent())
	{
		if(PICC_ReadCardSerial())
		{
			piccType=PICC_GetType(uid.sak);
			if (piccType == PICC_ISO_14443_4_TYPE)
			{
				printf("PICC Detected !!\r\n");
				printf("uid : ");
				for(uint8_t i=0; i<uid.size;i++)
				{
					card_uid[i] = uid.uidByte[i];
					printf("%02X", uid.uidByte[i]);
				}
				*size=uid.size;
				printf("\r\n");
				PICC_HaltA();
				return 1;
			}
		}
	}
	return 0;
}


/*void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == PCD_IRQ_Pin)
	{
		printf("a\r\n");
		PCD_WriteRegister(COM_IRQ_REG, 0x80);
	}
}*/

