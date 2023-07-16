#include "stm32f10x.h"  
#include "systick_delay.h"
#include "iic_oled.h"

extern const unsigned char BMP1[];
extern const unsigned char love[];
extern const unsigned char shiping1[];
extern const unsigned char shiping2[];
extern const unsigned char shiping3[];
extern const unsigned char gImage_cat[];
int main()
{
	OLED_Init();
	OLED_Fill(0xFF);Delay_ms(1000);
	OLED_Fill(0x00);//È«ÆÁÃð
	Delay_ms(1000);
	OLED_DrawBMP(0,0,102,8,(unsigned char *)gImage_cat);
	
}



