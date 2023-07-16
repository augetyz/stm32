#include "delay.h"
#include "uw.h"


uint overcount=0;


void CH_SR04_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructer;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructer;
	NVIC_InitTypeDef NVIC_InitStructer;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/*TRIG*/
	GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructer.GPIO_Pin=GPIO_Pin_6;
	GPIO_Init(GPIOB, &GPIO_InitStructer);

	/*ECOH*/
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructer.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOB, & GPIO_InitStructer);

	/*TIM2*/
	TIM_DeInit(TIM2);
	TIM_TimeBaseInitStructer.TIM_Period=999;
	TIM_TimeBaseInitStructer.TIM_Prescaler=71; 
	TIM_TimeBaseInitStructer.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructer.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructer);

	//TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );
	
	NVIC_InitStructer.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructer.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructer.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructer.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructer);

	TIM_Cmd(TIM2, DISABLE);
}



float Senor_Using(void)				//·µ»Ø¾àÀëÖµ
{
	float length=0,sum=0;
	u16 tim;
	uint i=0;
	
	while(i!=5)
	{
		PBout(6)=1; 
		delay_us(20); 
		PBout(6)=0;
		
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==RESET);
		TIM_Cmd(TIM2,ENABLE);

	i+=1;
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==SET);
	TIM_Cmd(TIM2,DISABLE);

	tim=TIM_GetCounter(TIM2);

	length=(tim+overcount*1000)/58.0;
	//length=(tim+overcount*1000)*0.0001*340/2;
	sum=length+sum;
	TIM2->CNT=0; 
	overcount=0; 
	//delay_ms(100);
	}
	length=sum/5;
	return length;
}


void TIM2_IRQHandler(void) 
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		overcount++;

  }
}
