/*
 * timer.h
 *
 *  Created on: 10 déc. 2018
 *      Author: corentin
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <unistd.h>

#define CYC_FREQ 120 //Mhz

#define CYC_TO_US(__CYC__) ((__CYC__)/CYC_FREQ)
#define US_TO_CYC(__US__) ((__US__)*CYC_FREQ)

void init_CYC_Timer();
void mark_CYC_Timer(uint32_t *ref);
uint32_t elapsed_CYC_Timer(uint32_t ref);
void delay_CYC(uint32_t cyc);

#endif /* TIMER_H_ */
