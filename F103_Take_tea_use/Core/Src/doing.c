#include "doing.h"

#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "soft_use.h"
/********************************************************************************************************/ /*
 输出对象: | 电机一  |  电机二  |  电机三  |  电机四 |  LED2  |  LED3  |  LED4  |
 step控制：| PA0     |  PA1     |  PA2     |  PA3    |  PC13  |  PC14  |  PC15  |
 dir控制 ：| PA4     |  PA5     |  PB12    |  PB13   |

 输入对象  ：| KEY1  | KEY2  |  限位开关1  |  限位开关2  |  限位开关3  |  限位开关4 |
 低电平有效：| PB2   | PA8   |  PB3        |  PA11       |  PB4        |  PA12      |

 */
/********************************************************************************************************/

extern BJ_status BJ_biubiu;

void BJ_motor_Ctrl(uint8_t Motor, int speed)
{
    switch (Motor)
    {
    case 1:
        if (BJ_biubiu.sign_now[0] == 0)
        {
            if (speed < 0)
            {
                GPIOA->ODR |= GPIO_PIN_4;
                BJ_biubiu.step_goal[0] = -speed;
            }
            else
            {
                GPIOA->ODR &= ~GPIO_PIN_4;
                BJ_biubiu.step_goal[0] = speed;
            }
            BJ_biubiu.BJ_now[0] += speed;
            BJ_biubiu.step_use[0] = 0;
            BJ_biubiu.sign_now[0] = 1;
        }
        break;
    case 2:
        if (BJ_biubiu.sign_now[1] == 0)
        {
            if (speed < 0)
            {
                GPIOA->ODR |= GPIO_PIN_5;
                BJ_biubiu.step_goal[1] = -speed;
            }
            else
            {
                GPIOA->ODR &= ~GPIO_PIN_5;
                BJ_biubiu.step_goal[1] = speed;
            }
            BJ_biubiu.step_use[1] = 0;
            BJ_biubiu.sign_now[1] = 1;
            BJ_biubiu.BJ_now[1] += speed;
        }
        break;

    case 3:
        if (BJ_biubiu.sign_now[2] == 0)
        {
            if (speed < 0)
            {
                GPIOB->ODR |= GPIO_PIN_12;
                BJ_biubiu.step_goal[2] = -speed;
            }
            else
            {
                GPIOB->ODR &= ~GPIO_PIN_12;
                BJ_biubiu.step_goal[2] = speed;
            }
            BJ_biubiu.step_use[2] = 0;
            BJ_biubiu.sign_now[2] = 1;
            BJ_biubiu.BJ_now[2] += speed;
        }
        break;
    case 4:
        if (BJ_biubiu.sign_now[3] == 0)
        {
            if (speed < 0)
            {
                GPIOB->ODR |= GPIO_PIN_13;
                BJ_biubiu.step_goal[3] = -speed;
            }
            else
            {
                GPIOB->ODR &= ~GPIO_PIN_13;
                BJ_biubiu.step_goal[3] = speed;
            }
            BJ_biubiu.step_use[3] = 0;
            BJ_biubiu.sign_now[3] = 1;
            BJ_biubiu.BJ_now[3] += speed;
        }
        break;
    }
}

void BJ_move_to(int x, int y, uint8_t user)
{
    float dert = 0, distance_x = 0, distance_y = 0;
    if (user == 1)
    {
        distance_x = x - BJ_biubiu.coord_x[0];
        distance_y = BJ_biubiu.coord_y[0] - y;
        BJ_motor_Ctrl(1, 0.7071f * (distance_x - distance_y));
        BJ_motor_Ctrl(2, 0.7071f * (-distance_y - distance_x));
        
    }
    else if (user == 0)
    {
        distance_x = x - BJ_biubiu.coord_x[1];
        distance_y = y - BJ_biubiu.coord_y[1];
        BJ_motor_Ctrl(3, 0.7071f * (distance_x - distance_y));
        BJ_motor_Ctrl(4, 0.7071f * (distance_y - distance_x));
    }
}
