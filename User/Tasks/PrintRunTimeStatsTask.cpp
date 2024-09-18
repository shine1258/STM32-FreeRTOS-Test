#include "PrintRunTimeStatsTask.h"
#include "cmsis_os.h"
#include "task.h"
#include <stdio.h>

static char runTimeStatsBuffer[200];

void PrintRunTimeStatsTask_Run(void)
{
    while (true) {
        vTaskGetRunTimeStats(runTimeStatsBuffer);
        printf("%s\r\n", runTimeStatsBuffer);
        osDelay(1000);
    }
}