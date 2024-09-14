#include "Serial.h"
#include "Common.h"
#include "cmsis_os.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

#define READ_ONCE_COUNT 1
#define READ_BUFFER_SIZE 256

static osThreadId_t thread;
static osMessageQueueId_t readBuffer;
static uint8_t aRead;

static uint8_t* bytesToRead;
static uint16_t lengthToRead;
static uint16_t readedLength;

void Serial_Init(void)
{
    readBuffer = osMessageQueueNew(READ_BUFFER_SIZE, sizeof(uint8_t), NULL);
    MALLOC_FAILED_CHECK(readBuffer);
    HAL_UART_Receive_IT(&huart1, &aRead, READ_ONCE_COUNT);
}

void Serial_WriteBytes(uint8_t* bytes, uint16_t length)
{
    HAL_UART_Transmit(&huart1, bytes, length, 0xFFFF);
}

SerialStatus_t Serial_ReadBytes(uint8_t* bytes, uint16_t length, uint32_t timeout)
{
    if (thread)
        return SERIAL_ERROR;

    thread = osThreadGetId();
    bytesToRead = bytes;
    lengthToRead = length;

    uint32_t flags = osThreadFlagsWait(BIT_0, osFlagsWaitAny, timeout);

    thread = NULL;
    bytesToRead = NULL;
    lengthToRead = 0;
    readedLength = 0;

    if (flags != (uint32_t)osFlagsErrorTimeout)
        return SERIAL_OK;
    else
        return SERIAL_TIMEOUT;
}

void Serial_ClearReadBuffer(void)
{
    osMessageQueueReset(readBuffer);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    if (huart == &huart1) {
        if (osMessageQueueGetCount(readBuffer) == READ_BUFFER_SIZE) {
            uint8_t temp;
            osMessageQueueGet(readBuffer, &temp, NULL, 0);
        }

        osMessageQueuePut(readBuffer, &aRead, 0, 0);

        if (thread) {
            while (osMessageQueueGetCount(readBuffer) > 0 && (readedLength < lengthToRead)) {
                osMessageQueueGet(readBuffer, bytesToRead + readedLength, NULL, 0);
                readedLength++;

                if (readedLength == lengthToRead) {
                    osThreadFlagsSet(thread, BIT_0);
                }
            }
        }

        HAL_UART_Receive_IT(&huart1, &aRead, READ_ONCE_COUNT);
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