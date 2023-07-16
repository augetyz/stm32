#include "hc_sr04.h"
void chaoshengbo_Config(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
 	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	 //使能RCC时钟

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
		GPIO_Init(GPIOB, &GPIO_InitStructure);					 //初始化输出
	    GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}

void Trig_Config(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	
	SysTick_Delay_Us(20);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}

