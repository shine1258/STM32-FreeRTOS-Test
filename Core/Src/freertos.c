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
  // uint32_t num = 0;
  /* Infinite loop */
  for (;;)
  {
    // printf("%d %d %d\r\n",
    //        osThreadGetState(Main_TaskHandle),
    //        // RGBBlue_TaskHandle ? osThreadGetState(RGBBlue_TaskHandle) : 15,
    //        osThreadGetState(RGBBlue_TaskHandle),
    //        osThreadGetState(RGBWhite_TaskHandle));

    // num++;

    // if (num == 5)
    // {

    //   printf("Disable interrupt\r\n");
    //   portDISABLE_INTERRUPTS();

    //   while (++num <= 10000000)
    //     ;

    //   printf("Enable interrupt\r\n");
    //   portENABLE_INTERRUPTS();

    //   num = 0;
    // }

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
