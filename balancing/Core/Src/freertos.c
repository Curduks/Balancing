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
#include "stdio.h"
#include "font.h"
#include "pid.h"
#include "usart.h"
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
  .priority = (osPriority_t) osPriorityHigh,
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
	WHO_AM_I(&hi2c1);
	wake_up(&hi2c1);
	set_dlpf(&hi2c1);
	set_sample_rate(&hi2c1, 1000);
	set_sensitivity(&hi2c1, &my_mpu6050, gyro_full_scale_range_2000, accel_full_scale_range_16g);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_GPIO_WritePin(MOTOR_BREAK_GPIO_Port, MOTOR_BREAK_Pin, GPIO_PIN_SET);
	float targetAngle = 41.0; // 목표 각도
	float ANGLE_FIXRATE = 1.5; // [deg/s]
	float measuredAngle = 0.0; // 측정 각도
	set_pwm_duty_cycle(0);
	int8_t check_start = 0;
  /* Infinite loop */
  for(;;)
  {
	  read_gyro(&hi2c1, &my_mpu6050, deg_per_sec);
	  read_accel(&hi2c1, &my_mpu6050, gravity_acceleration);
	  cal_Roll_Pitch(&my_mpu6050);
	  measuredAngle = my_mpu6050.pitch;
	  if((int)measuredAngle == (int)targetAngle) check_start = 1; // 목표 각도로 옮겼을 때 부터 시작하기 위해

	  if(check_start != 0){
		  if(measuredAngle < targetAngle){ // 목표값을 시간과 측정값에 따라 변화
			  targetAngle += ANGLE_FIXRATE * 0.011;
		  }else{
			  targetAngle -= ANGLE_FIXRATE * 0.011;
		  }
		  motor_control(&my_mpu6050, pid_control(targetAngle,measuredAngle));
	  }
	  osDelay(10);
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
	osDelay(100);

	GC9A01_Initial();
	int roll_before = (int)my_mpu6050.roll;
	int roll_after = 0;
	int pitch_before = (int)my_mpu6050.pitch;
	int pitch_after = 0;
	ClearScreen2(WHITE);
	char buffer[5];

	/* roll pitch 초기 0 LCD 출력 */
	Gc9a01a_WriteString(40, 50, "roll:", Font_11x18, BLACK, WHITE);
	Gc9a01a_WriteString(40, 68, "pitch:", Font_11x18, BLACK, WHITE);
	Gc9a01a_WriteString(95,50,"0",Font_11x18, BLACK, WHITE);
	Gc9a01a_WriteString(106,68,"0",Font_11x18, BLACK, WHITE);

  /* Infinite loop */
  for(;;)
  {
	  /* roll or pitch 값 변화 시 LCD에 표기 */
	  roll_after = (int)my_mpu6050.roll;
	  pitch_after = (int)my_mpu6050.pitch;

	  if(roll_after != roll_before){
		  sprintf(buffer, "%d", roll_after);
		  for(int i = 0; i < 4; i++){
			  if(buffer[i] == '\0' || buffer[i] == 165){
				  buffer[i] = ' ';
			  }
		  }
		  buffer[4] = '\0';
		  Gc9a01a_WriteString(95,50,buffer,Font_11x18, BLACK, WHITE);
		  roll_before = roll_after;
	  }
	  if(pitch_after != pitch_before){
		  sprintf(buffer, "%d", pitch_after);
		  for(int i = 0; i < 4; i++){
			  if(buffer[i] == '\0' || buffer[i] == 165){
				  buffer[i] = ' ';
			  }
		  }
		  buffer[4] = '\0';
		  Gc9a01a_WriteString(106,68,buffer,Font_11x18, BLACK, WHITE);
		  pitch_before = pitch_after;
	  }


	  /* ------------------------------------ */

	  osDelay(30);
  }
  /* USER CODE END startLcdTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

