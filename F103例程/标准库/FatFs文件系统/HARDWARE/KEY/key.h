

#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"

#define S2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)			   //宏定义 为采集数据做准备
#define S3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)

void KEY_Init(void);//IO初始化



#endif
