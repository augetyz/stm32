#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "uw.h"

float distance;

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	CH_SR04_Init();
	uart_init(9600);
	delay_init();
	
	while(1)
	{
		//distance=Senor_Using();
		//printf("¾àÀëÎª£º%f\n",distance);
		printf("%f\n",Senor_Using());
		delay_ms(1000);
	}
}



