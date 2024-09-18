#include "Serial.h"
#include "Common.h"
#include "cmsis_os.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

namespace IO {

constexpr uint8_t READ_ONCE_COUNT = 1;
constexpr uint16_t READ_BUFFER_SIZE = 256;

static osMessageQueueId_t readBuffer;
static uint8_t aRead;
static bool isReading = false;

Serial::Serial(void)
{
    readBuffer = osMessageQueueNew(READ_BUFFER_SIZE, sizeof(uint8_t), NULL);
    MALLOC_FAILED_CHECK(readBuffer);
    HAL_UART_Receive_IT(&huart1, &aRead, READ_ONCE_COUNT);
}

Serial::~Serial(void)
{
    osMessageQueueDelete(readBuffer);
    HAL_UART_Abort_IT(&huart1);
}

void Serial::writeBytes(uint8_t* bytes, uint16_t length)
{
    HAL_UART_Transmit(&huart1, bytes, length, 0xFFFF);
}

SerialResult Serial::readBytes(uint8_t* bytes, uint16_t length, uint32_t timeout)
{
    if (isReading)
        return SerialResult::ERROR;

    if (length == 0)
        return SerialResult::ERROR;

    isReading = true;

    osStatus_t status = osStatus_t::osOK;
    uint32_t remainTimeout = timeout;
    uint32_t startTime = osKernelGetTickCount();
    uint16_t readedLength = 0;

    while (readedLength < length && status == osStatus_t::osOK) {
        status = osMessageQueueGet(readBuffer, bytes + readedLength, NULL, remainTimeout);
        readedLength++;
        remainTimeout = timeout - (GetExecutionTickCount(startTime));
    }

    isReading = false;

    if (status == osStatus_t::osOK)
        return SerialResult::OK;
    else
        return SerialResult::TIMEOUT;
}

void Serial::clearReadBuffer(void)
{
    osMessageQueueReset(readBuffer);
}

#ifdef __cplusplus
extern "C" {
#endif

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    if (huart == &huart1) {
        if (osMessageQueueGetCount(readBuffer) == READ_BUFFER_SIZE) {
            uint8_t temp;
            osMessageQueueGet(readBuffer, &temp, NULL, 0);
        }

        osMessageQueuePut(readBuffer, &aRead, 0, 0);
        HAL_UART_Receive_IT(&huart1, &aRead, READ_ONCE_COUNT);
    }

#ifdef __cplusplus
}
#endif

} // namespace IO

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GNUC__

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE* f)

#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
    Serial::instance().writeBytes((uint8_t*)&ch, 1);
    return ch;
}

#ifdef __cplusplus
}
#endif

}