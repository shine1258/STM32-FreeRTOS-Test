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

        uxTaskGetSystemState(pxTaskStatusArray, numberOfTasks, nullptr);

        printf("\r\nTask Name : Stack Max\r\n");

        for (uint8_t i = 0; i < numberOfTasks; i++) {
            printf("%s : %d\r\n",
                pxTaskStatusArray[i].pcTaskName,
                pxTaskStatusArray[i].usStackHighWaterMark);
        }

        printf("\r\n");

        delete[] pxTaskStatusArray;

        osDelay(5000);
    }
}