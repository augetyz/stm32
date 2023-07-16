#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "wkup.h"
#include "TIM.h"
#include "bsp_adc.h"
uint32_t time = 0;

u8 sign=0;
// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[NOFCHANEL];
/*****************************************************/
//开机关机键：PA0
//长按信号键：PB2
//短按信号键：PE3
//X轴：PA2
//Y轴：PA1
/*****************************************************/



 int main(void)
 {	 
	float x,y;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	BASIC_TIM_Init();//定时器初始化
	Key1_Init();
	Key2_Init();
	delay_ms(30);
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化	
	ADCx_Init();
	WKUP_Init(); //待机唤醒初始化
	while(1)
	{
		LED0=!LED0;
		delay_ms(250);
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
		ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
		x=1.66-ADC_ConvertedValueLocal[2];
		y=1.66-ADC_ConvertedValueLocal[1];
		if(x>0)
			printf("X轴：左     ");
		else
			printf("X轴：右     ");
		if(y>0)
			printf("Y轴：前\n");
		else
			printf("Y轴：后\n");
	}
 }

void EXTI2_IRQHandler(void)
{ 	
    int16_t t1=0;	
	EXTI_ClearITPendingBit(EXTI_Line2); // 清除LINE10上的中断标志位		
	if(KEY1==1)
		t1=TIM6->CNT;
	printf("%d",t1);
	while(KEY1);
	t1=TIM6->CNT-t1;
	printf("       %d\n",t1);
	if(t1>6000)
		if(sign)
		{
			printf("#################################\n");//信息1自定义*************************
			sign=0;
		}
		else
		{
			printf("#################################\n");//信息2自定义*************************
			sign=1;
		}
		
}
void EXTI3_IRQHandler(void)
{ 		    		    				     		    
	if(KEY2==1)
	{	
		delay_ms(10);	
		if(KEY2==1)
		{		  
			printf("**************************************\n");//信息自定义*************************
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line3); 
}
