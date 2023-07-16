/*
SDIO模式：是主板背面的TF卡座   该座连接的方式是 SDIO模式
SDIO接口定义   
SDIO_D0  PC8
SDIO_D1  PC9
SDIO_D2  PC10
SDIO_D3  PC11
SDIO_SCK PC12
SDIO_CMD PD2
*/
#include "iic_oled.h"
#include "iic_gpio.h"
#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "sdio_sdcard.h" 
#include  "pff.h"				  //文件系统调用.h加载
#include <stdio.h>
#include <string.h>
#include  "usart.h"
FATFS fatfs;	//文件系统结构体定义

int tbuf[512];			   //512字节 SD卡数据缓存空间


//显示BIN文件  bin文件大小为240x320
//path  bin文件名
//返回0 显示完成 1  读取失败
u8 play_bin(const char  *path)
{

FRESULT res; 
u16 br;
	
res=pf_open(path);		             //打开指定路径文件	 这一步可以打开任何路径下的文件 注意它的功能就是打开文件，不是文件夹
                                     //读文件内数据的前提是必须要打开这个文件
  if(res == FR_OK)
	{
		pf_read(tbuf,16,&br);		//上面 res=pf_open(path);打开的是指定路径下的文件，这里就可以直接读取文件的数据
	                                //从初始位置读取512个字节到缓存区  再次读取无需偏移 自动跳到下512字节
									//pf_read的特点：不仅可以读取路径下的文件数据，而在你不改变路径的前提它会自动加地址读取下面的数据
									//从程序可以看出 程序在不停的循环pf_read(tbuf, 512, &br);函数来读取512个字节，
									//那么它内部的工作就是从给的路径开始读去512个字节然后自动指向加512字节的路径，读取下512个字节直到图片显示完成
	    if(tbuf[0]<0)
			;
		else			
		OLED_ShowStr(0,2,(unsigned char*)tbuf,1);
		if(br==0){led_d2;return 0;}   	 //没有数据 br将为0  这时跳出函数	          			
	}

 return 1;  	//说明读取数据出现问题
 }  	

int main(void)
 {
	  unsigned char str[10];
	  delay_init();	    	 //延时函数初始化	 	  
      OLED_Init();
      OLED_Fill(0xFF);
	  OLED_Fill(0x00);
	  if(TFsdio_Init()==0)sprintf((char*)str,"TF Card  ok");
	  else{ sprintf((char*)str,"TF Card Error");}
	  OLED_ShowStr(0,0,str,1);
	  delay_ms(500);
	  pf_mount(&fatfs);	         //初始化petit FATFS文件系统  并提取tf卡相应数据                      
      play_bin("/cat.txt");	       //显示指定路径下的bin文件	   
                               //这是要已知存入TF卡里的路径 “/4.bin”就是在TF卡根目录下文件名为4.bin文件
							  //比如文件在文件夹 测试文件夹下的4.bin 那么就要写"/测试/4.bin"
}
	    





