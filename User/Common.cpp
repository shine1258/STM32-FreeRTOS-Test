#include "Common.h"
#include "cmsis_os.h"

void vAssertCalled(uint8_t* file, uint32_t line)
{
    printf("ASSERT! File: %s, Line: %ld\r\n", file, line);
    osKernelLock();
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

void* operator new(size_t size)
{
    printf("new(%d)\r\n", size);
    return pvPortMalloc(size);
}

void operator delete(void* ptr)
{
    printf("delete(%p)\r\n", ptr);
    vPortFree(ptr);
}

void operator delete(void* ptr, size_t size)
{
    printf("delete(%p, %d)\r\n", ptr, size);
    vPortFree(ptr);
}