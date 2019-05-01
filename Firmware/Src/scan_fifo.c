/*
 * scan_fifo.c
 *
 *  Created on: 10 avr. 2019
 *      Author: corentin
 */

#include "scan_fifo.h"


volatile FifoScan *fifoScan = (volatile uint32_t *)FIFO_LOCATION;


void fifoScanInit()
{
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();
	__BKPSRAM_CLK_ENABLE();
	HAL_PWREx_EnableBkUpReg();

	if(fifoScan->initFlag != 0xA5A5A5A5)
	{
		fifoScan->initFlag = 0xA5A5A5A5;
		fifoScan->header.nbr=0;
		fifoScan->header.get_index=0;
		fifoScan->header.put_index=0;

	}
		//__asm__ __volatile__ ("bkpt #0");
}
uint8_t fifoScanPut(const Scan *scan)
{
	if(fifoScan->header.nbr >= FIFO_BUFFER_SIZE*sizeof(Scan) || scan==NULL)
		return 1;
	fifoScan->buffer[fifoScan->header.put_index]= *scan;
	fifoScan->header.put_index++;
	if(fifoScan->header.put_index >= FIFO_BUFFER_SIZE*sizeof(Scan))
		fifoScan->header.put_index = 0;
	fifoScan->header.nbr++;
	return 0;

}
uint8_t fifoScanGet(Scan *scan)
{
	if(fifoScan->header.nbr == 0)
		return 1;
	if(scan != NULL)
		*scan = fifoScan->buffer[fifoScan->header.get_index];
	fifoScan->header.get_index++;
	if(fifoScan->header.get_index >= FIFO_BUFFER_SIZE*sizeof(Scan))
			fifoScan->header.get_index = 0;
	fifoScan->header.nbr--;
	return 0;
}
uint8_t fifoScanFirst(Scan *scan)
{
	if(fifoScan->header.nbr == 0 || scan==NULL)
		return 1;
	*scan = fifoScan->buffer[fifoScan->header.get_index];
	return 0;
}
uint16_t fifoScanNbr()
{
	return fifoScan->header.nbr;
}
