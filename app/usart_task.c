#include "usart_task.h"
#include "cmsis_os.h"
#include "main.h"
#include "INS_task.h"

#include "bsp_led.h"
#include "bsp_laser.h"
#include "bsp_usart.h"

#include "decoder.h"

extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;

uint8_t val;
uint8_t cali_gyro_val[26];
uint8_t set_gyro_val[24];
usart_mode_t mode;

void usart_task(void const * argument) {
    mode = NORMAL;
    HAL_UART_Receive_IT(&huart1, &val, 1);

    while (1)
    {
        osDelay(500);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(huart);
    /* NOTE: This function Should not be modified, when the callback is needed,
             the HAL_UART_TxCpltCallback could be implemented in the user file
     */
    led_off();

    if (mode == NORMAL)
    {
        switch (val)
        {
        case 0x01: laser_on();                                            break;
        case 0x02: laser_off();                                           break;
        case 0x03: __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, PWM_ON);   break;
        case 0x04: __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, PWM_OFF);  break;
        case 0x06: INS_callback();                                        break;
        case 0x08: mode = CALI_GYRO;                                      break;
        case 0x0A: mode = SET_GYRO;                                       break;
        case 0x0D: mode = GET_TEMP;                                       break;
        }
    }
    else if (mode == CALI_GYRO)
    {
        

        
        mode = NORMAL;
    }
    else if (mode == SET_GYRO)
    {
        fp32 cali_scale[3], cali_offset[3];
        data_t data;
        data.value = set_gyro_val;
        data.length = 24;
        get_fp32(&data, cali_scale, 3);
        get_fp32(&data, cali_offset, 3);
        INS_set_cali_gyro(cali_scale, cali_offset);
        INS_set_cali_gyro_ok();
        mode = NORMAL;
    }
    else if (mode == GET_TEMP)
    {
        set_temperature(&val);
        mode = NORMAL;
    }

    switch (mode)
    {
    case NORMAL:
        HAL_UART_Receive_IT(&huart1, &val, 1);
        break;
    case CALI_GYRO:
        HAL_UART_Receive_IT(&huart1, &cali_gyro_val, 26);
        break;
    case SET_GYRO:
        HAL_UART_Receive_IT(&huart1, &set_gyro_val, 24);
        break;
    case GET_TEMP:
        HAL_UART_Receive_IT(&huart1, &val, 1);
        break;
    }    
    

}
