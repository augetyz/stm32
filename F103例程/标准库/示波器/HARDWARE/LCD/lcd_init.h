#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "sys.h"

#define USE_HORIZONTAL 2  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 120
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif



//-----------------LCD端口定义---------------- 
#define RCC_APB2Periph_GPIO RCC_APB2Periph_GPIOB
#define LCD_GPIO 		GPIOB
#define LCD_SCL 	GPIO_Pin_13
#define LCD_SDA 	GPIO_Pin_15
#define LCD_RES 	GPIO_Pin_14
#define LCD_DC 		GPIO_Pin_1
#define LCD_CS 		GPIO_Pin_12
#define LCD_BLK 	GPIO_Pin_8





#define LCD_SCLK_Clr() GPIO_ResetBits(LCD_GPIO,LCD_SCL)//SCL=SCLK
#define LCD_SCLK_Set() GPIO_SetBits(LCD_GPIO,LCD_SCL)

#define LCD_MOSI_Clr() GPIO_ResetBits(LCD_GPIO,LCD_SDA)//SDA=MOSI
#define LCD_MOSI_Set() GPIO_SetBits(LCD_GPIO,LCD_SDA)

#define LCD_RES_Clr()  GPIO_ResetBits(LCD_GPIO,LCD_RES)//RES
#define LCD_RES_Set()  GPIO_SetBits(LCD_GPIO,LCD_RES)

#define LCD_DC_Clr()   GPIO_ResetBits(LCD_GPIO,LCD_DC)//DC
#define LCD_DC_Set()   GPIO_SetBits(LCD_GPIO,LCD_DC)
 		     
#define LCD_CS_Clr()   GPIO_ResetBits(LCD_GPIO,LCD_CS)//CS
#define LCD_CS_Set()   GPIO_SetBits(LCD_GPIO,LCD_CS)

#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOA,LCD_BLK)//BLK
#define LCD_BLK_Set()  GPIO_SetBits(GPIOA,LCD_BLK)




void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(u8 dat);//模拟SPI时序
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




