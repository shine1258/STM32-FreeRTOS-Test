#include "Serial.h"
#include "Common.h"
#include "cmsis_os.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

namespace IO {

static constexpr uint8_t readOnceCount = 1;
static constexpr uint16_t readBufferSize = 256;
static osMessageQueueId_t readBuffer;
static uint8_t aRead;
static bool isReading = false;

Serial::Serial(void)
{
    readBuffer = osMessageQueueNew(readBufferSize, sizeof(uint8_t), NULL);
    MALLOC_FAILED_CHECK(readBuffer);
    HAL_UART_Receive_IT(&huart1, &aRead, readOnceCount);
}

Serial::~Serial(void)
{
    osMessageQueueDelete(readBuffer);
    HAL_UART_Abort_IT(&huart1);
}

/// @brief 发送字节数组
/// @param bytes 待发送的字节数组
/// @param length 数组长度
/// @return 状态值
Serial::Status Serial::writeBytes(uint8_t* bytes, uint16_t length)
{
    if (!bytes || length == 0)
        return Status::ERROR;

    HAL_UART_Transmit(&huart1, bytes, length, 0xFFFF);

    return Status::OK;
}

/// @brief 读取字节数组
/// @param bytes 待接收的字节数组
/// @param length 数组长度
/// @param timeout 超时时间
/// @return 状态值
Serial::Status Serial::readBytes(uint8_t* bytes, uint16_t length, uint32_t timeout)
{
    if (isReading || length == 0 || !bytes)
        return Status::ERROR;

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
        return Status::OK;
    else
        return Status::TIMEOUT;
}

/// @brief 清空读缓冲区
void Serial::clearReadBuffer()
{
    osMessageQueueReset(readBuffer);
}

#ifdef __cplusplus
extern "C" {
#endif

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    if (huart == &huart1) {
        if (osMessageQueueGetCount(readBuffer) == readBufferSize) {
            uint8_t temp;
            osMessageQueueGet(readBuffer, &temp, NULL, 0);
        }

        osMessageQueuePut(readBuffer, &aRead, 0, 0);
        HAL_UART_Receive_IT(&huart1, &aRead, readOnceCount);
    }
}

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

} // namespace IO