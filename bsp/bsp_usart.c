#include "bsp_usart.h"
#include "main.h"

#include "cmsis_os.h"

#include "encoder.h"

extern UART_HandleTypeDef huart1;

int8_t temperature;
bool_t temperature_ok;

void bmi088_ist8310_init(void) {
    HAL_UART_Transmit(&huart1, (uint8_t*)"\x05", 1, 100);
}

void send_bmi088_ist8310(fp32 INS_gyro[3], fp32 INS_accel[3], fp32 INS_mag[3], fp32 INS_quat[4], fp32 INS_angle[3]) {
    HAL_UART_Transmit(&huart1, (uint8_t*)"\x05", 1, 100);
    uint8_t datas[BMI088_IST8310_LENGTH];
    data_t data;
    data.value = datas;
    data.length = BMI088_IST8310_LENGTH;
    set_fp32(&data, INS_gyro, 3);
    set_fp32(&data, INS_accel, 3);
    set_fp32(&data, INS_mag, 3);
    set_fp32(&data, INS_quat, 4);
    set_fp32(&data, INS_angle, 3);
    HAL_UART_Transmit(&huart1, datas, BMI088_IST8310_LENGTH, 100);
}

void INS_cali_gyro_ok(void) {
    HAL_UART_Transmit(&huart1, (uint8_t*)"\x09", 1, 100);
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

void send_hook(uint8_t hook_code) {
    uint8_t data[2] = {0xFF, hook_code};
    HAL_UART_Transmit(&huart1, data, 2, 500);
}

void set_temperature(int8_t *temp) {
    temperature = *temp;
    temperature_ok = 1;
}
