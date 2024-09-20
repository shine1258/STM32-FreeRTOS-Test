#include "Serial.hpp"
#include "Common.h"
#include "cmsis_os.h"
#include "usart.h"

namespace IO::Serial {

static constexpr uint8_t readOnceCount = 1;
static constexpr uint16_t readBufferSize = 256;
static bool isReading;
static bool isInited;
static osMessageQueueId_t readBuffer;
static uint8_t aRead;
static void init();

static void init()
{
    readBuffer = osMessageQueueNew(readBufferSize, sizeof(uint8_t), nullptr);
    MALLOC_FAILED_CHECK(readBuffer);
    HAL_UART_Receive_IT(&huart1, &aRead, readOnceCount);
}

/// @brief 发送字节数组
/// @param bytes 待发送的字节数组
/// @param length 数组长度
/// @return 状态值
Status writeBytes(const uint8_t* bytes, const uint16_t length)
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
Status readBytes(uint8_t* bytes, const uint16_t length, const uint32_t timeout)
{
    if (isReading || length == 0 || !bytes)
        return Status::ERROR;

    if (!isInited) {
        init();
        isInited = true;
    }

    isReading = true;

    osStatus_t status = osStatus_t::osOK;
    uint32_t remainTimeout = timeout;
    uint16_t readedLength = 0;
    auto startTime = osKernelGetTickCount();

    while (readedLength < length && status == osStatus_t::osOK) {
        status = osMessageQueueGet(readBuffer, bytes + readedLength, nullptr, remainTimeout);
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
void clearReadBuffer()
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
            osMessageQueueGet(readBuffer, &temp, nullptr, 0);
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
    writeBytes((uint8_t*)&ch, 1);
    return ch;
}

#ifdef __cplusplus
}
#endif

} // namespace IO
