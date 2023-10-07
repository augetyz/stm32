/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dma.h"
#include "usart.h"
#include "fashion_star_uart_servo.h"
#include "ring_buffer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define Back_X_Start 1665 
#define Back_X_End   1330 

#define Back_Y_Start 1338
#define Back_Y_End   1646

#define Black_X_Start 1525 
#define Black_X_End   1334

#define Black_Y_Start 1338
#define Black_Y_End   1460

#define Back_Center_x   1488
#define Back_Center_y   1480 //1645

#define X TIM3->CCR1
#define Y TIM3->CCR2

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t time; 
}Servo_date;
typedef struct {
    int point_coord[4][2];
}point_date;
typedef struct {
    int point[2];
}red_point;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t usart_1_date[40] = {0};
uint8_t biu=0;
extern Usart_DataTypeDef usart2;

uint16_t x_biu=Back_Center_x,y_biu=Back_Center_y;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
QueueHandle_t   servo_Queue =NULL;
QueueHandle_t   point_Queue =NULL;
QueueHandle_t   redpoint_Queue =NULL;
SemaphoreHandle_t usart1_RX_Sem_Handle = NULL;
SemaphoreHandle_t Black_line_Sem_Handle = NULL;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId OLED_TaskHandle;
osThreadId Uart_TaskHandle;
osThreadId Servo_TaskHandle;
osThreadId LED_TaskHandle;
osThreadId KEY_TaskHandle;
osThreadId Black_line_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void Servo_Ctrl(uint16_t x,uint16_t y,uint16_t time);
uint8_t point_do(int16_t x,int16_t y,int16_t a,int16_t b);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void OLED_Task_fucation(void const * argument);
void Uart_Task_Function(void const * argument);
void Servo_Task_Function(void const * argument);
void LED_Task_Function(void const * argument);
void KEY_Task_Function(void const * argument);
void Black_line_Function(void const * argument);

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
    servo_Queue = xQueueCreate((UBaseType_t ) 1,/* 消息队列的长度 */
                            (UBaseType_t ) sizeof(Servo_date));/* 消息的大小 */
    point_Queue = xQueueCreate((UBaseType_t ) 1,/* 消息队列的长度 */
                            (UBaseType_t ) sizeof(point_date));/* 消息的大小 */
    redpoint_Queue = xQueueCreate((UBaseType_t ) 1,/* 消息队列的长度 */
                            (UBaseType_t ) sizeof(red_point));/* 消息的大小 */                        
    usart1_RX_Sem_Handle  = xSemaphoreCreateBinary();
    
    Black_line_Sem_Handle = xSemaphoreCreateBinary();
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of OLED_Task */
  osThreadDef(OLED_Task, OLED_Task_fucation, osPriorityIdle, 0, 256);
  OLED_TaskHandle = osThreadCreate(osThread(OLED_Task), NULL);

  /* definition and creation of Uart_Task */
  osThreadDef(Uart_Task, Uart_Task_Function, osPriorityNormal, 0, 256);
  Uart_TaskHandle = osThreadCreate(osThread(Uart_Task), NULL);

  /* definition and creation of Servo_Task */
  osThreadDef(Servo_Task, Servo_Task_Function, osPriorityIdle, 0, 256);
  Servo_TaskHandle = osThreadCreate(osThread(Servo_Task), NULL);

  /* definition and creation of LED_Task */
  osThreadDef(LED_Task, LED_Task_Function, osPriorityIdle, 0, 128);
  LED_TaskHandle = osThreadCreate(osThread(LED_Task), NULL);

  /* definition and creation of KEY_Task */
  osThreadDef(KEY_Task, KEY_Task_Function, osPriorityAboveNormal, 0, 128);
  KEY_TaskHandle = osThreadCreate(osThread(KEY_Task), NULL);

  /* definition and creation of Black_line_Task */
  osThreadDef(Black_line_Task, Black_line_Function, osPriorityNormal, 0, 256);
  Black_line_TaskHandle = osThreadCreate(osThread(Black_line_Task), NULL);

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
      LED_R_GPIO_Port->ODR^=LED_R_Pin;
        osDelay(100);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_OLED_Task_fucation */
/**
* @brief Function implementing the OLED_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OLED_Task_fucation */
void OLED_Task_fucation(void const * argument)
{
  /* USER CODE BEGIN OLED_Task_fucation */
  /* Infinite loop */
  for(;;)
  {

        osDelay(1);
  }
  /* USER CODE END OLED_Task_fucation */
}

/* USER CODE BEGIN Header_Uart_Task_Function */
/**
* @brief Function implementing the Uart_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Uart_Task_Function */
void Uart_Task_Function(void const * argument)
{
  /* USER CODE BEGIN Uart_Task_Function */
  /* Infinite loop */
    int i=0,num,sign=0,date_long=18,Rx_long=38,num_black=0;

    static point_date Point_coord;
    static red_point Red_point;
    static int last_x,last_y;
    HAL_UART_Receive_DMA(&huart1, usart_1_date, Rx_long); 
  for(;;)
  {
    if(xSemaphoreTake(usart1_RX_Sem_Handle, 100)==pdTRUE) /* 等待时间 */
    {
        vTaskSuspendAll();
          for(i=0;i<date_long;i++)
          {
              if(usart_1_date[i]==0X2C)
              {
                  num=i;
                  if(usart_1_date[num+1]==0X12)
                  {
                      if(Rx_long==38)
                        sign=1;
                      else
                      {
                          sign=0;
                          Rx_long=38;
                          date_long=18;
                      }
                    
                  }
                  else if(usart_1_date[num+1]==0X21)
                  {
                      sign=2;
                      date_long=7;
                      Rx_long=14;
                  }
                  else
                    sign=0;
                  break;              
              }
              LED_G_GPIO_Port->ODR&=~LED_G_Pin;
              sign=0;
          }         
          xTaskResumeAll();

          if(sign==1)
          {
              
              LED_G_GPIO_Port->ODR|=LED_G_Pin;
              
              Point_coord.point_coord[0][0]=(int)(((int)usart_1_date[i+3]<<8) + (int)usart_1_date[i+2]);
              if(Point_coord.point_coord[0][0]>500)
                  Point_coord.point_coord[0][0]|=0XFFFF0000;
              Point_coord.point_coord[0][1]=(int)(((int)usart_1_date[i+5]<<8) + (int)usart_1_date[i+4]);
              if(Point_coord.point_coord[0][1]>500)
                  Point_coord.point_coord[0][1]|=0XFFFF0000;       
              Point_coord.point_coord[1][0]=(int)(((int)usart_1_date[i+7]<<8) + (int)usart_1_date[i+6]);
              if(Point_coord.point_coord[1][0]>500)
                  Point_coord.point_coord[1][0]|=0XFFFF0000;
              Point_coord.point_coord[1][1]=(int)(((int)usart_1_date[i+9]<<8) + (int)usart_1_date[i+8]); 
                if(Point_coord.point_coord[1][1]>500)
                   Point_coord.point_coord[1][1]|=0XFFFF0000;              
              Point_coord.point_coord[2][0]=(int)(((int)usart_1_date[i+11]<<8) + (int)usart_1_date[i+10]);
                if(Point_coord.point_coord[2][0]>500)
                                  Point_coord.point_coord[2][0]|=0XFFFF0000;
              Point_coord.point_coord[2][1]=(int)(((int)usart_1_date[i+13]<<8) + (int)usart_1_date[i+12]);
                if(Point_coord.point_coord[2][1]>500)
                                  Point_coord.point_coord[2][1]|=0XFFFF0000;
              Point_coord.point_coord[3][0]=(int)(((int)usart_1_date[i+15]<<8) + (int)usart_1_date[i+14]);
                if(Point_coord.point_coord[3][0]>500)
                                  Point_coord.point_coord[3][0]|=0XFFFF0000;
              Point_coord.point_coord[3][1]=(int)(((int)usart_1_date[i+17]<<8) + (int)usart_1_date[i+16]);
                if(Point_coord.point_coord[3][1]>500)
                                  Point_coord.point_coord[3][1]|=0XFFFF0000;
               
              xQueueSend(point_Queue,&Point_coord,0);
                
                num_black++;
                
                if(num_black>40)
                {
                    num_black=0;
                    Linux_GPIO_Port->ODR&=~Linux_Pin;
                    BEEP_GPIO_Port->ODR^=BEEP_Pin;
                    osDelay(200);
                    BEEP_GPIO_Port->ODR^=BEEP_Pin;
                    osDelay(200);
                    BEEP_GPIO_Port->ODR^=BEEP_Pin;
                    osDelay(200);
                    BEEP_GPIO_Port->ODR^=BEEP_Pin;
                    osDelay(200);
                }

          } 
          if(sign==2)
          {
              Red_point.point[0]=(int)(((int)usart_1_date[i+3]<<8) + (int)usart_1_date[i+2]);
              if(Red_point.point[0]>500)
                  Red_point.point[0]|=0XFFFF0000;
              Red_point.point[1]=(int)(((int)usart_1_date[i+5]<<8) + (int)usart_1_date[i+4]);
              if(Red_point.point[1]>500)
                  Red_point.point[1]|=0XFFFF0000;
              if(abs(last_x-Red_point.point[0])>150||abs(last_y-Red_point.point[1])>150)
                       LED_G_GPIO_Port->ODR&=~LED_G_Pin;
                else   
                {
                    xQueueSend(redpoint_Queue,&Red_point,0);
                    last_x=Red_point.point[0];
                    last_y=Red_point.point[1];
                    LED_G_GPIO_Port->ODR|=LED_G_Pin; 
                }

                
          }              

        HAL_UART_Receive_DMA(&huart1, usart_1_date, Rx_long);
    }
    else   
    LED_G_GPIO_Port->ODR&=~LED_G_Pin;    
    osDelay(1);
  }
  /* USER CODE END Uart_Task_Function */
}

/* USER CODE BEGIN Header_Servo_Task_Function */
/**
* @brief Function implementing the Servo_Task thread.
* @param argument: Not used
* @retval None
*/
#define num_use 12
/* USER CODE END Header_Servo_Task_Function */
void Servo_Task_Function(void const * argument)
{
  /* USER CODE BEGIN Servo_Task_Function */
  /* Infinite loop */
    X=Back_Center_x;
    Y=Back_Center_y;
    static Servo_date servo;
    float angle[2];
    uint16_t time_use, i = 0;
  for(;;)
  {
    xQueueReceive( servo_Queue,&servo,portMAX_DELAY);
    time_use = servo.time / num_use;
      angle[0]=((int)servo.x-(int)X)/num_use;
      angle[1]=((int)servo.y-(int)Y)/num_use;
      for(i=0;i<num_use;i++)
      {
          X+=angle[0];
          Y+=angle[1];
          osDelay(time_use);
      }
      X=servo.x;
      Y=servo.y;
      osDelay(100);
      
  }
  /* USER CODE END Servo_Task_Function */
}

/* USER CODE BEGIN Header_LED_Task_Function */
/**
* @brief Function implementing the LED_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED_Task_Function */
void LED_Task_Function(void const * argument)
{
  /* USER CODE BEGIN LED_Task_Function */
  /* Infinite loop */
    red_point Red_cood;
    static point_date Point_coord;
    static point_date Point_coord2;
    uint8_t point_select=0;
  for(;;)
  {
      if(biu==0)
      {
          xSemaphoreTake(Black_line_Sem_Handle,portMAX_DELAY);
          xQueueReceive( point_Queue,&Point_coord,portMAX_DELAY);
          
          Point_coord2.point_coord[0][0]=(Point_coord.point_coord[0][0]+Point_coord.point_coord[1][0])/2;
          Point_coord2.point_coord[0][1]=(Point_coord.point_coord[0][1]+Point_coord.point_coord[1][1])/2;
          Point_coord2.point_coord[1][0]=(Point_coord.point_coord[1][0]+Point_coord.point_coord[2][0])/2;
          Point_coord2.point_coord[1][1]=(Point_coord.point_coord[1][1]+Point_coord.point_coord[2][1])/2;
          Point_coord2.point_coord[2][0]=(Point_coord.point_coord[2][0]+Point_coord.point_coord[3][0])/2;
          Point_coord2.point_coord[2][1]=(Point_coord.point_coord[2][1]+Point_coord.point_coord[3][1])/2;
          Point_coord2.point_coord[3][0]=(Point_coord.point_coord[3][0]+Point_coord.point_coord[0][0])/2;
          Point_coord2.point_coord[3][1]=(Point_coord.point_coord[3][1]+Point_coord.point_coord[0][1])/2;
      }
      xQueueReceive( redpoint_Queue,&Red_cood,portMAX_DELAY);
//      vTaskSuspendAll();
       switch(point_select) 
       {
           case 1:
               if(point_do(Red_cood.point[0],Red_cood.point[1],Point_coord2.point_coord[0][0],Point_coord2.point_coord[0][1])==1)
               {
//                   xTaskResumeAll();
                   osDelay(100);
                   point_select++;
               }
               break;
           case 0:
               if(point_do(Red_cood.point[0],Red_cood.point[1],Point_coord.point_coord[0][0],Point_coord.point_coord[0][1])==1)
               {
//                   xTaskResumeAll();
                   osDelay(100);
                   point_select++;

               }
               break;
           case 3:
               if(point_do(Red_cood.point[0],Red_cood.point[1],Point_coord2.point_coord[1][0],Point_coord2.point_coord[1][1])==1)
               {
//                   xTaskResumeAll();
                   osDelay(100);
                   point_select++;
               }
               break;
           case 2:
               if(point_do(Red_cood.point[0],Red_cood.point[1],Point_coord.point_coord[1][0],Point_coord.point_coord[1][1])==1)
               {
//                   xTaskResumeAll();
                   osDelay(100);
                   point_select++;

               }
               break;
           case 5:
               if(point_do(Red_cood.point[0],Red_cood.point[1],Point_coord2.point_coord[2][0],Point_coord2.point_coord[2][1])==1)
               {
//                   xTaskResumeAll();
                   osDelay(100);
                   point_select++;
               }
               break;    
           case 4:
               if(point_do(Red_cood.point[0],Red_cood.point[1],Point_coord.point_coord[2][0],Point_coord.point_coord[2][1])==1)
               {
//                   xTaskResumeAll();
                   osDelay(100);
                   point_select++;

               }
               break;
           case 7:
               if(point_do(Red_cood.point[0],Red_cood.point[1],Point_coord2.point_coord[3][0],Point_coord2.point_coord[3][1])==1)
               {
//                   xTaskResumeAll();
                   osDelay(100);
                   point_select++;
               }
               break;    
           case 6:
               if(point_do(Red_cood.point[0],Red_cood.point[1],Point_coord.point_coord[3][0],Point_coord.point_coord[3][1])==1)
               {
//                   xTaskResumeAll();
                   osDelay(100);
                   point_select++;

               }
               break;
           
           default:
//               xTaskResumeAll();
               point_select=0;
//               biu=0; 
               break;
       }
//       xTaskResumeAll();
      osDelay(120);
  }
  /* USER CODE END LED_Task_Function */
}

/* USER CODE BEGIN Header_KEY_Task_Function */
/**
* @brief Function implementing the KEY_Task thread.
* @param argument: Not used
* @retval None
*/

/* USER CODE END Header_KEY_Task_Function */
void KEY_Task_Function(void const * argument)
{
  /* USER CODE BEGIN KEY_Task_Function */
  /* Infinite loop */
    point_date Point_coord;
    
  for(;;)
  {
      xQueueReceive( point_Queue,&Point_coord,10);
      if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0)
      {
          while(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0);
         
          Servo_Ctrl(Back_X_Start,Back_Y_Start,2000);
          osDelay(2000);
          Servo_Ctrl(Back_X_End,Back_Y_Start,2000);
          osDelay(2000); 
          Servo_Ctrl(Back_X_End,Back_Y_End,2000);
          osDelay(2000); 
          Servo_Ctrl(Back_X_Start,Back_Y_End,2000);
          osDelay(2000);
          Servo_Ctrl(Back_X_Start,Back_Y_Start,2000);
          osDelay(2000);
      }
      if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0)
      {
          osDelay(10);
          while(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0);

          osDelay(1000);
            
          xSemaphoreGive(Black_line_Sem_Handle);
          xQueueSend(point_Queue,&Point_coord,0);
          biu=1;
      }
      //key3
      if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==0)
      {
          osDelay(10);
          while(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==0);
          Servo_Ctrl(Black_X_End,Black_Y_Start,2000);
          osDelay(2000);
          Servo_Ctrl(Black_X_End,Black_Y_End,2000);
          osDelay(2000); 
          Servo_Ctrl(Black_X_Start,Black_Y_End,2000);
          osDelay(2000); 
          Servo_Ctrl(Black_X_Start,Black_Y_Start,2000);
          osDelay(2000);
          Servo_Ctrl(Black_X_End,Black_Y_Start,2000);
          osDelay(2000);
      }
      //key4
      if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==0)
      {
          
          osDelay(10);
          while(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==0);   
          osDelay(100);
          while(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==1);  
          osDelay(1000);
      }
    osDelay(1);
  }
  /* USER CODE END KEY_Task_Function */
}

/* USER CODE BEGIN Header_Black_line_Function */
/**
* @brief Function implementing the Black_line_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Black_line_Function */
void Black_line_Function(void const * argument)
{
  /* USER CODE BEGIN Black_line_Function */
  /* Infinite loop */
    point_date Point_coord;
  for(;;)
  {
//      xSemaphoreTake(Black_line_Sem_Handle,portMAX_DELAY);
//      if(biu==1)
//      {
//          xQueueReceive( point_Queue,&Point_coord,portMAX_DELAY);
//          xQueueReceive( point_Queue,&Point_coord,portMAX_DELAY);
//          Servo_Ctrl(Back_Center_x + 3 - 1.44f *(float) Point_coord.point_coord[0][0],Back_Center_y - 3 - 1.20f * (float)Point_coord.point_coord[0][1],2000);
//          osDelay(3000);
//          Servo_Ctrl(Back_Center_x + 3 - 1.44f *(float) Point_coord.point_coord[1][0],Back_Center_y- 3 - 1.20f * (float)Point_coord.point_coord[1][1],2000);
//          osDelay(3000);
//          Servo_Ctrl(Back_Center_x + 3 - 1.44f *(float) Point_coord.point_coord[2][0],Back_Center_y- 3 - 1.20f * (float)Point_coord.point_coord[2][1],2000);
//          osDelay(3000);
//          Servo_Ctrl(Back_Center_x + 3 - 1.44f *(float) Point_coord.point_coord[3][0],Back_Center_y- 3 - 1.20f * (float)Point_coord.point_coord[3][1],2000);
//          osDelay(3000);
//          Servo_Ctrl(Back_Center_x + 3 - 1.44f *(float) Point_coord.point_coord[0][0],Back_Center_y - 3 - 1.20f * (float)Point_coord.point_coord[0][1],2000);
//          osDelay(3000);
//          biu=0;
//      }
      osDelay(100);
  }
  /* USER CODE END Black_line_Function */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void Servo_Ctrl(uint16_t x,uint16_t y,uint16_t time)
{
    Servo_date Servo;
    Servo.x=x;
    Servo.y=y;
    Servo.time=time;
    xQueueSend(servo_Queue,&Servo,0);
}
uint8_t point_do(int16_t x,int16_t y,int16_t a,int16_t b)
{

    static float K=0,d=0,out_x=0,out_y=0;
    
    int sign=0;
    float kp1=0.2,ki1=0.01,kp2=0.1,kp3=0.15,kp4=0.2,ki2=0.01;
    

    out_x=kp1*(a-x);
    out_y=kp1*(b-y);
    
    
    if(abs(a-x)>3)
    {
        X-=out_x;
    }
    else
        sign++;

    if(abs(b-y)>2)
    {
        Y+=out_y;
    }
    else
        sign++;
    if(sign==2)
    {
        return 1;
    }
    else
        return 0;

    
}
/* USER CODE END Application */

