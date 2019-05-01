#include "beeper.h"

int frequency=0;
uint32_t time_ref=0;
int duration=0;
bool playing=false;

void beep(int freq, int ms_duration)
{
	duration=ms_duration;
	__HAL_TIM_SET_AUTORELOAD(&htim2, (2*100000)/freq);
	mark_CYC_Timer(&time_ref);
	playing=true;
}

void beepProcess()
{
	if(playing && CYC_TO_US(elapsed_CYC_Timer(time_ref))>=(duration*1000))
	{
		playing=false;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(playing)
		HAL_GPIO_TogglePin(Beeper_GPIO_Port, Beeper_Pin);
	else
		HAL_GPIO_WritePin(Beeper_GPIO_Port, Beeper_Pin, GPIO_PIN_RESET);
}
