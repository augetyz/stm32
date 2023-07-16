#include "exit_callback.h"
#include <stdio.h>

 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
    UNUSED(GPIO_Pin);
    if(GPIO_Pin==GPIO_PIN_4)
    {
        if((GPIOH->IDR&GPIO_PIN_4)==0)
        {
            while((GPIOH->IDR&GPIO_PIN_4)==0);
            GPIOI->ODR^=GPIO_PIN_8;
            printf("°´¼ü´¥·¢\n");
        }
    }
}


