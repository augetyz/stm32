#ifndef _TIM1_H
#define _TIM1_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#define BASIC_TIM2

#ifdef  BASIC_TIM2
#define            BASIC_TIM                   TIM2
#define            BASIC_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM_CLK               RCC_APB1Periph_TIM2
#define            BASIC_TIM_Period            (500-1)
#define            BASIC_TIM_Prescaler         71
#define            BASIC_TIM_IRQ               TIM2_IRQn
#define            BASIC_TIM_IRQHandler        TIM2_IRQHandler

#else  // 使用基本定时器TIM7
#define            BASIC_TIM                   TIM7
#define            BASIC_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM_CLK               RCC_APB1Periph_TIM7
#define            BASIC_TIM_Period            1000-1
#define            BASIC_TIM_Prescaler         71
#define            BASIC_TIM_IRQ               TIM7_IRQn
#define            BASIC_TIM_IRQHandler        TIM7_IRQHandler

#endif

void BASIC_TIM_Init(void);

#endif

