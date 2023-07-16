#include "stm32f10x.h"  
#include "LED.h"
#include "tim1.h"
 int m ,n,i;

int main(void)
{
	extern int m ,n;
	m=0;i=1;
	n=1;
	LED_Init();
	BASIC_TIM_Init();
	while(1);
}


