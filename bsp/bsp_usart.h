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
 * 0x09 -> send_INS_cali  + [result bits]
 * 0x0A <- INS_set_cali_gyro + [cali_scale[3] cali_offset[3]]
 * 0x0B -> INS_set_cali_gyro_ok
 * 0x0C -> get_control_temperature
 * 0x0D <- setTemperature + [result bits]
 * 0xFF+X -> 错误码 send_error
 */

extern void bmi088_ist8310_init(void);
extern void send_bmi088_ist8310(void);
extern void send_INS_cali(void);
extern void INS_set_cali_gyro_ok(void);
extern int8_t get_control_temperature(void);

extern void send_error(uint8_t error_code);

extern void set_temperature(int8_t *temp);

#endif
