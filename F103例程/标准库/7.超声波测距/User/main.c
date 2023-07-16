#include "stm32f10x.h"  
#include "LED.h"
#include "exti.h"
#include "usart.h"
#include "systick_delay.h"
#include "hc_sr04.H"
int main(void)
{
	int m; uint32_t u;double s;	
	LED_Init();
	USART1_Config();
	EXTI1_Configuration();
    EXTI_ClearFlag(EXTI_Line0);
	chaoshengbo_Config();
	printf("初始化完成\n");
	for(m=0;m<=5;m++)
	{
		Trig_Config();
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) != 1);
		SysTick_Config(720000);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1);
	    u = SysTick->VAL;
	    SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
	    s =(720000-u)/720000*10/1000*344/2*100;
	    printf("%.2fcm",s);
		SysTick_Delay_Ms(1000);
	}
	return 0;
}


