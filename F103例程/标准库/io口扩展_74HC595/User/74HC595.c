#include "74HC595.h"
#include "systick_delay.h"


void IO_extend_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 

	GPIO_InitStructure.GPIO_Pin = DS_PIN|STCP_PIN|SHCP_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(PORT_74HC595, &GPIO_InitStructure);	
	GPIO_ResetBits(PORT_74HC595,DS_PIN|STCP_PIN|SHCP_PIN);
}

void SendByte_595(u32 dat)
{
	u8 i;
	/*for(i=0;i<8;i++)//八位数据判断，最大进行八个扩展
	{
		if(dat&0x80)
			DS(1);
		else
			DS(0);
		SHCP(0);
		Delay_ms(1);
		SHCP(1);
		dat<<=1;
	}*/
	/*for(i=0;i<16;i++)//十六位数据判断，最大进行十六个扩展
	{
		if(dat&0x8000)
			DS(1);
		else
			DS(0);
		SHCP(0);
		Delay_ms(1);
		SHCP(1);
		dat<<=1;
	}*/
	for(i=0;i<32;i++)//三十二位数据判断，最大进行三十二个扩展
	{
		if(dat&0x80000000)
			DS(1);
		else
			DS(0);
		SHCP(0);
		Delay_ms(1);
		SHCP(1);
		dat<<=1;
	}
	Latch_595D();
}
void Latch_595D(void) //锁存
{  
	STCP(0);
	Delay_ms(1);
	STCP(1);
}
void DS(int i)
{
	if(i)
		GPIO_SetBits(PORT_74HC595,DS_PIN);
	else
		GPIO_ResetBits(PORT_74HC595,DS_PIN);
	
}
void SHCP(int i)
{
	if(i)
		GPIO_SetBits(PORT_74HC595,SHCP_PIN);
	else
		GPIO_ResetBits(PORT_74HC595,SHCP_PIN);
}
void STCP(int i)
{
	if(i)
		GPIO_SetBits(PORT_74HC595,STCP_PIN);
	else
		GPIO_ResetBits(PORT_74HC595,STCP_PIN);
}
u32 change_up(u32 m,u8 n)//m=三十二位数，n为整数，将m的第n位置1（从右往左）
{
	m|=(1<<(n-1));
	return m;
}
u32 change_down(u32 m,u8 n)//m=三十二位数，n为整数，将m的第n位置0（从右往左）
{
	m &= ~(1<<(n-1));
	return m;
}
