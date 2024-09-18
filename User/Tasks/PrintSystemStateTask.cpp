#include "PrintSystemStateTask.h"
#include "Common.h"
#include "cmsis_os.h"
#include "task.h"
#include <stdio.h>

void PrintSystemStateTask_Run(void)
{
    while (true) {
        auto numberOfTasks = osThreadGetCount();
        auto pxTaskStatusArray = new TaskStatus_t[numberOfTasks];
        MALLOC_FAILED_CHECK(pxTaskStatusArray);

        uxTaskGetSystemState(pxTaskStatusArray, numberOfTasks, nullptr);

        for (uint8_t i = 0; i < numberOfTasks; i++) {
            printf("\t%s: %u\r\n",
                pxTaskStatusArray[i].pcTaskName,
                pxTaskStatusArray[i].usStackHighWaterMark);
        }

        delete[] pxTaskStatusArray;

        osDelay(1000);
    }
}