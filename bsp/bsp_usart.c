#include "bsp_usart.h"
#include "main.h"

extern UART_HandleTypeDef huart1;

int8_t temperature;
bool_t temperature_ok;

void bmi088_ist8310_init(void) {
    HAL_UART_Transmit(&huart1, (uint8_t*)"\x05", 1, 100);
}

void send_bmi088_ist8310(void) {

}

void send_INS_cali(void) {

}

void INS_set_cali_gyro_ok(void) {
    HAL_UART_Transmit(&huart1, (uint8_t*)"\x0B", 1, 100);
}

int8_t get_control_temperature(void) {
    temperature_ok = 0;
    HAL_UART_Transmit(&huart1, (uint8_t*)"\x0C", 1, 100);
    while (temperature_ok == 0) {
        osDelay(100);
    }
    return temperature;
}

void send_error(uint8_t error_code) {
    uint8_t data[2] = {0xFF, error_code};
    HAL_UART_Transmit(&huart1, data, 2, 500);
}

void set_temperature(int8_t *temp) {
    temperature = temp;
    temperature_ok = 1;
}