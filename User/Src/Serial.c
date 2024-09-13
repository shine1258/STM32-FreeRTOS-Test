#include "Serial.h"
#include "cmsis_os.h"
#include "usart.h"
#include <stdio.h>

osSemaphoreId_t semaphore;
uint8_t byteBuffer;
uint8_t* bytesToRead;
uint16_t lengthToRead;
uint16_t readedLength = 0;

void Serial_Init(void)
{
    semaphore = osSemaphoreNew(1, 0, NULL);
    HAL_UART_Receive_IT(&huart1, &byteBuffer, 1);
}

void Serial_WriteBytes(uint8_t* bytes, uint16_t length)
{
    HAL_UART_Transmit(&huart1, bytes, length, 0xFFFF);
}

SerialStatus_t Serial_ReadBytes(uint8_t* bytes, uint16_t length, uint32_t timeout)
{
    if (bytesToRead)
        return SERIAL_ERROR;

    bytesToRead = bytes;
    lengthToRead = length;

    osStatus_t status = osSemaphoreAcquire(semaphore, timeout);
    bytesToRead = NULL;

    if (status == osOK)
        return SERIAL_OK;
    else
        return SERIAL_TIMEOUT;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    if (huart == &huart1) {
        if (bytesToRead) {
            if (readedLength < lengthToRead) {
                bytesToRead[readedLength++] = byteBuffer;
            } else if (readedLength == lengthToRead) {
                readedLength = 0;
                osSemaphoreRelease(semaphore);
            }
        }

        HAL_UART_Receive_IT(&huart1, &byteBuffer, 1);
    }
}

#ifdef __GNUC__

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE* f)

#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
    Serial_WriteBytes((uint8_t*)&ch, 1);
    return ch;
}