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
/* Definitions for Main_Task */
osThreadId_t Main_TaskHandle;
const osThreadAttr_t Main_Task_attributes = {
    .name = "Main_Task",
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
/* Definitions for KeyScan_Task */
osThreadId_t KeyScan_TaskHandle;
const osThreadAttr_t KeyScan_Task_attributes = {
    .name = "KeyScan_Task",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityLow,
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

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void Main_TaskEntry(void* argument);
void Task01Entry(void* argument);
void Task02Entry(void* argument);
void KeyScan_TaskEntry(void* argument);

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

    /* USER CODE BEGIN RTOS_QUEUES */

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

    /* USER CODE BEGIN RTOS_THREADS */

    MALLOC_FAILED_CHECK(Main_TaskHandle);
    MALLOC_FAILED_CHECK(Task01Handle);
    MALLOC_FAILED_CHECK(Task02Handle);
    MALLOC_FAILED_CHECK(KeyScan_TaskHandle);

    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */

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
    MainTask_Run();
    /* Infinite loop */

    for (;;) {
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
void Task01Entry(void* argument)
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
void Task02Entry(void* argument)
{
    /* USER CODE BEGIN Task02Entry */
    UNUSED(argument);
    CommunicationTask_Run();

    /* Infinite loop */
    for (;;) { }
    /* USER CODE END Task02Entry */
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

    /* Infinite loop */
    for (;;) {
        osDelay(10);
    }
    /* USER CODE END KeyScan_TaskEntry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */
