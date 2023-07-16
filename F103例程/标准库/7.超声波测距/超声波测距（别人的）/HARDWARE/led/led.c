#include"led.h"

void led_init(void)
{
	GPIO_InitTypeDef GPIO_Init_Structure;  //定义结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);		//配置GPIO时钟
	
	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_5;
	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;		//配置结构体内容(见stm32f10x_gpio.c和stm32f10x_gpio.c)
	GPIO_Init_Structure.GPIO_Mode=GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOB,&GPIO_Init_Structure);			//GPIO端口与结构体对应
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOE,&GPIO_Init_Structure);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
}
