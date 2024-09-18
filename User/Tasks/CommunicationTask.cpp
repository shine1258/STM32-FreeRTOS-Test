#include "CommunicationTask.h"
#include "Common.h"
#include "Serial.h"
#include "cmsis_os.h"
#include "stdlib.h"

using namespace IO;

constexpr uint8_t bufferSize = 40;
constexpr uint8_t readOnceCount = 10;
constexpr uint8_t repeat = bufferSize / readOnceCount;

char buffer[bufferSize];

void CommunicationTask_Run(void)
{
    auto& Serial = Serial::instance();
    uint32_t totalTimeout = 2000;

    while (true) {

        Serial.clearReadBuffer();

        uint32_t remainTimeout = totalTimeout;
        uint32_t startTime = osKernelGetTickCount();

        buffer[bufferSize] = '\0';

        for (uint8_t i = 0; i < repeat; i++) {
            if (Serial.readBytes((uint8_t*)(buffer + i * readOnceCount), readOnceCount, remainTimeout) == SerialResult::TIMEOUT) {
                goto Timeout;
            }

            remainTimeout = totalTimeout - (GetExecutionTickCount(startTime));
        }

        printf("Received: %s\r\n", buffer);
        osDelay(500);
        continue;

    Timeout:
        printf("Timeout\r\n");
    }
}