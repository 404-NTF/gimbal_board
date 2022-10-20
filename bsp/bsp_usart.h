#ifndef BSP_USART_H
#define BSP_USART_H
#include "struct_typedef.h"
/**
 * usart数据定义
 * 0x01 <- laser_on
 * 0x02 <- laser_off
 * 0x03 <- pwm_on
 * 0x04 <- pwm_off
 * 0x05 <- bmi088_ist8310_init
 * 0x06 -> bmi088_ist8310_init_ok
 * 0x07 <- bmi088_ist8310_read
 * 0x08 -> bmi088_ist8310_read_result 64字节
 * 0x09 <- INS_cali_gyro 26字节
 * 0x0A <- INS_set_cali_gyro 24字节
 */

#define CALI_GYRO_LENGTH 26
#define SET_GYRO_LENGTH 24
#define BMI088_IST8310_LENGTH 65


extern void bmi088_ist8310_init_ok(void);
extern void send_bmi088_ist8310(fp32 INS_gyro[3], fp32 INS_accel[3], fp32 INS_mag[3], fp32 INS_quat[4], fp32 INS_angle[3]);


#endif
