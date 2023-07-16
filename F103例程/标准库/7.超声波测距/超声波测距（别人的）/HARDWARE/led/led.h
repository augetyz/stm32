#ifndef _LED_H

#define _LED_H
#include "sys.h"					//LED端口定义

#define LED0 PBout(5)			//重定义，方便操作，将PB5引脚(输出状态)重定义为LED0
#define LED1 PEout(5)			//go to definition查看

void led_init(void);			//函数声明


#endif
