/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fashion_star_uart_servo.h"
#include "ring_buffer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t usart2SendBuf[USART_SEND_BUF_SIZE + 1];
uint8_t usart2RecvBuf[USART_RECV_BUF_SIZE + 1];
RingBufferTypeDef usart2SendRingBuf;
RingBufferTypeDef usart2RecvRingBuf;
Usart_DataTypeDef usart2;
extern uint8_t date;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t Rx_Buffer[15];
uint8_t Rx_sign=0;
int x=0,y=0;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    uint8_t color_find=0;
    uint8_t direction=0;
    float kp1=0.025,ki1=0,kp2=0.025,ki2=0;
    static float angle_x=0,angle_y=0;
    static float dert_sum[2];
    uint8_t Beep_sign=0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM9_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  usart2.pUSARTx = &huart2;
  // 初始化缓冲区(环形队列)
  RingBuffer_Init(&usart2SendRingBuf, USART_SEND_BUF_SIZE, usart2SendBuf);
  RingBuffer_Init(&usart2RecvRingBuf, USART_RECV_BUF_SIZE, usart2RecvBuf);
  usart2.recvBuf = &usart2RecvRingBuf;
  usart2.sendBuf = &usart2SendRingBuf;  
  HAL_UART_Receive_IT(&huart2, &date, 1);
  HAL_Delay(100);
  BEEP_GPIO_Port->ODR^=BEEP_Pin;
  FSUS_SetServoAngle(&usart2, 1, 0, 200, 0, 0);
  HAL_Delay(100);
  FSUS_SetServoAngle(&usart2, 2, -5, 200, 0, 0);
  LED_R_GPIO_Port->ODR^=LED_R_Pin;
  LED_G_GPIO_Port->ODR^=LED_G_Pin;
  HAL_UART_Receive_DMA(&huart1,Rx_Buffer,14);
  while(1)
  {
     
      if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0)
      {
          while(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0);
          FSUS_SetServoAngle(&usart2, 1, 30, 200, 0, 0);
          angle_x=30;
          HAL_Delay(50);
          FSUS_SetServoAngle(&usart2, 2, -10, 200, 0, 0);
          angle_y=-10;
          break;
      }
      if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==0)
      {
          while(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==0);
          FSUS_SetServoAngle(&usart2, 1, -30, 200, 0, 0);
          angle_x=-30;
          HAL_Delay(50);
          FSUS_SetServoAngle(&usart2, 2, -10, 200, 0, 0);
          angle_y=-10;
          break;
      }
      HAL_Delay(10);
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      
      if(Rx_sign)
      {
          LED_R_GPIO_Port->ODR^=LED_R_Pin;
          if(x>=3||x<=-3)
          {
              angle_x-=x*kp1+dert_sum[0]*ki1;
              dert_sum[0]+=x;
              FSUS_SetServoAngle(&usart2, 1, angle_x, 50, 0, 0);
          }
          else
          {
              dert_sum[0]=0;
              Beep_sign++;
          }
          HAL_Delay(30);
          
          if(y>=3||y<=-3)
          {
              angle_y+=y*kp2+dert_sum[1]*ki2;
              dert_sum[1]+=y;
              FSUS_SetServoAngle(&usart2, 2, angle_y, 50, 0, 0);
          }
          else
          {
              dert_sum[1]=0;    
              Beep_sign++;
          }
          
          if(Beep_sign>=2)
          {
              BEEP_GPIO_Port->ODR&=~BEEP_Pin;
              Beep_sign=0;
              LED_G_GPIO_Port->ODR&=~LED_G_Pin;
          }
          else
          {
              BEEP_GPIO_Port->ODR|=BEEP_Pin;
              
              LED_G_GPIO_Port->ODR|=LED_G_Pin;
          } 
          Rx_sign=0;
          HAL_Delay(10);
      }
      HAL_Delay(20);
     if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0)
      {
          HAL_Delay(100);
          while(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0);
          HAL_Delay(1000);
          while(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==1);
          HAL_Delay(1000);
          
      }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
