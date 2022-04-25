#include "usart_task.h"
#include "cmsis_os.h"
#include "main.h"
#include "INS_task.h"

fp32 gyro[3], accel[3], temp;

uint8_t Buffers[29];
uint8_t val;

extern UART_HandleTypeDef huart1;

static void UpdateBuffer(uint8_t *buffer, fp32 *data, uint8_t start, uint8_t length);

void usart_task(void const * argument) {
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
    switch (val)
    {
    case 0x01: laser_on();                                            break;
    case 0x02: laser_off();                                           break;
    case 0x03: __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, PWM_ON);   break;
    case 0x04: __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, PWM_OFF);  break;
    case 0x06: INS_callback();                                        break;
    case 0x07:
        // 校准
        break;
    case 0x08:
        // 设置陀螺仪偏移
        break;
    }
  
    HAL_UART_Receive_IT(&huart1, &val, 1);
}


void UpdateBuffer(uint8_t *buffer, fp32 *data, uint8_t start, uint8_t length)
{
  FloatAndCharAry *f;
  uint8_t i;
  for(i = 0; i < length; i++)
  {
    f = (FloatAndCharAry*)&data[i];
    buffer[start * 4 + i * 4] = f->byte[0];
    buffer[start * 4 + i * 4 + 1] = f->byte[1];
    buffer[start * 4 + i * 4 + 2] = f->byte[2];
    buffer[start * 4 + i * 4 + 3] = f->byte[3];
  }
}


