#include "spi.h"
#include "delay.h"

static void SPI__BLK(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin = SPI_BLK;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //初始化GPIOA
 	GPIO_SetBits(GPIOA,SPI_BLK);
}
void SPI_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(SPI_RCC_APB2Periph_GPIO, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin = SPI_SCL|SPI_SDA|SPI_RES|SPI_DC|SPI_CS;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);	  //初始化GPIOA
 	GPIO_SetBits(SPI_GPIO,SPI_SCL|SPI_SDA|SPI_RES|SPI_DC|SPI_CS);
	SPI__BLK();
}



/******************************************************************************
      函数说明：SPI串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void SPI_Writ_Bus(u8 dat) 
{	
	u8 i;
	SPI_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		SPI_SCLK_Clr();
		if(dat&0x80)
		{
		   SPI_MOSI_Set();
		}
		else
		{
		   SPI_MOSI_Clr();
		}
		SPI_SCLK_Set();
		dat<<=1;
	}	
  SPI_CS_Set();	
}


/******************************************************************************
      函数说明：SPI写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void SPI_WR_DATA8(u8 dat)
{
	SPI_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：SPI写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void SPI_WR_DATA(u16 dat)
{
	SPI_Writ_Bus(dat>>8);
	SPI_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：SPI写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void SPI_WR_REG(u8 dat)
{
	SPI_DC_Clr();//写命令
	SPI_Writ_Bus(dat);
	SPI_DC_Set();//写数据
}










