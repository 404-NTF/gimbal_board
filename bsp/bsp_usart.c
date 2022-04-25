#include "bsp_usart.h"
#include "main.h"

extern UART_HandleTypeDef huart1;

void bmi088_ist8310_init(void) {
    HAL_UART_Transmit(&huart1, (uint8_t*)"\x05", 1, 100);
}
