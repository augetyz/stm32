
#ifndef __TFT_H
#define __TFT_H
#include "stm32f10x.h"


//快速IO
//该定义主要应用于 显示  
//能让IO在显示调用上 没有任何其他套用 直接调用IO最底层寄存器配置
//以达到 在MCU能力范围内的最快显示效果
#define	TFT_CS_1    GPIOE->BSRR=1<<0     //片选端口  	     PE0
#define	TFT_RS_1	GPIOC->BSRR=1<<4     //数据/命令         PC4	   
#define	TFT_WR_1	GPIOC->BSRR=1<<2    //写数据			 PC2
#define	TFT_RD_1	GPIOC->BSRR=1<<0    //读数据			 PC0
								    
#define	TFT_CS_0    GPIOE->BRR=1<<0      //片选端口  	     PE0
#define	TFT_RS_0	GPIOC->BRR=1<<4      //数据/命令         PC4	   
#define	TFT_WR_0	GPIOC->BRR=1<<2     //写数据			 PC2
#define	TFT_RD_0	GPIOC->BRR=1<<0     //读数据			 PC0



void TFT_CS(u8 d);

void Lcd_Init(void);


void Lcd_Write_Data(u16 data);								 //写16位数据

void Address_set(u16 x1,u16 y1,u16 x2,u16 y2,u16 xq,u16 yq);    //设置显示范围




//屏幕尺寸
#define TFT_XMAX       239
#define TFT_YMAX       319




#endif






