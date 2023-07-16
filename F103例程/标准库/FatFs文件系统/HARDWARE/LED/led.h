

#ifndef	__LED_H
#define __LED_H
#include "stm32f10x.h"

void LED_Init(void);//初始化
//void led(u8 m);

#define	led_d2  PAout(1)  //数据端口
#define	led_d3  PEout(14)  //数据端口

#endif


