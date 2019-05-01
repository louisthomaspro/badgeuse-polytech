/*
 * timer.c
 *
 *  Created on: 10 déc. 2018
 *      Author: corentin
 */
#include "timer.h"

volatile uint32_t *DWT_CYCCNT = (uint32_t *)0xE0001004;
volatile uint32_t *DWT_CONTROL = (uint32_t *)0xE0001000;
volatile uint32_t *SBC_DEMCR = (uint32_t *)0xE000EDFC;

void init_CYC_Timer()
{
	*SBC_DEMCR = *SBC_DEMCR|0x01000000;
	*DWT_CONTROL = *DWT_CONTROL|1;
}
void mark_CYC_Timer(uint32_t *ref)
{
	*ref=*DWT_CYCCNT;
}
uint32_t elapsed_CYC_Timer(uint32_t ref)
{
	uint32_t time_cyc = *DWT_CYCCNT;
	if(time_cyc >= ref)
		return (time_cyc - ref);
	else
		return 4294967295;
}

void delay_CYC(uint32_t cyc)
{
	uint32_t ref=*DWT_CYCCNT;
	while((*DWT_CYCCNT >= ref && *DWT_CYCCNT-ref < cyc ) || (*DWT_CYCCNT < ref && 4294967295-ref+*DWT_CYCCNT < cyc));
}
