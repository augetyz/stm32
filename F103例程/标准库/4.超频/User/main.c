#include "stm32f10x.h" 
#include "led.h"
int main(void)
{
	LED_Init();
	HSE_SetSysClock( RCC_PLLMul_9);

	while(1)
	{
		LED_Light();
	}

}


