

#include "key.h"




void KEY_Init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;	 //结构体定义
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//开启GPIOA GPIOD时钟
GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_15;	//IO设置
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;		   //设置成上拉输入
GPIO_Init(GPIOA,&GPIO_InitStructure);	           //初始化GPIO

}












