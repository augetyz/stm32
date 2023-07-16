#include "stm32f10x.h"  
#include "LED.h"
#include "74HC595.h"
int main(void)
{
	u32 i;
	LED_Init();
	SysTick_Init();
	IO_extend_Init();
	i=change_up(change_up(change_up(change_up(change_up(0,5),7),8),13),15);
	SendByte_595(~0xffffab2b);
}


