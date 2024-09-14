/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "Common.h"
#include "Key.h"
#include "Serial.h"
#include "event_groups.h"
#include "queue.h"
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

char buffer[20] = "fdsagfhdshds";
char runTimeBuffer[200];
QueueSetHandle_t myQueueSetHandle;

/* USER CODE END Variables */
/* Definitions for Main_Task */
osThreadId_t Main_TaskHandle;
const osThreadAttr_t Main_Task_attributes = {
  .name = "Main_Task",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for Task01 */
osThreadId_t Task01Handle;
const osThreadAttr_t Task01_attributes = {
  .name = "Task01",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task02 */
osThreadId_t Task02Handle;
const osThreadAttr_t Task02_attributes = {
  .name = "Task02",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for KeyScan_Task */
osThreadId_t KeyScan_TaskHandle;
const osThreadAttr_t KeyScan_Task_attributes = {
  .name = "KeyScan_Task",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task03 */
osThreadId_t Task03Handle;
const osThreadAttr_t Task03_attributes = {
  .name = "Task03",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow2,
};
/* Definitions for queue */
osMessageQueueId_t queueHandle;
const osMessageQueueAttr_t queue_attributes = {
  .name = "queue"
};
/* Definitions for bigItemQueue */
osMessageQueueId_t bigItemQueueHandle;
const osMessageQueueAttr_t bigItemQueue_attributes = {
  .name = "bigItemQueue"
};
/* Definitions for myMutex01 */
osMutexId_t myMutex01Handle;
const osMutexAttr_t myMutex01_attributes = {
  .name = "myMutex01"
};
/* Definitions for myBinarySem01 */
osSemaphoreId_t myBinarySem01Handle;
const osSemaphoreAttr_t myBinarySem01_attributes = {
  .name = "myBinarySem01"
};
/* Definitions for myCountingSem01 */
osSemaphoreId_t myCountingSem01Handle;
const osSemaphoreAttr_t myCountingSem01_attributes = {
  .name = "myCountingSem01"
};
/* Definitions for myEvent01 */
osEventFlagsId_t myEvent01Handle;
const osEventFlagsAttr_t myEvent01_attributes = {
  .name = "myEvent01"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void Main_TaskEntry(void *argument);
void Task01Entry(void *argument);
void Task02Entry(void *argument);
void KeyScan_TaskEntry(void *argument);
void Task03Entry(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void) { }

__weak unsigned long getRunTimeCounterValue(void)
{
    return 0;
}
/* USER CODE END 1 */

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char* pcTaskName)
{
    UNUSED(xTask);
    printf("Stack overflow in task %s\r\n", pcTaskName);
    vAssertCalled((uint8_t*)__FILE__, __LINE__);
}
/* USER CODE END 4 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

    myQueueSetHandle = xQueueCreateSet(2);
    MALLOC_FAILED_CHECK(myQueueSetHandle);

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of myMutex01 */
  myMutex01Handle = osMutexNew(&myMutex01_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */

    MALLOC_FAILED_CHECK(myMutex01Handle);

  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinarySem01 */
  myBinarySem01Handle = osSemaphoreNew(1, 0, &myBinarySem01_attributes);

  /* creation of myCountingSem01 */
  myCountingSem01Handle = osSemaphoreNew(100, 0, &myCountingSem01_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */

    MALLOC_FAILED_CHECK(myBinarySem01Handle);
    MALLOC_FAILED_CHECK(myCountingSem01Handle);

  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of queue */
  queueHandle = osMessageQueueNew (2, sizeof(int8_t), &queue_attributes);

  /* creation of bigItemQueue */
  bigItemQueueHandle = osMessageQueueNew (1, sizeof(char *), &bigItemQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */

    MALLOC_FAILED_CHECK(queueHandle);
    MALLOC_FAILED_CHECK(bigItemQueueHandle);

    xQueueAddToSet(queueHandle, myQueueSetHandle);
    xQueueAddToSet(myBinarySem01Handle, myQueueSetHandle);

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Main_Task */
  Main_TaskHandle = osThreadNew(Main_TaskEntry, NULL, &Main_Task_attributes);

  /* creation of Task01 */
  Task01Handle = osThreadNew(Task01Entry, NULL, &Task01_attributes);

  /* creation of Task02 */
  Task02Handle = osThreadNew(Task02Entry, NULL, &Task02_attributes);

  /* creation of KeyScan_Task */
  KeyScan_TaskHandle = osThreadNew(KeyScan_TaskEntry, NULL, &KeyScan_Task_attributes);

  /* creation of Task03 */
  Task03Handle = osThreadNew(Task03Entry, NULL, &Task03_attributes);

  /* USER CODE BEGIN RTOS_THREADS */

    MALLOC_FAILED_CHECK(Main_TaskHandle);
    MALLOC_FAILED_CHECK(Task01Handle);
    MALLOC_FAILED_CHECK(Task02Handle);
    MALLOC_FAILED_CHECK(KeyScan_TaskHandle);
    MALLOC_FAILED_CHECK(Task03Handle);

  /* USER CODE END RTOS_THREADS */

  /* creation of myEvent01 */
  myEvent01Handle = osEventFlagsNew(&myEvent01_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */

    MALLOC_FAILED_CHECK(myEvent01Handle);

  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Main_TaskEntry */
/**
 * @brief  Function implementing the Main_Task thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_Main_TaskEntry */
void Main_TaskEntry(void *argument)
{
  /* USER CODE BEGIN Main_TaskEntry */
    UNUSED(argument);

    /* Infinite loop */

    for (;;) {
        // vTaskGetRunTimeStats(runTimeBuffer);
        // printf("Run Time Stats:\n%s\n", runTimeBuffer);
        osDelay(5000);
    }
  /* USER CODE END Main_TaskEntry */
}

/* USER CODE BEGIN Header_Task01Entry */
/**
 * @brief Function implementing the Task01 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Task01Entry */
void Task01Entry(void *argument)
{
  /* USER CODE BEGIN Task01Entry */
    UNUSED(argument);
    /* Infinite loop */
    for (;;) {
        osThreadFlagsWait(BIT_0, osFlagsWaitAny, osWaitForever);
        printf("Flag received\r\n");
    }
  /* USER CODE END Task01Entry */
}

/* USER CODE BEGIN Header_Task02Entry */
/**
 * @brief Function implementing the Task02 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Task02Entry */
void Task02Entry(void *argument)
{
  /* USER CODE BEGIN Task02Entry */
    UNUSED(argument);
    /* Infinite loop */
    for (;;) {
        Serial_ClearReadBuffer();

        uint32_t totalTimeout = 2000;
        uint32_t remainTimeout = totalTimeout;
        uint32_t startTime = osKernelGetTickCount();

        if (Serial_ReadBytes((uint8_t*)buffer, 20, remainTimeout) == SERIAL_TIMEOUT)
            goto Timeout;

        remainTimeout = totalTimeout - (GetElapsedTickCount(startTime));
        printf("%ld\r\n", remainTimeout);

        if (Serial_ReadBytes((uint8_t*)buffer, 20, remainTimeout) == SERIAL_TIMEOUT)
            goto Timeout;

        remainTimeout = totalTimeout - (GetElapsedTickCount(startTime));
        printf("%ld\r\n", remainTimeout);

        if (Serial_ReadBytes((uint8_t*)buffer, 20, remainTimeout) == SERIAL_TIMEOUT)
            goto Timeout;

        remainTimeout = totalTimeout - (GetElapsedTickCount(startTime));
        printf("%ld\r\n", remainTimeout);

        if (Serial_ReadBytes((uint8_t*)buffer, 20, remainTimeout) == SERIAL_TIMEOUT)
            goto Timeout;

        printf("Success\r\n");
        osDelay(500);
        continue;

    Timeout:
        printf("Timeout\r\n");
    }
  /* USER CODE END Task02Entry */
}

/* USER CODE BEGIN Header_KeyScan_TaskEntry */
/**
 * @brief Function implementing the KeyScan_Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_KeyScan_TaskEntry */
void KeyScan_TaskEntry(void *argument)
{
  /* USER CODE BEGIN KeyScan_TaskEntry */
    UNUSED(argument);

    /* Infinite loop */
    for (;;) {
        int8_t keyNum = KeyScan();

        if (keyNum != -1) {
            printf("Key %d pressed\r\n", keyNum);

            switch (keyNum) {
            case 1:
                osThreadFlagsSet(Task01Handle, BIT_0);
                break;
            case 2:
                osEventFlagsSet(myEvent01Handle, BIT_1);
                break;
            default:
                break;
            }
        }

        osDelay(10);
    }
  /* USER CODE END KeyScan_TaskEntry */
}

/* USER CODE BEGIN Header_Task03Entry */
/**
 * @brief Function implementing the Task03 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Task03Entry */
void Task03Entry(void *argument)
{
  /* USER CODE BEGIN Task03Entry */
    UNUSED(argument);
    /* Infinite loop */
    for (;;) {
        osDelay(1);
    }
  /* USER CODE END Task03Entry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */

