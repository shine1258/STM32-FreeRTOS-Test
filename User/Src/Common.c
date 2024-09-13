#include "Common.h"
#include "cmsis_os.h"

void vAssertCalled(uint8_t* file, uint32_t line)
{
    printf("ASSERT! File: %s, Line: %ld\r\n", file, line);
    osKernelLock();
    for (;;)
        ;
}

uint32_t GetElapsedTickCount(uint32_t startTickCount)
{
    uint32_t currentTickCount = osKernelGetTickCount();

    if (currentTickCount >= startTickCount) {
        return currentTickCount - startTickCount;
    } else {
        return (UINT32_MAX - startTickCount) + currentTickCount + 1;
    }
}