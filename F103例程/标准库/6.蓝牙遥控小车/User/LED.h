#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"
void LED_Init(void);
void delay_ms(u16 time);
#define digitalToggle(p,i) {p->ODR ^=i;} 
#define TOGGLE		 digitalToggle(GPIOC,GPIO_Pin_13)

#endif 

