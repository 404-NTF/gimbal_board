#include "usart_task.h"
#include "cmsis_os.h"

void usart_task(void const * argument) {
    while (1)
    {
        osDelay(500);
    }
}
