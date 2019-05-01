#include "stm32f2xx_hal.h"
#include "usart.h"

int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit(&huart3, (uint8_t*)ptr, len, 0xFFFF);
return len;
}
