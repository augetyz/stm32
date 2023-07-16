#ifndef _SYSTICK_DELAY_H
#define _SYSTICK_DELAY_H

#include "stm32f10x.h"

void SysTick_Init(void);
#define Delay_us(x) SysTick_Delay_Us(x);
#define Delay_ms(x) SysTick_Delay_Ms(x);	 //µ¥Î»ms
#define delay_us(x) SysTick_Delay_Us(x);
#define delay_ms(x) SysTick_Delay_Ms(x);
void SysTick_Delay_Us( __IO uint32_t us);
void SysTick_Delay_Ms( __IO uint32_t ms);

#endif 
