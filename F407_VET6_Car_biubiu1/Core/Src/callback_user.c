#include "callback_user.h"
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    uint32_t Encoder_date=0;
    Encoder_date=TIM2->CNT-6720;
    TIM2->CNT=6720;
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{   
    if((GPIOA->IDR&GPIO_PIN_15)==0)
    {
        delay(10);
        if((GPIOA->IDR&GPIO_PIN_15)==0)
        {printf("key\n");
            while((GPIOA->IDR&GPIO_PIN_15)==0);
        }
    }
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    printf("USART2ok\n");
}




