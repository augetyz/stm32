#ifndef  __PWM3_H
#define  __PWM3_H
#include "systick_delay.h"

#define RCC_APB1Periph_TIM3_Def        RCC_APB1Periph_TIM3
#define RCC_APB2Periph_GPIO_TIM3_Def   RCC_APB2Periph_GPIOB
#define GPIO_Pin_TIM3_Def              GPIO_Pin_0
#define GPIO_TIM3_Def                  GPIOB
#define TIM3_Def                       TIM3
#define TIM3_OC_CH_Init                TIM_OC3Init
#define TIM3_OC_CH_PreloadConfig       TIM_OC3PreloadConfig


void TIM3_PWM_Init(u16 arr,u16 psc);

#endif
