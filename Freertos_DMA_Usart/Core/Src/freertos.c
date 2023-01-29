/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
SemaphoreHandle_t BinarySem_Handle =NULL;
SemaphoreHandle_t PA0_Sem_Handle =NULL;
extern uint8_t USART1_RX_Buffer[100];
extern UART_HandleTypeDef huart1;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId LED_TaskHandle;
osThreadId myTask03Handle;
osThreadId myTask04Handle;
osThreadId myTask05Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void LED_Toggle(void const * argument);
void Usart_Tx(void const * argument);
void Key_deal(void const * argument);
void Led_control(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
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
  BinarySem_Handle = xSemaphoreCreateBinary();	 
  if(NULL != BinarySem_Handle)
    printf("BinarySem_Handle二值信号量创建成功!\r\n");
  PA0_Sem_Handle = xSemaphoreCreateBinary();	 
  if(NULL != PA0_Sem_Handle)
    printf("PA0_Sem_Handle二值信号量创建成功!\r\n");
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of LED_Task */
  osThreadDef(LED_Task, LED_Toggle, osPriorityNormal, 0, 128);
  LED_TaskHandle = osThreadCreate(osThread(LED_Task), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, Usart_Tx, osPriorityHigh, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myTask04 */
  osThreadDef(myTask04, Key_deal, osPriorityRealtime, 0, 128);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

  /* definition and creation of myTask05 */
  osThreadDef(myTask05, Led_control, osPriorityAboveNormal, 0, 128);
  myTask05Handle = osThreadCreate(osThread(myTask05), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
    GPIOF->ODR^=GPIO_PIN_10;
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_LED_Toggle */
/**
* @brief Function implementing the LED_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED_Toggle */
void LED_Toggle(void const * argument)
{
  /* USER CODE BEGIN LED_Toggle */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END LED_Toggle */
}

/* USER CODE BEGIN Header_Usart_Tx */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Usart_Tx */
void Usart_Tx(void const * argument)
{
  /* USER CODE BEGIN Usart_Tx */
    BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
  /* Infinite loop */
  for(;;)
  {
    xReturn = xSemaphoreTake(BinarySem_Handle,/* 二值信号量句柄 */
                              portMAX_DELAY); /* 等待时间 */
    if(pdTRUE == xReturn)
      printf("BinarySem_Handle二值信号量获取成功!\n\n");
	TIM14->CCR1=1000-TIM14->CCR1;
    osDelay(1);
  }
  /* USER CODE END Usart_Tx */
}

/* USER CODE BEGIN Header_Key_deal */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Key_deal */
void Key_deal(void const * argument)
{
  /* USER CODE BEGIN Key_deal */
    BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
  /* Infinite loop */
  for(;;)
  {
      if(GPIOE->IDR&(1<<4))
      {
          while(GPIOE->IDR&(1<<4));
          xReturn = xSemaphoreGive( BinarySem_Handle );//给出二值信号量
          if( xReturn == pdTRUE )
            printf("BinarySem_Handle二值信号量释放成功!\r\n");
          else
            printf("BinarySem_Handle二值信号量释放失败!\r\n");
      }
      if(GPIOA->IDR&(1<<0))
      {
          while(GPIOA->IDR&(1<<0));
          xReturn = xSemaphoreGive( PA0_Sem_Handle );//给出二值信号量
          if( xReturn == pdTRUE )
            printf("PA0_Sem_Handle二值信号量释放成功!\r\n");
          else
            printf("PA0_Sem_Handle二值信号量释放失败!\r\n");
      }
    osDelay(1);
  }
  /* USER CODE END Key_deal */
}

/* USER CODE BEGIN Header_Led_control */
/**
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Led_control */
void Led_control(void const * argument)
{
  /* USER CODE BEGIN Led_control */
    BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
  /* Infinite loop */
  for(;;)
  {
    xReturn = xSemaphoreTake(PA0_Sem_Handle,/* 二值信号量句柄 */
                              portMAX_DELAY); /* 等待时间 */
    if(pdTRUE == xReturn)
      printf("PA0_Sem_Handle二值信号量获取成功!\n\n");
	printf("%s\n",USART1_RX_Buffer);
    HAL_UART_Receive_DMA(&huart1,USART1_RX_Buffer,100);
    osDelay(1);
  }
  /* USER CODE END Led_control */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
