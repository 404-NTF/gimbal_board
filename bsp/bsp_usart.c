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
    data_t data;
    data.length = BMI088_IST8310_LENGTH;
    set_fp32(&data, INS_gyro, 3);
    set_fp32(&data, INS_accel, 3);
    set_fp32(&data, INS_mag, 3);
    set_fp32(&data, INS_quat, 4);
    set_fp32(&data, INS_angle, 3);
    HAL_UART_Transmit(&huart1, data.value, BMI088_IST8310_LENGTH, 100);
}

void send_INS_cali(fp32 cali_scale[3], fp32 cali_offset[3], uint16_t time_count) {
    data_t data;
    data.length = CALI_GYRO_LENGTH;
    set_fp32(&data, cali_scale, 3);
    set_fp32(&data, cali_offset, 3);
    set_uint16_t(&data, &time_count, 1);
    HAL_UART_Transmit(&huart1, data.value, CALI_GYRO_LENGTH, 100);
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
    temperature = *temp;
    temperature_ok = 1;
}
