#ifndef USART_TASK_H
#define USART_TASK_H

#define PWM_ON 890
#define PWM_OFF 1730

typedef enum {
    NORMAL = 0,
    CALI_GYRO,
    SET_GYRO,
    INS_INIT,
} usart_mode_t;

extern void usart_init(void);

#endif
