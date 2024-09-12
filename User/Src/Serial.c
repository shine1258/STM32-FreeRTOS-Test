#include "Serial.h"
#include "cmsis_os.h"
#include "usart.h"
#include <stdio.h>

osSemaphoreId_t semaphore;

void Serial_Init(void)
{
    semaphore = osSemaphoreNew(1, 0, NULL);
}

void Serial_WriteBytes(uint8_t* bytes, uint16_t length)
{
    HAL_UART_Transmit(&huart1, bytes, length, 1000);
}

void Serial_ReadBytes(uint8_t* bytes, uint16_t length, uint32_t timeout)
{
    osMessageQueueReset(semaphore);
    HAL_UART_Receive_IT(&huart1, bytes, length);
    osStatus_t result = osSemaphoreAcquire(semaphore, timeout);

    if (result == osOK) {
        printf("Serial_ReadBytes: %s\r\n", bytes);
    } else {
        printf("%d\r\n", result);
        printf("Serial_ReadBytes timeout\r\n");
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    if (huart == &huart1) {
        osSemaphoreRelease(semaphore);
    }
}

#ifdef __GNUC__

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE* f)

#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 0xFFFF);
    return ch;
}