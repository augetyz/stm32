#include "stm32f10x.h"  
#include "LED.h"
#include "usart.h"
#include "car.h"
int main(void)
{
	LED_Init();
	USART1_Config();
    M_Init();
    while(1)
    {}
}


