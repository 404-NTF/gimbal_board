#ifndef BSP_USART_H
#define BSP_USART_H
#include "struct_typedef.h"
/**
 * usart数据定义
 * 0x01 <- laser_on
 * 0x02 <- laser_off
 * 0x03 <- pwm_on
 * 0x04 <- pwm_off
 * 0x05 -> bmi088_ist8310_init
 * 0x06 <- bmi088_ist8310_read
 * 0x07 -> bmi088_ist8310_read_result + [result bits] *
 * 0x08 <- INS_cali_gyro + [cali_scale[3] cali_offset[3] time_count]
 * 0x09 -> INS_cali_gyro_ok
 * 0x0A <- INS_set_cali_gyro + [cali_scale[3] cali_offset[3]]
 * 0x0B -> INS_set_cali_gyro_ok
 * 0x0C -> get_control_temperature
 * 0x0D <- setTemperature + [result bits]
 * 0xFF+X -> 钩子 send_hook
 */

#define CALI_GYRO_LENGTH 26
#define SET_GYRO_LENGTH 24
#define BMI088_IST8310_LENGTH 64


extern void bmi088_ist8310_init(void);
extern void send_bmi088_ist8310(fp32 INS_gyro[3], fp32 INS_accel[3], fp32 INS_mag[3], fp32 INS_quat[4], fp32 INS_angle[3]);
extern void INS_cali_gyro_ok(void);
extern void INS_set_cali_gyro_ok(void);
extern int8_t get_control_temperature(void);

extern void send_hook(uint8_t hook_code);

extern void set_temperature(int8_t *temp);

#endif
