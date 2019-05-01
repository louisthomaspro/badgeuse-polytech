/*
 * scan_fifo.h
 *
 *  Created on: 10 avr. 2019
 *      Author: corentin
 */

#ifndef SCAN_FIFO_H_
#define SCAN_FIFO_H_
#include "card_reader.h"

#define BKPSRAM_END (BKPSRAM_BASE+0xFFF)

#define FIFO_INITFLAG 0xA5A5A5A5
#define FIFO_LOCATION BKPSRAM_BASE
#define FIFO_BUFFER_SIZE (BKPSRAM_END-(BKPSRAM_BASE+10))

typedef struct
{
	uint8_t card_uid[ISO_14443_4_UID_SIZE];
	uint32_t timestamp; // [26:20]YY [19:16]MM [15:11]DD [10:6]HH [5:0]mm
}Scan;

typedef struct
{
	uint16_t nbr;
	uint16_t get_index;
	uint16_t put_index;
}FifoScanHeader;

typedef struct
{
	uint32_t initFlag;
	FifoScanHeader header;
	Scan buffer[FIFO_BUFFER_SIZE/sizeof(Scan)];
}FifoScan;

void fifoScanInit();
uint8_t fifoScanPut(const Scan *scan);
uint8_t fifoScanGet(Scan *scan);
uint8_t fifoScanFirst(Scan *scan);
uint16_t fifoScanNbr();

#endif /* SCAN_FIFO_H_ */
