/*
 * beeper.h
 *
 *  Created on: 30 avr. 2019
 *      Author: corentin
 */

#ifndef BEEPER_H_
#define BEEPER_H_
#include "stm32f2xx_hal.h"
#include "timer.h"
#include "tim.h"
#include <stdbool.h>

void beep(int freq, int ms_duration);
void beepProcess();
#endif /* BEEPER_H_ */
