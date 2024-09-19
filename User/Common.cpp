#include "Common.h"
#include "cmsis_os.h"

void* operator new(size_t size)
{
    auto result = pvPortMalloc(size);
    printf("new(%p, %d)\r\n", result, size);
    return result;
}

void operator delete(void* ptr)
{
    vPortFree(ptr);
    printf("delete(%p)\r\n", ptr);
}

void operator delete(void* ptr, size_t size)
{
    vPortFree(ptr);
    printf("delete(%p, %d)\r\n", ptr, size);
}

void vAssertCalled(uint8_t* file, uint32_t line)
{
    printf("ASSERT! File: %s, Line: %ld\r\n", file, line);
    portENTER_CRITICAL();
    for (;;)
        ;
}

uint32_t GetExecutionTickCount(uint32_t startTickCount)
{
    uint32_t currentTickCount = osKernelGetTickCount();

    if (currentTickCount >= startTickCount) {
        return currentTickCount - startTickCount;
    } else {
        return (UINT32_MAX - startTickCount) + currentTickCount + 1;
    }
}