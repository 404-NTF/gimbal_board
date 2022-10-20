#include "bsp_usart.h"
#include "main.h"

#include "cmsis_os.h"

#include "encoder.h"

#include "bsp_led.h"

extern UART_HandleTypeDef huart1;

int8_t temperature;
bool_t temperature_ok;

void bmi088_ist8310_init_ok(void) {
    HAL_UART_Transmit(&huart1, (uint8_t*)"\x06", 1, 100);
}

void send_bmi088_ist8310(fp32 INS_gyro[3], fp32 INS_accel[3], fp32 INS_mag[3], fp32 INS_quat[4], fp32 INS_angle[3]) {
    uint8_t datas[BMI088_IST8310_LENGTH];
    data_t data;
    data.value = datas;
    data.length = BMI088_IST8310_LENGTH;
    data.curser = 0;
    set_uint8_t(&data, (uint8_t*)"\x08", 1);
    set_fp32(&data, INS_gyro, 3);
    set_fp32(&data, INS_accel, 3);
    set_fp32(&data, INS_mag, 3);
    set_fp32(&data, INS_quat, 4);
    set_fp32(&data, INS_angle, 3);
    HAL_UART_Transmit(&huart1, datas, BMI088_IST8310_LENGTH, 100);
}
