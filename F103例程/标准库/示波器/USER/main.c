#include "delay.h"
#include "sys.h"
#include "led.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"
#include "pwm2.h"
#include "adc.h"
#include <math.h>
#include <string.h>
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[NOFCHANEL];
int main(void)
{
	int l,m;char str[10];
	delay_init();
	ADCx_Init();
	LED_Init();//LED初始化
	LCD_Init();//LCD初始化
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
	LED=0;
	TIM2_PWM_Init(7200,100);TIM_SetCompare2(TIM2,4600);
	LCD_DrawLine(14,8,14,108,BLACK);//在指定位置画一条线	y轴
	LCD_DrawLine(14,108,154,108,BLACK);//在指定位置画一条线	x轴
	LCD_ShowChar(3,4,'y',RED,WHITE,16,1);//显示一个字符
	LCD_ShowChar(3,15,'/',RED,WHITE,16,1);//显示一个字符
	LCD_ShowChar(3,24,'v',RED,WHITE,16,1);//显示一个字符
	LCD_ShowChar(3,32,'c',RED,WHITE,16,1);//显示一个字符
	LCD_ShowChar(3,40,'c',RED,WHITE,16,1);//显示一个字符
	LCD_ShowString(154-32,128-19,"x/ms",RED,WHITE,16,0);//显示字符串
	while(1)
	{
		for(l=0;l<140;l++)
		{
			ADC_ConvertedValueLocal[0] =(float)ADC_ConvertedValue[0]/4096*3.3;
			m=(int)(ADC_ConvertedValueLocal[0]*20)+1;
			LCD_DrawPoint(15+l,90-m,BLACK);			
		}
		sprintf(str,"v:%.2f",(float)ADC_ConvertedValue[0]/4096*3.3);
		LCD_ShowString(50,128-19,str,RED,WHITE,16,0);//显示字符串
		delay_ms(1000);
		LCD_Fill(15,7,155,107,LGRAY);//指定区域填充颜色
	}
}

