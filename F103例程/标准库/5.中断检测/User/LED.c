 #include "LED.h"
 
void LED_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
 	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	 //使能RCC时钟

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
		GPIO_Init(GPIOC, &GPIO_InitStructure);					 //初始化输出
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);// 输出低电平
}
void delay_ms(u16 time)

{

u16 i=0;

while(time--)

{

i=1000;  

while(i--) ;

}

}
void quickblink(void)
{
  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
  delay_ms(1000);
	TOGGLE;
}
	
void slowblink(void)
{
  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
  delay_ms(1000);
	TOGGLE;
}
