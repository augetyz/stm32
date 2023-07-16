#include "car.h"

void M_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
 	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //使能RCC时钟

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);					 //初始化输出
		
}
//  4 2  -
//  3 1  +
void car_left(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	
}
void car_right(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}
void car_back(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_3);
}
void car_go(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_3);
	
}
void car_stop(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);
}

