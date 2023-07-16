#ifndef _BJ_CTRL_H_
#define _BJ_CTRL_H_

#include "main.h"
#include <stdio.h>

typedef struct {
    int16_t step[4];
    uint8_t sign[4];
}BJ_Ctrl;


#define BJ_Dir_1_GO   (GPIOA->ODR|=0X01<<4)
#define BJ_Dir_1_BACK (GPIOA->ODR&=~(0X01<<4))

#define BJ_Dir_2_GO   (GPIOA->ODR|=0X01<<5)
#define BJ_Dir_2_BACK  (GPIOA->ODR&=~(0X01<<5))

#define BJ_Dir_3_GO   (GPIOB->ODR|=0X01<<12)
#define BJ_Dir_3_BACK (GPIOB->ODR&=~(0X01<<12))

#define BJ_Dir_4_GO   (GPIOB->ODR|=0X01<<13)
#define BJ_Dir_4_BACK (GPIOB->ODR&=~(0X01<<13))

void BJ_do_step(int step,uint8_t BJ_motor);

#endif // !_BJ_CTRL_H_



