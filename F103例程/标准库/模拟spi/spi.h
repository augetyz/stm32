#ifndef __SPI_H
#define __SPI_H

#include "sys.h"





//-----------------LCD端口定义---------------- 
#define SPI_RCC_APB2Periph_GPIO RCC_APB2Periph_GPIOB
#define SPI_GPIO 		GPIOB
#define SPI_SCL 	GPIO_Pin_13
#define SPI_SDA 	GPIO_Pin_15
#define SPI_RES 	GPIO_Pin_14
#define SPI_DC 		GPIO_Pin_1
#define SPI_CS 		GPIO_Pin_12
#define SPI_BLK 	GPIO_Pin_8





#define SPI_SCLK_Clr() GPIO_ResetBits(SPI_GPIO,SPI_SCL)//SCL=SCLK
#define SPI_SCLK_Set() GPIO_SetBits(SPI_GPIO,SPI_SCL)

#define SPI_MOSI_Clr() GPIO_ResetBits(SPI_GPIO,SPI_SDA)//SDA=MOSI
#define SPI_MOSI_Set() GPIO_SetBits(SPI_GPIO,SPI_SDA)

#define SPI_RES_Clr()  GPIO_ResetBits(SPI_GPIO,SPI_RES)//RES
#define SPI_RES_Set()  GPIO_SetBits(SPI_GPIO,SPI_RES)

#define SPI_DC_Clr()   GPIO_ResetBits(SPI_GPIO,SPI_DC)//DC
#define SPI_DC_Set()   GPIO_SetBits(SPI_GPIO,SPI_DC)
 		     
#define SPI_CS_Clr()   GPIO_ResetBits(SPI_GPIO,SPI_CS)//CS
#define SPI_CS_Set()   GPIO_SetBits(SPI_GPIO,SPI_CS)

#define SPI_BLK_Clr()  GPIO_ResetBits(GPIOA,SPI_BLK)//BLK
#define SPI_BLK_Set()  GPIO_SetBits(GPIOA,SPI_BLK)




void SPI_GPIO_Init(void);//初始化GPIO
void SPI_Writ_Bus(u8 dat);//模拟SPI时序
void SPI_WR_DATA8(u8 dat);//写入一个字节
void SPI_WR_DATA(u16 dat);//写入两个字节
void SPI_WR_REG(u8 dat);//写入一个指令
#endif




