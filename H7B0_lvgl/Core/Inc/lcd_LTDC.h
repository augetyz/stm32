#ifndef _LCD_LTDC_H_
#define _LCD_LTDC_H_

#include "main.h"
#include "stm32h7xx_hal.h"


// layer0 的显存地址，本例程使用7B0内部的AXI SRAM作为显存，起始地址0x24000000，大小为1M
// layer0 显存大小等于 = LCD_Width * LCD_Width * BytesPerPixel_0（每个像素所占字节大小）
// 因为 AXI SRAM 的大小只有1M，用户设置的区域一定不能超过这个值！
// 在本例程中，800*480的屏幕，使用RGB565格式，需要显存 800*480*2 = 768000 字节
#define LCD_MemoryAdd 0x24000000            //	显存的起始地址
#define LCD_Width 800                       //	LCD的像素长度
#define LCD_Height 480                      //	LCD的像素宽度
#define Color_Mode LTDC_PIXEL_FORMAT_RGB565 //	颜色格式

#define LCD_WHITE 0xffFFFFFF // 纯白色
#define LCD_BLACK 0xff000000 // 纯黑色

#define LCD_BLUE 0xff0000FF    //	纯蓝色
#define LCD_GREEN 0xff00FF00   //	纯绿色
#define LCD_RED 0xffFF0000     //	纯红色
#define LCD_CYAN 0xff00FFFF    //	蓝绿色
#define LCD_MAGENTA 0xffFF00FF //	紫红色
#define LCD_YELLOW 0xffFFFF00  //	黄色
#define LCD_GREY 0xff2C2C2C    //	灰色

#define LIGHT_BLUE 0xff8080FF    //	亮蓝色
#define LIGHT_GREEN 0xff80FF80   //	亮绿色
#define LIGHT_RED 0xffFF8080     //	亮红色
#define LIGHT_CYAN 0xff80FFFF    //	亮蓝绿色
#define LIGHT_MAGENTA 0xffFF80FF //	亮紫红色
#define LIGHT_YELLOW 0xffFFFF80  //	亮黄色
#define LIGHT_GREY 0xffA3A3A3    //	亮灰色

#define DARK_BLUE 0xff000080    //	暗蓝色
#define DARK_GREEN 0xff008000   //	暗绿色
#define DARK_RED 0xff800000     //	暗红色
#define DARK_CYAN 0xff008080    //	暗蓝绿色
#define DARK_MAGENTA 0xff800080 //	暗紫红色
#define DARK_YELLOW 0xff808000  //	暗黄色
#define DARK_GREY 0xff404040    //	暗灰色

#define pink  0XFFC0CB       //粉红色
#define lightcoral   0XFF7F50       //珊瑚色
#define fleshcolor  0XFF7D40       //肉色
#define dodgerblue  0X1E90FF       //宝石蓝色
#define tinzenite  0X03A89E       //锰蓝色
#define Tomato_red  0XFF6347       //番茄红
#define nacarat  0XFF4500      //桔红
#define peacock_blue  0X33A1C9      //孔雀蓝
#define turquoise_blue  0X00C78C      //土耳其玉色




void LCD_CopyBuffer(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint32_t *color);         

void color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);
void lcd_clear(uint16_t color);
uint16_t color_change(uint32_t Color);

/*基础功能函数*/
void LCD_DrawPoint(uint16_t x, uint16_t y, uint32_t color);
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color_biu);


#endif
/**************************
浅灰蓝 176	224	230	0XB0E0E6
品蓝	65	105	225	0X4169E1
石板蓝	106	90	205	0X6A5ACD
天蓝	135	206	235	0X87CEEB
				
青色	0	255	255	0X00FFFF
绿土	56	94	15	0X385E0F
靛青	8	46	84	0X082E54
碧绿色	127	255	212	0X7FFFD4
青绿色	64	224	208	0X40E0D0
绿色	0	255	0	0X00FF00
黄绿色	127	255	0	0X7FFF00
钴绿色	61	145	64	0X3D9140
翠绿色	0	201	87	0X00C957
森林绿	34	139	34	0X228B22
草地绿	124	252	0	0X7CFC00
酸橙绿	50	205	50	0X32CD32
薄荷色	189	252	201	0XBDFCC9
草绿色	107	142	35	0X6B8E23
暗绿色	48	128	20	0X308014
海绿色	46	139	87	0X2E8B57
嫩绿色	0	255	127	0X00FF7F
				
紫色	160	32	240	0XA020F0
紫罗蓝 138	43	226	0X8A2BE2
jasoa	160	102	211	0XA066D3
湖紫色	153	51	250	0X9933FA
淡紫色	218	112	214	0XDA70D6
梅红色	221	160	221	0XDDA0DD
**************************/
