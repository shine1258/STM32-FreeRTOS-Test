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

// List_t list;
// ListItem_t listItem1;
// ListItem_t listItem2;
// ListItem_t listItem3;

/* USER CODE END Variables */
osThreadId Main_TaskHandle;
osThreadId RGBBlue_TaskHandle;
osThreadId RGBWhite_TaskHandle;
osThreadId KeyScan_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Main_TaskEntry(void const *argument);
void RGBBlue_TaskEntry(void const *argument);
void RGBWhite_TaskEntry(void const *argument);
void KeyScan_TaskEntry(void const *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Main_Task */
  osThreadDef(Main_Task, Main_TaskEntry, osPriorityAboveNormal, 0, 128);
  Main_TaskHandle = osThreadCreate(osThread(Main_Task), NULL);

  /* definition and creation of RGBBlue_Task */
  osThreadDef(RGBBlue_Task, RGBBlue_TaskEntry, osPriorityLow, 0, 128);
  RGBBlue_TaskHandle = osThreadCreate(osThread(RGBBlue_Task), NULL);

  /* definition and creation of RGBWhite_Task */
  osThreadDef(RGBWhite_Task, RGBWhite_TaskEntry, osPriorityLow, 0, 128);
  RGBWhite_TaskHandle = osThreadCreate(osThread(RGBWhite_Task), NULL);

  /* definition and creation of KeyScan_Task */
  osThreadDef(KeyScan_Task, KeyScan_TaskEntry, osPriorityLow, 0, 128);
  KeyScan_TaskHandle = osThreadCreate(osThread(KeyScan_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */
}

/* USER CODE BEGIN Header_Main_TaskEntry */
/**
 * @brief  Function implementing the Main_Task thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_Main_TaskEntry */
void Main_TaskEntry(void const *argument)
{
  /* USER CODE BEGIN Main_TaskEntry */
  UNUSED(argument);

#pragma region
  // printf("初始化列表和列表项\r\n");

  // vListInitialise(&list);
  // vListInitialiseItem(&listItem1);
  // vListInitialiseItem(&listItem2);
  // vListInitialiseItem(&listItem3);

  // listItem1.xItemValue = 40;
  // listItem2.xItemValue = 60;
  // listItem3.xItemValue = 50;

  // printf("list: %p\r\n", (void *)&list);
  // printf("list->pxIndex: %p\r\n", (void *)list.pxIndex);
  // printf("list->xListEnd: %p\r\n", (void *)&list.xListEnd);
  // printf("listItem1: %p\r\n", (void *)&listItem1);
  // printf("listItem2: %p\r\n", (void *)&listItem2);
  // printf("listItem3: %p\r\n", (void *)&listItem3);
  // printf("\r\n");

  // printf("将列表项1插入到列表中\r\n");

  // vListInsert(&list, &listItem1);

  // printf("list->xListEnd->pxNext: %p\r\n", (void *)list.xListEnd.pxNext);
  // printf("listItem1->pxNext: %p\r\n", (void *)listItem1.pxNext);
  // printf("list->xListEnd->pxPrevious: %p\r\n", (void *)list.xListEnd.pxPrevious);
  // printf("listItem1->pxPrevious: %p\r\n", (void *)listItem1.pxPrevious);
  // printf("\r\n");

  // printf("将列表项2插入到列表中\r\n");

  // vListInsert(&list, &listItem2);

  // printf("list->xListEnd->pxNext: %p\r\n", (void *)list.xListEnd.pxNext);
  // printf("listItem1->pxNext: %p\r\n", (void *)listItem1.pxNext);
  // printf("listItem2->pxNext: %p\r\n", (void *)listItem2.pxNext);
  // printf("list->xListEnd->pxPrevious: %p\r\n", (void *)list.xListEnd.pxPrevious);
  // printf("listItem1->pxPrevious: %p\r\n", (void *)listItem1.pxPrevious);
  // printf("listItem2->pxPrevious: %p\r\n", (void *)listItem2.pxPrevious);
  // printf("\r\n");

  // printf("将列表项3插入到列表中\r\n");

  // vListInsert(&list, &listItem3);

  // printf("list->xListEnd->pxNext: %p\r\n", (void *)list.xListEnd.pxNext);
  // printf("listItem1->pxNext: %p\r\n", (void *)listItem1.pxNext);
  // printf("listItem2->pxNext: %p\r\n", (void *)listItem2.pxNext);
  // printf("listItem3->pxNext: %p\r\n", (void *)listItem3.pxNext);
  // printf("list->xListEnd->pxPrevious: %p\r\n", (void *)list.xListEnd.pxPrevious);
  // printf("listItem1->pxPrevious: %p\r\n", (void *)listItem1.pxPrevious);
  // printf("listItem2->pxPrevious: %p\r\n", (void *)listItem2.pxPrevious);
  // printf("listItem3->pxPrevious: %p\r\n", (void *)listItem3.pxPrevious);
  // printf("\r\n");

  // printf("从列表中移除列表项2\r\n");

  // uxListRemove(&listItem2);

  // printf("list->xListEnd->pxNext: %p\r\n", (void *)list.xListEnd.pxNext);
  // printf("listItem1->pxNext: %p\r\n", (void *)listItem1.pxNext);
  // printf("listItem3->pxNext: %p\r\n", (void *)listItem3.pxNext);
  // printf("list->xListEnd->pxPrevious: %p\r\n", (void *)list.xListEnd.pxPrevious);
  // printf("listItem1->pxPrevious: %p\r\n", (void *)listItem1.pxPrevious);
  // printf("listItem3->pxPrevious: %p\r\n", (void *)listItem3.pxPrevious);
  // printf("\r\n");

  // printf("将列表项2插入到列表末尾\r\n");

  // list.pxIndex = &listItem1;
  // vListInsertEnd(&list, &listItem2);

  // printf("list->xListEnd->pxNext: %p\r\n", (void *)list.xListEnd.pxNext);
  // printf("listItem1->pxNext: %p\r\n", (void *)listItem1.pxNext);
  // printf("listItem2->pxNext: %p\r\n", (void *)listItem2.pxNext);
  // printf("listItem3->pxNext: %p\r\n", (void *)listItem3.pxNext);
  // printf("list->xListEnd->pxPrevious: %p\r\n", (void *)list.xListEnd.pxPrevious);
  // printf("listItem1->pxPrevious: %p\r\n", (void *)listItem1.pxPrevious);
  // printf("listItem2->pxPrevious: %p\r\n", (void *)listItem2.pxPrevious);
  // printf("listItem3->pxPrevious: %p\r\n", (void *)listItem3.pxPrevious);
  // printf("\r\n");
#pragma endregion

  osThreadSetPriority(NULL, osPriorityHigh);
  osThreadSetPriority(RGBBlue_TaskHandle, osPriorityBelowNormal);
  osThreadSetPriority(RGBWhite_TaskHandle, osPriorityBelowNormal);

  printf("Priority of Main_Task: %d\r\n", osThreadGetPriority(NULL));
  printf("Priority of RGBBlue_Task: %d\r\n", osThreadGetPriority(RGBBlue_TaskHandle));
  printf("Priority of RGBWhite_Task: %d\r\n", osThreadGetPriority(RGBWhite_TaskHandle));

  UBaseType_t nums = uxTaskGetNumberOfTasks();
  printf("Nums of tasks: %ld\r\n", nums);

  TaskStatus_t *taskStatusArray = pvPortMalloc(nums * sizeof(TaskStatus_t));
  uxTaskGetSystemState(taskStatusArray, nums, NULL);

  for (uint8_t i = 0; i < nums; i++)
  {
    printf("\r\n");
    printf("Task[%d]->name: %s\r\n", i, taskStatusArray[i].pcTaskName);
    printf("Task[%d]->number: %ld\r\n", i, taskStatusArray[i].xTaskNumber);
    printf("Task[%d]->priority: %ld\r\n", i, taskStatusArray[i].uxCurrentPriority);
  }

  vPortFree(taskStatusArray);

  TaskStatus_t taskStatus;
  vTaskGetInfo(NULL, &taskStatus, pdTRUE, eInvalid);

  printf("\r\n");
  printf("Task->name: %s\r\n", taskStatus.pcTaskName);
  printf("Task->number: %ld\r\n", taskStatus.xTaskNumber);
  printf("Task->priority: %ld\r\n", taskStatus.uxCurrentPriority);

  /* Infinite loop */
  for (;;)
  {
    osDelay(1000);
  }
  /* USER CODE END Main_TaskEntry */
}

/* USER CODE BEGIN Header_RGBBlue_TaskEntry */
/**
 * @brief Function implementing the RGBBlue_Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_RGBBlue_TaskEntry */
void RGBBlue_TaskEntry(void const *argument)
{
  /* USER CODE BEGIN RGBBlue_TaskEntry */
  UNUSED(argument);
  /* Infinite loop */
  for (;;)
  {
    osDelay(500);
    // HAL_GPIO_TogglePin(RGB_BLUE_GPIO_Port, RGB_BLUE_Pin);
  }
  /* USER CODE END RGBBlue_TaskEntry */
}

/* USER CODE BEGIN Header_RGBWhite_TaskEntry */
/**
 * @brief Function implementing the RGBWhite_Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_RGBWhite_TaskEntry */
void RGBWhite_TaskEntry(void const *argument)
{
  /* USER CODE BEGIN RGBWhite_TaskEntry */
  UNUSED(argument);
  /* Infinite loop */
  for (;;)
  {
    osDelay(1000);
    // HAL_GPIO_TogglePin(RGB_WHITE_GPIO_Port, RGB_WHITE_Pin);
  }
  /* USER CODE END RGBWhite_TaskEntry */
}

/* USER CODE BEGIN Header_KeyScan_TaskEntry */
/**
 * @brief Function implementing the KeyScan_Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_KeyScan_TaskEntry */
void KeyScan_TaskEntry(void const *argument)
{
  /* USER CODE BEGIN KeyScan_TaskEntry */
  UNUSED(argument);
  /* Infinite loop */
  for (;;)
  {
    if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET)
    {
      osDelay(10); // Debounce delay

      while (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET)
      {
        osDelay(1); // Wait for key release
      }

      // if (RGBBlue_TaskHandle)
      // {
      //   osThreadTerminate(RGBBlue_TaskHandle);
      //   RGBBlue_TaskHandle = NULL;
      // }
      // else
      // {
      //   osThreadDef(RGBBlue_Task, RGBBlue_TaskEntry, osPriorityLow, 0, 128);
      //   RGBBlue_TaskHandle = osThreadCreate(osThread(RGBBlue_Task), NULL);
      // }

      // osThreadSuspend(RGBBlue_TaskHandle);

      osDelay(10); // Debounce delay
    }

    osDelay(1);
  }
  /* USER CODE END KeyScan_TaskEntry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == Sensor_Pin)
  {
    // osThreadResume(RGBBlue_TaskHandle);
  }
}
/* USER CODE END Application */
