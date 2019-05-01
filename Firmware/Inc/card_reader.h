/*
 * card_reader.h
 *
 *  Created on: 24 janv. 2019
 *      Author: corentin
 */

#ifndef CARD_READER_H_
#define CARD_READER_H_

#include "stm32f2xx_hal.h"
#include "MFRC522.h"

#define CARD_READER_UUID "D25460585B8311E99E1A04E05A1F8E6D"

uint8_t getCardUid(uint8_t *uid, uint8_t *size);



#endif /* CARD_READER_H_ */
