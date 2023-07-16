#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"
void LED_Init(void);
#define digitalToggle(p,i) {p->ODR ^=i;} 
#define TOGGLE		 digitalToggle(GPIOA,GPIO_Pin_0)
#endif 
