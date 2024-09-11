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
#include "cmsis_os.h"
#include "main.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "Common.h"
#include "Key.h"
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

/* USER CODE END Variables */
/* Definitions for Main_Task */
osThreadId_t Main_TaskHandle;
const osThreadAttr_t Main_Task_attributes = {
    .name = "Main_Task",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityAboveNormal,
};
/* Definitions for QueueR_Task */
osThreadId_t QueueR_TaskHandle;
const osThreadAttr_t QueueR_Task_attributes = {
    .name = "QueueR_Task",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityLow,
};
/* Definitions for QueueRB_Task */
osThreadId_t QueueRB_TaskHandle;
const osThreadAttr_t QueueRB_Task_attributes = {
    .name = "QueueRB_Task",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityLow,
};
/* Definitions for KeyScan_Task */
osThreadId_t KeyScan_TaskHandle;
const osThreadAttr_t KeyScan_Task_attributes = {
    .name = "KeyScan_Task",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityLow,
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

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void Main_TaskEntry(void* argument);
void QueueR_TaskEntry(void* argument);
void QueueRB_TaskEntry(void* argument);
void KeyScan_TaskEntry(void* argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
}

__weak unsigned long getRunTimeCounterValue(void)
{
    return 0;
}
/* USER CODE END 1 */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* Create the queue(s) */
    /* creation of queue */
    queueHandle = osMessageQueueNew(2, sizeof(int8_t), &queue_attributes);

    /* creation of bigItemQueue */
    bigItemQueueHandle = osMessageQueueNew(1, sizeof(char*), &bigItemQueue_attributes);

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */

    MALLOC_FAILED_CHECK(queueHandle);
    MALLOC_FAILED_CHECK(bigItemQueueHandle);

    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of Main_Task */
    Main_TaskHandle = osThreadNew(Main_TaskEntry, NULL, &Main_Task_attributes);

    /* creation of QueueR_Task */
    QueueR_TaskHandle = osThreadNew(QueueR_TaskEntry, NULL, &QueueR_Task_attributes);

    /* creation of QueueRB_Task */
    QueueRB_TaskHandle = osThreadNew(QueueRB_TaskEntry, NULL, &QueueRB_Task_attributes);

    /* creation of KeyScan_Task */
    KeyScan_TaskHandle = osThreadNew(KeyScan_TaskEntry, NULL, &KeyScan_Task_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */

    MALLOC_FAILED_CHECK(Main_TaskHandle);
    MALLOC_FAILED_CHECK(QueueR_TaskHandle);
    MALLOC_FAILED_CHECK(QueueRB_TaskHandle);
    MALLOC_FAILED_CHECK(KeyScan_TaskHandle);

    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_Main_TaskEntry */
/**
 * @brief  Function implementing the Main_Task thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_Main_TaskEntry */
void Main_TaskEntry(void* argument)
{
    /* USER CODE BEGIN Main_TaskEntry */
    UNUSED(argument);

    /* Infinite loop */

    for (;;) {
        printf("Stack high water mark of each task:\r\n");

        UBaseType_t numOfTasks = uxTaskGetNumberOfTasks();
        TaskStatus_t* taskStatusArr = pvPortMalloc(numOfTasks * sizeof(TaskStatus_t));
        MALLOC_FAILED_CHECK(taskStatusArr);
        uxTaskGetSystemState(taskStatusArr, numOfTasks, NULL);

        for (uint8_t i = 0; i < numOfTasks; i++) {
            printf("%s: %d\r\n", taskStatusArr[i].pcTaskName, taskStatusArr[i].usStackHighWaterMark);
        }

        vPortFree(taskStatusArr);

        printf("\r\n");
        osDelay(5000);
    }
    /* USER CODE END Main_TaskEntry */
}

/* USER CODE BEGIN Header_QueueR_TaskEntry */
/**
 * @brief Function implementing the QueueR_Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_QueueR_TaskEntry */
void QueueR_TaskEntry(void* argument)
{
    /* USER CODE BEGIN QueueR_TaskEntry */
    UNUSED(argument);
    /* Infinite loop */
    for (;;) {
        int8_t keyNum;
        osMessageQueueGet(queueHandle, &keyNum, NULL, osWaitForever);
        printf("QueueR received key %d\r\n", keyNum);
    }
    /* USER CODE END QueueR_TaskEntry */
}

/* USER CODE BEGIN Header_QueueRB_TaskEntry */
/**
 * @brief Function implementing the QueueRB thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_QueueRB_TaskEntry */
void QueueRB_TaskEntry(void* argument)
{
    /* USER CODE BEGIN QueueRB_TaskEntry */
    UNUSED(argument);
    char* pBuffer;

    /* Infinite loop */
    for (;;) {
        osMessageQueueGet(bigItemQueueHandle, &pBuffer, NULL, osWaitForever);
        printf("QueueRB received: %s\r\n", pBuffer);
    }
    /* USER CODE END QueueRB_TaskEntry */
}

/* USER CODE BEGIN Header_KeyScan_TaskEntry */
/**
 * @brief Function implementing the KeyScan_Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_KeyScan_TaskEntry */
void KeyScan_TaskEntry(void* argument)
{
    /* USER CODE BEGIN KeyScan_TaskEntry */
    UNUSED(argument);
    char* pBuffer = buffer;

    /* Infinite loop */
    for (;;) {
        int8_t keyNum = KeyScan();

        if (keyNum != -1) {
            printf("Key %d pressed\r\n", keyNum);

            switch (keyNum) {
            case 1:
                osMessageQueuePut(queueHandle, &keyNum, 0, osWaitForever);
                break;
            case 2:
                osMessageQueuePut(bigItemQueueHandle, &pBuffer, 0, osWaitForever);
                break;
            default:
                break;
            }
        }

        osDelay(10);
    }
    /* USER CODE END KeyScan_TaskEntry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */
