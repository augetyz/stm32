#include "soft_use.h"

#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>
#include "doing.h"
#include <stdlib.h>
#include <string.h>

BJ_status BJ_biubiu;
uint8_t usart1_date[12];
extern uint8_t do_sign;
extern uint8_t x,y;
void delay(uint32_t time)
{
    uint32_t i, m;
    for (i = 0; i < time; i++)
    {
        for (m = 0; m < 36000; m++)
            ;
    }
}
void delay_us(uint32_t time)
{
    uint32_t i, m;
    for (i = 0; i < time; i++)
    {
        for (m = 0; m < 32; m++)
            ;
    }
}
int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0)
        ;
    USART1->DR = (uint8_t)ch;
    return ch;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin)
    {
    case KEY1:
        if ((GPIOB->IDR & KEY1) == 0)
        {
            delay(10);
            if ((GPIOB->IDR & KEY1) == 0)
            {
                while ((GPIOB->IDR & KEY1) == 0)
                    ;
                // do something

                switch (do_sign)
                {
                case 0:
                    BJ_move_to(0, 0, 1);
                    break;
                case 1:
                    BJ_move_to(1500, 2000, 1);
                    break;
                case 2:
                    BJ_move_to(500, 2000, 1);
                    break;
                case 3:
                    BJ_move_to(1500, 1000, 1);
                    break;
                case 4:
                    BJ_move_to(2000, 2000, 1);
                    break;
                case 5:
                    BJ_move_to(500, 200, 1);
                    break;
                default:
                    do_sign = 0;
                    break;
                }
            }
        }
        break;
    case KEY2:
        if ((GPIOA->IDR & KEY2) == 0)
        {
            delay(10);
            if ((GPIOA->IDR & KEY2) == 0)
            {
                while ((GPIOA->IDR & KEY2) == 0)
                    ;
                // do something
                if (do_sign > 6)
                    do_sign = 0;
                else
                    do_sign++;
                // BJ_move_to(1500, 2000, 1);
            }
        }
        break;
    case S_KEY1:
        break;
    case S_KEY2:
        break;
    case S_KEY3:
        break;
    case S_KEY4:
        break;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint32_t time = 0;
    if (htim->Instance == TIM1)
    {
        time++;
        if (time > 1000)
        {

            time = 0;
        }
        BJ_biubiu.coord_x[0] = -0.7071f * BJ_biubiu.BJ_now[1] + 0.7071f * BJ_biubiu.BJ_now[0];
        BJ_biubiu.coord_y[0] = 0.7071f * BJ_biubiu.BJ_now[0] + 0.7071f * BJ_biubiu.BJ_now[1];

        BJ_biubiu.coord_x[1] = 0.7071f * BJ_biubiu.BJ_now[2] + 0.7071f * BJ_biubiu.BJ_now[3];
        BJ_biubiu.coord_y[1] = 0.7071f * BJ_biubiu.BJ_now[2] - 0.7071f * BJ_biubiu.BJ_now[3];
    }
}
// 步进电机驱动定时器步进回调函数
// 这里进行步进计数、目标点查询
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{

    static uint8_t BJ_step[4] = {1, 1, 1, 1}; // 初始值为1，防止为0出bug
    if (htim->Instance == TIM2)
    {
        if (BJ_biubiu.step_goal[0] != 0) // 检测是否有任务
        {
            BJ_biubiu.step_use[0]++; // 步进
            if (BJ_step[0])
            {
                TIM2->CCR1 = 600; // 脉冲输出
                BJ_step[0] = 0;
            }
            if (BJ_biubiu.step_use[0] >= BJ_biubiu.step_goal[0]) // 检测完成
            {
                BJ_biubiu.step_use[0] = BJ_biubiu.step_goal[0] = 0; // 归零
                TIM2->CCR1 = 0;                                     // 停止输出脉冲
                BJ_step[0] = 1;
                x=1;
            }
        }
        else
            BJ_biubiu.sign_now[0] = 0;

        if (BJ_biubiu.step_goal[1] != 0)
        {
            BJ_biubiu.step_use[1]++;
            if (BJ_step[1])
            {
                TIM2->CCR2 = 600;
                BJ_step[1] = 0;
            }
            if (BJ_biubiu.step_use[1] >= BJ_biubiu.step_goal[1])
            {
                BJ_biubiu.step_use[1] = BJ_biubiu.step_goal[1] = 0;
                TIM2->CCR2 = 0;
                BJ_step[1] = 1;
                y=1;
            }
        }
        else
            BJ_biubiu.sign_now[1] = 0;

        if (BJ_biubiu.step_goal[2] != 0)
        {
            BJ_biubiu.step_use[2]++;
            if (BJ_step[2])
            {
                TIM2->CCR3 = 600;
                BJ_step[2] = 0;
            }
            if (BJ_biubiu.step_use[2] >= BJ_biubiu.step_goal[2])
            {
                BJ_biubiu.step_use[2] = BJ_biubiu.step_goal[2] = 0;
                TIM2->CCR3 = 0;
                BJ_step[2] = 1;
            }
        }
        else
            BJ_biubiu.sign_now[2] = 0;

        if (BJ_biubiu.step_goal[3] != 0)
        {
            BJ_biubiu.step_use[3]++;
            if (BJ_step[3])
            {
                TIM2->CCR4 = 600;
                BJ_step[3] = 0;
            }
            if (BJ_biubiu.step_use[3] >= BJ_biubiu.step_goal[3])
            {
                BJ_biubiu.step_use[3] = BJ_biubiu.step_goal[3] = 0;
                TIM2->CCR4 = 0;
                BJ_step[3] = 1;
            }
        }
        else
            BJ_biubiu.sign_now[3] = 0;
    }
}
void parseTwoNumbers(char *str, int *num1, int *num2)
{
    char *token;
    token = strtok(str, ",");
    *num1 = atoi(token);
    token = strtok(NULL, ",");
    *num2 = atoi(token);
}
void date_deal_usart(uint8_t *date)
{
    uint8_t i = 0, num = 0;
    int x, y;
    for (i = 0; date[i] != '\n' && i < 10; i++)
        ;
    if (i >= 12)
    {
        printf("error2\n");
        return;
    }
    date[i] = '\0';
    parseTwoNumbers(date, &x, &y);
    if (abs(x) > 4000 || abs(y) > 4000)
    {
        printf("%d,%d\n", x, y);
        x = y = 0;
        printf("error3\n");
        return;
    }
    printf("%d,%d\n", x, y);
    BJ_move_to(x, y, 1);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) // 定义 USART1 接收完成回调函数功能
{
    // date_deal_usart(usart1_date);
    static uint8_t num = 0;
    if (*(usart1_date + num) != 10)
    {
        num++;
        if (num >= 10)
        {

            printf("error1\n");
            HAL_UART_Transmit(&huart1, usart1_date, num, 100);
            num = 0;
        }
    }
    else
    {
        date_deal_usart(usart1_date);
        HAL_UART_Transmit(&huart1, usart1_date, num, 100); // 将usart1接收到的数据通过usart1发出
        num = 0;
    }
    HAL_UART_Receive_IT(&huart1, usart1_date + num, 1);
}
