#ifndef  _BSP_LED_H
#define  _BSP_LED_H

#include "stm32f10x.h"

#define LED_G_GPIO_PIN       GPIO_Pin_13
#define LED_G_GPIO_PORT      GPIOC
#define LED_G_GPIO_CLK       RCC_APB2Periph_GPIOC

#define ON   1
#define OFF  0

#define  LED_G_TOGGLE   {LED_G_GPIO_PORT->ODR ^= GPIO_Pin_13;}
#define SYSCLK_FREQ_CHAOPIN
void LED_GPIO_Config(void);
#endif  /* _BSP_LED_H */
