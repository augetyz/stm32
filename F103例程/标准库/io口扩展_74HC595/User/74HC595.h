#ifndef __74HC595_H
#define __74HC595_H	 
#include "systick_delay.h"

#define PORT_74HC595 GPIOB
						
#define DS_PIN GPIO_Pin_0

			 
#define SHCP_PIN GPIO_Pin_9     

					 
#define STCP_PIN GPIO_Pin_8


void IO_extend_Init(void);
void SendByte_595(u32 dat);
void Latch_595D(void);
void DS(int i);
void SHCP(int i);
void STCP(int i);
u32 change_up(u32 m,u8 n);
u32 change_down(u32 m,u8 n);
#endif


