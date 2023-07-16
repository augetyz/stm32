#include "stm32f10x.h"  
#define LED_GPIO_PORT GPIOC
#define LED_GPIO_CLK RCC_APB2Periph_GPIOC
#define LED_GPIO_PIN GPIO_Pin_13
#define digitalLo(p,i) {p->BRR=i;}
#define LED_ON digitalLo(LED_GPIO_PORT,LED_GPIO_PIN)
int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( LED_GPIO_CLK, ENABLE);
   GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
	LED_ON;
	return 0;
}


