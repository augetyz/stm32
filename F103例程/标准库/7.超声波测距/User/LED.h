#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"

#define digitalToggle(p,i) {p->ODR ^=i;} 
#define TOGGLE		 digitalToggle(GPIOC,GPIO_Pin_13)

void delay_ms(u16 time);
void LED_Init(void);
void quickblink(void);
void slowblink(void);

#endif 
