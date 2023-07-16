#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include "main.h"
#include <stdio.h>




void delay(uint32_t time);
void delay_us(uint32_t time);
void Usart_SendString(uint8_t *str);
void clearArray(uint8_t * array,uint16_t length);

#endif // !_CALLBACK_H_

