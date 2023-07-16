#include"stm32f10x.h"

int main(void)
{
  *(unsigned int *)0x40021018 |= ((1)<<4);//打开时钟。
	
  *(unsigned int *)0x40011004 |= ((1)<<(20));//PC13属于高寄存器，在官方手册中找到为20.
	
	*(unsigned int *)0x4001100C &=~(1<<13);//起始地址+偏移，使PC13端口低电。
   return 0;
}
void SystemInit(void)
{}


