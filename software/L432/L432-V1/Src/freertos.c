/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "data.h"
#include "screen.h"
#include "mcp23017.h"
#include "input.h"
#include "mapper.h"

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
osThreadId screenTaskHandle;
osThreadId inputTaskHandle;
osMutexId i2c1_mutexHandle;
osMutexId i2c3_mutexHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartScreenTask(void const * argument);
void StartInputTask(void const * argument);

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
void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */
       
	/* USER CODE END Init */

	/* Create the mutex(es) */
	/* definition and creation of i2c1_mutex */
	osMutexDef(i2c1_mutex);
	i2c1_mutexHandle = osMutexCreate(osMutex(i2c1_mutex));

	/* definition and creation of i2c3_mutex */
	osMutexDef(i2c3_mutex);
	i2c3_mutexHandle = osMutexCreate(osMutex(i2c3_mutex));

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
	/* definition and creation of screenTask */
	osThreadDef(screenTask, StartScreenTask, osPriorityLow, 0, 128);
	screenTaskHandle = osThreadCreate(osThread(screenTask), NULL);

	/* definition and creation of inputTask */
	osThreadDef(inputTask, StartInputTask, osPriorityNormal, 0, 128);
	inputTaskHandle = osThreadCreate(osThread(inputTask), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
		/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartScreenTask */
/**
  * @brief  Function implementing the screenTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartScreenTask */
void StartScreenTask(void const * argument)
{
	/* USER CODE BEGIN StartScreenTask */
	//osEvent evt;
	/* Infinite loop */
	for (;;)
	{
		osSignalWait(1, 1000);
		if (osMutexWait(i2c3_mutexHandle, osWaitForever) == osOK) {
			screen_draw(&currentData, &scopeData);
			osMutexRelease(i2c3_mutexHandle);
		}
		osDelay(1);
	}
	/* USER CODE END StartScreenTask */
}

/* USER CODE BEGIN Header_StartInputTask */
/**
* @brief Function implementing the inputTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartInputTask */
void StartInputTask(void const * argument)
{
	/* USER CODE BEGIN StartInputTask */
	osEvent evt;
	/* Infinite loop */
	for (;;)
	{
		evt = osSignalWait(1, 5000);
		if (osMutexWait(i2c1_mutexHandle, osWaitForever) == osOK) {
			input_read();
			osMutexRelease(i2c1_mutexHandle);
			
			map_input();
			osSignalSet(screenTaskHandle, 1);
		}
		
	}
	/* USER CODE END StartInputTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
