/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "mpu6050.h"
#include "gc9a01a.h"
#include "stdlib.h"
#include "font.h"
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
int test_num = 0;
mpu6050 my_mpu6050;
/* USER CODE END Variables */
/* Definitions for Mpu6050Task */
osThreadId_t Mpu6050TaskHandle;
const osThreadAttr_t Mpu6050Task_attributes = {
  .name = "Mpu6050Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LcdTask */
osThreadId_t LcdTaskHandle;
const osThreadAttr_t LcdTask_attributes = {
  .name = "LcdTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void startMpu6050Task(void *argument);
void startLcdTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
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
  /* creation of Mpu6050Task */
  Mpu6050TaskHandle = osThreadNew(startMpu6050Task, NULL, &Mpu6050Task_attributes);

  /* creation of LcdTask */
  LcdTaskHandle = osThreadNew(startLcdTask, NULL, &LcdTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_startMpu6050Task */
/**
  * @brief  Function implementing the Mpu6050Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_startMpu6050Task */
void startMpu6050Task(void *argument)
{
  /* USER CODE BEGIN startMpu6050Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
  }
  /* USER CODE END startMpu6050Task */
}

/* USER CODE BEGIN Header_startLcdTask */
/**
* @brief Function implementing the LcdTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startLcdTask */
void startLcdTask(void *argument)
{
  /* USER CODE BEGIN startLcdTask */
	GC9A01_Initial();
	int check = 0;
	//LCD_DrawRectangle(20,20,80,80,RED);
	ClearScreen2(WHITE);
	//ClearScreen(RED);
	//test_fill(&hspi2);
  /* Infinite loop */
  for(;;)
  {
	  char buffer[256];
	  itoa(check++,buffer,10);
	  Gc9a01a_WriteString(50,50,buffer,Font_16x26, RED, WHITE);

	  osDelay(1000);
  }
  /* USER CODE END startLcdTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

