#include "Common.h"
#include "cmsis_os.h"

void vAssertCalled(uint8_t* file, uint32_t line)
{
    printf("ASSERT! File: %s, Line: %ld\r\n", file, line);
    osKernelLock();
    for (;;)
        ;
}
