#ifndef _LED_H
#define _LED_H

#define digitalToggle(p,i) {p->ODR ^=i;} 
#define TOGGLE		 digitalToggle(GPIOC,GPIO_Pin_13)

#include "stm32f10x.h"
void LED_Init(void);

#endif 
