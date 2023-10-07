#include "soft_user.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;


__IO uint32_t sysTickCnt;

void delay(uint32_t time)
{
    uint32_t i, m;
    for (i = 0; i < time; i++)
    {
        for (m = 0; m < 21000; m++)
            ;
    }
}
void delay_us(uint32_t time)
{
    uint32_t i, m;
    for (i = 0; i < time; i++)
    {
        for (m = 0; m < 21; m++)
            ;
    }
}
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100);
    return (ch);
}
void Usart_SendByte(UART_HandleTypeDef *pUSARTx, uint8_t ch)
{
    /* 发送一个字节到USART */
    HAL_UART_Transmit(pUSARTx, (uint8_t *)&ch, 1, 100);
}
// 将串口发送缓冲区的内容全部发出去
void Usart_SendAll(Usart_DataTypeDef *usart)
{
    uint8_t value;
    while (RingBuffer_GetByteUsed(usart->sendBuf))
    {
        value = RingBuffer_Pop(usart->sendBuf);
        // printf("Usart_SendAll pop: %d", value);
        Usart_SendByte(usart->pUSARTx, value);
    }
}



void clearArray(uint8_t *array, uint16_t length)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        array[i] = 0;
    }
}

// 等待计时完成
void SysTick_Wait()
{
    // 定时器使能
    TIM6->CR1 |= TIM_CR1_CEN;
    //	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    // 等待直到计时器变为0
    while (sysTickCnt > 0)
        ;
    // 定时器失能
    //	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    TIM6->CR1 &= (uint16_t)~TIM_CR1_CEN;
}

// 延时us
void SysTick_DelayUs(__IO uint32_t nTime)
{
    // 设置时钟中断为us级
    //    SysTick_Config(SystemCoreClock / 1000000);
    TIM6->PSC = 71;
    sysTickCnt = nTime;
    // 等待计时完成
    SysTick_Wait();
    // 重新设置系统中断为ms级
    TIM6->PSC = 71999;
    // 定时器失能
    TIM6->CR1 &= (uint16_t)~TIM_CR1_CEN;
}

// 延时ms
void SysTick_DelayMs(__IO uint32_t nTime)
{
    sysTickCnt = nTime;
    SysTick_Wait();
}

// 延时s
void SysTick_DelayS(__IO uint32_t nTime)
{
    SysTick_DelayMs(nTime * 1000);
}

// 设置倒计时(非阻塞式)
void SysTick_CountdownBegin(__IO uint32_t nTime)
{
    // 这里设置为1ms中断一次
    sysTickCnt = nTime;
    // 定时器使能
    TIM6->CR1 |= TIM_CR1_CEN;
}

// 撤销倒计时
void SysTick_CountdownCancel(void)
{
    // 重置嘀嗒计时器的计数值
    sysTickCnt = 0;
    // systick 定时器失能
    TIM6->CR1 &= (uint16_t)~TIM_CR1_CEN;
}

// 判断倒计时是否超时
uint8_t SysTick_CountdownIsTimeout(void)
{
    return sysTickCnt == 0;
}


