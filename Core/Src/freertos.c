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
#include "CommunicationTask.h"
#include "Key.h"
#include "MainTask.h"
#include "PrintSystemStateTask.h"
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

/* USER CODE END Variables */
/* Definitions for MainTask */
osThreadId_t MainTaskHandle;
const osThreadAttr_t MainTask_attributes = {
    .name = "MainTask",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityAboveNormal,
};
/* Definitions for Task01 */
osThreadId_t Task01Handle;
const osThreadAttr_t Task01_attributes = {
    .name = "Task01",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityLow,
};
/* Definitions for Task02 */
osThreadId_t Task02Handle;
const osThreadAttr_t Task02_attributes = {
    .name = "Task02",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityLow1,
};
/* Definitions for KeyScanTask */
osThreadId_t KeyScanTaskHandle;
const osThreadAttr_t KeyScanTask_attributes = {
    .name = "KeyScanTask",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void MainTaskEntry(void* argument);
void Task01Entry(void* argument);
void Task02Entry(void* argument);
void KeyScanTaskEntry(void* argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char* pcTaskName);

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
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */

    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */

    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */

    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of MainTask */
    MainTaskHandle = osThreadNew(MainTaskEntry, NULL, &MainTask_attributes);

    /* creation of Task01 */
    Task01Handle = osThreadNew(Task01Entry, NULL, &Task01_attributes);

    /* creation of Task02 */
    Task02Handle = osThreadNew(Task02Entry, NULL, &Task02_attributes);

    /* creation of KeyScanTask */
    KeyScanTaskHandle = osThreadNew(KeyScanTaskEntry, NULL, &KeyScanTask_attributes);

    /* USER CODE BEGIN RTOS_THREADS */

    MALLOC_FAILED_CHECK(MainTaskHandle);
    MALLOC_FAILED_CHECK(Task01Handle);
    MALLOC_FAILED_CHECK(Task02Handle);
    MALLOC_FAILED_CHECK(KeyScanTaskHandle);

    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */

    /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_MainTaskEntry */
/**
 * @brief  Function implementing the MainTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_MainTaskEntry */
__weak void MainTaskEntry(void* argument)
{
    /* USER CODE BEGIN MainTaskEntry */
    UNUSED(argument);
    MainTask_Run();
    /* Infinite loop */
    for (;;) {
        osDelay(1);
    }
    /* USER CODE END MainTaskEntry */
}

/* USER CODE BEGIN Header_Task01Entry */
/**
 * @brief Function implementing the Task01 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Task01Entry */
__weak void Task01Entry(void* argument)
{
    /* USER CODE BEGIN Task01Entry */
    UNUSED(argument);
    // PrintSystemStateTask_Run();
    /* Infinite loop */
    for (;;) { }
    /* USER CODE END Task01Entry */
}

/* USER CODE BEGIN Header_Task02Entry */
/**
 * @brief Function implementing the Task02 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Task02Entry */
__weak void Task02Entry(void* argument)
{
    /* USER CODE BEGIN Task02Entry */
    UNUSED(argument);
    CommunicationTask_Run();

    /* Infinite loop */
    for (;;) { }
    /* USER CODE END Task02Entry */
}

/* USER CODE BEGIN Header_KeyScanTaskEntry */
/**
 * @brief Function implementing the KeyScanTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_KeyScanTaskEntry */
__weak void KeyScanTaskEntry(void* argument)
{
    /* USER CODE BEGIN KeyScanTaskEntry */
    UNUSED(argument);
    /* Infinite loop */
    for (;;) {
        osDelay(1);
    }
    /* USER CODE END KeyScanTaskEntry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */
