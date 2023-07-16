#include "stm32f10x.h"  
#include "LED.h"
#include "exti.h"
int main(void)
{
	LED_Init();
	EXTI_Key_Config();
	while (1)
	{
	}
}


