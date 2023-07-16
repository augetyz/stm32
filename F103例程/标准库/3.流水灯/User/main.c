#include "stm32f10x.h" 
#include "led.h"
int main(void)
{
	LED_Init();
	while(1)
	{
		LED_Light();
	}

}


