#ifndef __IIC_OLED_H
#define	__IIC_OLED_H
#include "stm32f10x.h"
//#include "iic_gpio.h"

#define I2C_ADDR			0x78		/* IIC设备地址 */
#define I2C_WR	0		/* 写控制bit */
#define I2C_RD	1		/* 读控制bit */
uint8_t i2c_CheckDevice(uint8_t _Address);
uint8_t OLED_CheckOk(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);
void OLED_Init(void);
void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);


#endif

