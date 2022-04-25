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
 * 0x07 -> bmi088_ist8310_read_result + [result bits]
 * 0x08 <- INS_cali_gyro + [cali_scale[3] cali_offset[3] time_count]
 * 0x09 -> INS_cali_gyro_result + [result bits]
 * 0x0A <- INS_set_cali_gyro + [cali_scale[3] cali_offset[3]]
 * 0x0B -> INS_set_cali_gyro_ok
 * 0xFF+X -> 错误码
 */

extern void bmi088_ist8310_init(void);

#endif
