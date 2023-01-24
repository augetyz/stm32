#include "lcd_LTDC.h"

static pFONT *LCD_Fonts; // 英文字体
extern DMA2D_HandleTypeDef hdma2d;	// DMA2D句柄
void color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
     uint16_t x, y;
     if (sx <= ex)
     {
          for (x = sx; x <= ex; x++)
          {
               if (sy < ey)
               {
                    for (y = sy; y <= ey; y++)
                         lcd_draw_point(x, y, color);
               }
               else
               {
                    for (y = ey; y <= sy; y++)
                         lcd_draw_point(x, y, color);
               }
          }
     }
     else
     {
          for (x = ex; x <= sx; x++)
          {
               if (sy < ey)
               {
                    for (y = sy; y <= ey; y++)
                         lcd_draw_point(x, y, color);
               }
               else
               {
                    for (y = ey; y <= sy; y++)
                         lcd_draw_point(x, y, color);
               }
          }
     }
}

void draw_circle(int16_t sx, int16_t sy, uint16_t radius, uint32_t color)
{
     int16_t x = 0, y = 0;
     if (sx - radius > 0)
          x = sx - radius;
     if (sy - radius > 0)
          y = sy - radius;
     else
          y = 0;
     for (; x < sx + radius; x++)
     {
          if (sy - radius > 0)
               y = sy - radius;
          else
               y = 0;
          for (; y < sy + radius; y++)
          {
               if (((x - sx) * (x - sx) + (y - sy) * (y - sy)) <= radius * radius)
               {

                    lcd_fill(x, y, 1, 1, color);
               }
          }
     }
}
void lcd_clear(uint16_t color)
{

     uint16_t *ptr = (uint16_t *)(0x24000000);

     uint32_t i = 0;

     while (i < 800 * 480)
     {

          *(ptr + i++) = color;
     }
}
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
     uint16_t *ptr = (uint16_t *)(0x24000000);
    if(x<=LCD_Width&&y<=LCD_Height)
        *(ptr + y * LCD_Width + x) = color;
    else
        return;
}
void LCD_DrawPoint(uint16_t x, uint16_t y, uint32_t color)
{
     uint16_t *ptr = (uint16_t *)(0x24000000);
     if (Color_Mode == LTDC_PIXEL_FORMAT_RGB565)
     {
          color = color_change(color);
     }
     *(ptr + y * 800 + x) = color;
}
static void _DMA2D_Fill(void *pDst,
                        uint32_t xSize,
                        uint32_t ySize,
                        uint32_t OffLine,
                        uint32_t ColorIndex,
                        uint32_t PixelFormat)
{

     /* DMA2D 采用寄存器到存储器模式, 这种模式用不到前景层和背景层 */
     DMA2D->CR &= ~(DMA2D_CR_START); //	停止DMA2D
     DMA2D->CR = DMA2D_R2M;
     DMA2D->OCOLR = ColorIndex;
     DMA2D->OMAR = (uint32_t)pDst;
     DMA2D->OOR = OffLine;
     DMA2D->OPFCCR = PixelFormat;
     DMA2D->NLR = (uint32_t)(xSize << 16) | (uint16_t)ySize;

     /* 启动传输 */
     DMA2D->CR |= DMA2D_CR_START;

     /* 等待 DMA2D 传输完成 */
     while (DMA2D->CR & DMA2D_CR_START)
     {
     }
}
uint16_t color_change(uint32_t Color)
{
     uint16_t Red_Value = 0, Green_Value = 0, Blue_Value = 0;
     Red_Value = (uint16_t)((Color & 0x00F80000) >> 8);
     Green_Value = (uint16_t)((Color & 0x0000FC00) >> 5);
     Blue_Value = (uint16_t)((Color & 0x000000F8) >> 3);
     return (uint16_t)(Red_Value | Green_Value | Blue_Value);
}

void lcd_fill0(uint16_t sx, uint16_t sy, uint16_t x, uint16_t y, uint32_t color_biu)
{
     uint32_t date_address;
     uint16_t color;
     if (Color_Mode == LTDC_PIXEL_FORMAT_RGB565)
     {
          color = color_change(color_biu);
     }
     date_address = LCD_MemoryAdd + sy * LCD_Width * 2 + sx * 2;

     y++;
     _DMA2D_Fill((void *)(date_address), x, y, LCD_Width - x, color, Color_Mode);
}
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t x, uint16_t y, uint16_t color_biu)
{
     uint32_t date_address;
     
     date_address = LCD_MemoryAdd + sy * LCD_Width * 2 + sx * 2;
    
     
    
     _DMA2D_Fill((void *)(date_address), x, y, LCD_Width - x, color_biu, Color_Mode);
}
/***************************************************************************************************************
 *	函 数 名:	LCD_DisplayChar
 *
 *	入口参数:	x - 起始水平坐标，取值范围0~799
 *					y - 起始垂直坐标，取值范围0~479
 *					c  - ASCII字符
 *
 *	函数功能:	在指定坐标显示指定的字符
 *
 *	说    明:	1. 可设置要显示的字体，例如使用 LCD_SetFont(&Font24) 设置为 2412的ASCII字体
 *					2.	可设置要显示的颜色，例如使用 LCD_SetColor(0xff0000FF) 设置为蓝色
 *					3. 可设置对应的背景色，例如使用 LCD_SetBackColor(0xff000000) 设置为黑色的背景色
 *					4. 使用示例 LCD_DisplayChar( 10, 10, 'a') ，在坐标(10,10)显示字符 'a'
 *
 ***************************************************************************************************************/

void LCD_DisplayChar(uint16_t x, uint16_t y, uint8_t c, uint32_t color)
{
     uint16_t index = 0, counter = 0; // 计数变量
     uint8_t disChar;                 // 存储字符的地址
     uint16_t Xaddress = x;           // 水平坐标

     c = c - 32; // 计算ASCII字符的偏移
     if (Color_Mode == LTDC_PIXEL_FORMAT_RGB565)
     {
          color = color_change(color);
     }
     for (index = 0; index < LCD_Fonts->Sizes; index++)
     {
          disChar = LCD_Fonts->pTable[c * LCD_Fonts->Sizes + index]; // 获取字符的模值
          for (counter = 0; counter < 8; counter++)
          {
               if (disChar & 0x01)
               {
                    lcd_draw_point(Xaddress, y, color); // 当前模值不为0时，使用画笔色绘点
               }

               disChar >>= 1;
               Xaddress++; // 水平坐标自加

               if ((Xaddress - x) == LCD_Fonts->Width) // 如果水平坐标达到了字符宽度，则退出当前循环
               {                                       // 进入下一行的绘制
                    Xaddress = x;
                    y++;
                    break;
               }
          }
     }
}
void LCD_DisplayString(uint16_t x, uint16_t y, char *p, uint32_t color)
{
     while ((x < LCD_Width) && (*p != 0)) // 判断显示坐标是否超出显示区域并且字符是否为空字符
     {
          LCD_DisplayChar(x, y, *p, color);
          x += LCD_Fonts->Width; // 显示下一个字符
          p++;                   // 取下一个字符地址
     }
}
/***************************************************************************************************************
 *	函 数 名:	LCD_SetTextFont
 *
 *	入口参数:	*fonts - 要设置的文本字体
 *
 *	函数功能:	设置文本字体，包括中文和ASCII字符，
 *
 *	说    明:	1. 可选择使用 3232/2424/2020/1616/1212 五种大小的中文字体，
 *						并且对应的设置ASCII字体为 3216/2412/2010/1608/1206
 *					2. 相关字模存放在 lcd_fonts.c
 *					3. 中文字库使用的是小字库，即用到了对应的汉字再去取模
 *					4. 使用示例 LCD_SetTextFont(&CH_Font24) ，即设置 2424的中文字体以及2412的ASCII字符字体
 *
 ***************************************************************************************************************/

void LCD_SetTextFont(pFONT *fonts)
{
     LCD_Fonts = fonts; // 设置中文字体
     switch (fonts->Width)
     {
     case 12:
          LCD_Fonts = &Font12;
          break; // 设置ASCII字符的字体为 1206
     case 16:
          LCD_Fonts = &Font16;
          break; // 设置ASCII字符的字体为 1608
     case 20:
          LCD_Fonts = &Font20;
          break; // 设置ASCII字符的字体为 2010
     case 24:
          LCD_Fonts = &Font24;
          break; // 设置ASCII字符的字体为 2412
     case 32:
          LCD_Fonts = &Font32;
          break; // 设置ASCII字符的字体为 3216
     default:
          break;
     }
}
/***************************************************************************************************************************************
 *	函 数 名: LCD_DrawLine
 *
 *	入口参数: x1 - 起点 水平坐标，取值范围 0~799
 *			 	 y1 - 起点 垂直坐标，取值范围 0~479
 *
 *				 x2 - 终点 水平坐标，取值范围 0~799
 *            y2 - 终点 垂直坐标，取值范围 0~479
 *
 *	函数功能: 在两点之间画线
 *
 *	说    明: 该函数移植于ST官方评估板的例程
 *
 *****************************************************************************************************************************************/

#define ABS(X) ((X) > 0 ? (X) : -(X))

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
     int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
             yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
             curpixel = 0;

     deltax = ABS(x2 - x1); /* The difference between the x's */
     deltay = ABS(y2 - y1); /* The difference between the y's */
     x = x1;                /* Start x off at the first pixel */
     y = y1;                /* Start y off at the first pixel */

     if (x2 >= x1) /* The x-values are increasing */
     {
          xinc1 = 1;
          xinc2 = 1;
     }
     else /* The x-values are decreasing */
     {
          xinc1 = -1;
          xinc2 = -1;
     }

     if (y2 >= y1) /* The y-values are increasing */
     {
          yinc1 = 1;
          yinc2 = 1;
     }
     else /* The y-values are decreasing */
     {
          yinc1 = -1;
          yinc2 = -1;
     }

     if (deltax >= deltay) /* There is at least one x-value for every y-value */
     {
          xinc1 = 0; /* Don't change the x when numerator >= denominator */
          yinc2 = 0; /* Don't change the y for every iteration */
          den = deltax;
          num = deltax / 2;
          numadd = deltay;
          numpixels = deltax; /* There are more x-values than y-values */
     }
     else /* There is at least one y-value for every x-value */
     {
          xinc2 = 0; /* Don't change the x for every iteration */
          yinc1 = 0; /* Don't change the y when numerator >= denominator */
          den = deltay;
          num = deltay / 2;
          numadd = deltax;
          numpixels = deltay; /* There are more y-values than x-values */
     }
     for (curpixel = 0; curpixel <= numpixels; curpixel++)
     {
          LCD_DrawPoint(x, y, color); /* Draw the current pixel */
          num += numadd;              /* Increase the numerator by the top of the fraction */
          if (num >= den)             /* Check if numerator >= denominator */
          {
               num -= den; /* Calculate the new numerator value */
               x += xinc1; /* Change the x as appropriate */
               y += yinc1; /* Change the y as appropriate */
          }
          x += xinc2; /* Change the x as appropriate */
          y += yinc2; /* Change the y as appropriate */
     }
}
/***************************************************************************************************************************************
 *	函 数 名: LCD_DrawRect
 *
 *	入口参数: x - 起始水平坐标，取值范围0~799
 *				 y - 起始垂直坐标，取值范围0~479
 *			 	 width  - 矩形的水平宽度，最大取值LCD_Width
 *				 height - 矩形的垂直宽度，最大取值LCD_height
 *
 *	函数功能: 在指点位置绘制指定长宽的矩形线条
 *
 *	说    明: 该函数移植于ST官方评估板的例程
 *
 *****************************************************************************************************************************************/

void LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
     /* draw horizontal lines */
     LCD_DrawLine(x, y, x + width, y, color);
     LCD_DrawLine(x, y + height, x + width, y + height, color);

     /* draw vertical lines */
     LCD_DrawLine(x, y, x, y + height, color);
     LCD_DrawLine(x + width, y, x + width, y + height, color);
}
/***************************************************************************************************************************************
 *	函 数 名: LCD_DrawCircle
 *
 *	入口参数: x - 圆心 水平坐标，取值范围 0~799
 *			 	 y - 圆心 垂直坐标，取值范围 0~479
 *			 	 r  - 半径
 *
 *	函数功能: 在坐标 (x,y) 绘制半径为 r 的圆形线条
 *
 *	说    明: 1. 该函数移植于ST官方评估板的例程
 *				 2. 要绘制的区域不能超过屏幕的显示区域
 *
 *****************************************************************************************************************************************/

void LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r, uint32_t color)
{
     int Xadd = -r, Yadd = 0, err = 2 - 2 * r, e2;
     do
     {

          LCD_DrawPoint(x - Xadd, y + Yadd, color);
          LCD_DrawPoint(x + Xadd, y + Yadd, color);
          LCD_DrawPoint(x + Xadd, y - Yadd, color);
          LCD_DrawPoint(x - Xadd, y - Yadd, color);

          e2 = err;
          if (e2 <= Yadd)
          {
               err += ++Yadd * 2 + 1;
               if (-Xadd == Yadd && e2 <= Xadd)
                    e2 = 0;
          }
          if (e2 > Xadd)
               err += ++Xadd * 2 + 1;
     } while (Xadd <= 0);
}
/***************************************************************************************************************************************
 *	函 数 名: LCD_FillCircle
 *
 *	入口参数: x - 圆心 水平坐标，取值范围 0~799
 *			 	 y - 圆心 垂直坐标，取值范围 0~479
 *			 	 r  - 半径
 *
 *	函数功能: 在坐标 (x,y) 填充半径为 r 的圆形区域
 *
 *	说    明: 1. 该函数移植于ST官方评估板的例程
 *				 2. 要绘制的区域不能超过屏幕的显示区域
 *
 *****************************************************************************************************************************************/

void LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r, uint32_t color)
{
     int32_t D;     /* Decision Variable */
     uint32_t CurX; /* Current X Value */
     uint32_t CurY; /* Current Y Value */

     D = 3 - (r << 1);

     CurX = 0;
     CurY = r;

     while (CurX <= CurY)
     {
          if (CurY > 0)
          {
               LCD_DrawLine(x - CurX, y - CurY, x - CurX, y - CurY + 2 * CurY, color);
               LCD_DrawLine(x + CurX, y - CurY, x + CurX, y - CurY + 2 * CurY, color);
          }

          if (CurX > 0)
          {
               LCD_DrawLine(x - CurY, y - CurX, x - CurY, y - CurX + 2 * CurX, color);
               LCD_DrawLine(x + CurY, y - CurX, x + CurY, y - CurX + 2 * CurX, color);
          }
          if (D < 0)
          {
               D += (CurX << 2) + 6;
          }
          else
          {
               D += ((CurX - CurY) << 2) + 10;
               CurY--;
          }
          CurX++;
     }

     LCD_DrawCircle(x, y, r, color);
}
void lcd_draw_image(uint16_t sx,uint16_t sy,uint16_t w,uint16_t h,uint8_t* image)
{
    uint16_t x,y,color;
    uint32_t i=0;
    
    
    for(y=0;y<h;y++)
    {
        for(x=0;x<w;x++)
        {
            color=((uint16_t)image[i]<<8)+image[++i];
            lcd_draw_point(x+sx, y+sy, color);
            i++;
        }
        
    }
    
}
void LCD_CopyBuffer(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint32_t *color)
{

	DMA2D->CR	  &=	~(DMA2D_CR_START);				//	停止DMA2D
	DMA2D->CR		=	DMA2D_M2M;							//	存储器到存储器
	DMA2D->FGPFCCR	=	LTDC_PIXEL_FORMAT_RGB565;		//	设置颜色格式
   DMA2D->FGOR    =  0;										// 
	DMA2D->OOR		=	LCD_Width - width;				//	设置行偏移 	
	DMA2D->FGMAR   =  (uint32_t)color;		
	DMA2D->OMAR		=	LCD_MemoryAdd + 2*(LCD_Width * y + x);	// 地址;
	DMA2D->NLR		=	(width<<16)|(height);			//	设定长度和宽度		
	DMA2D->CR	  |=	DMA2D_CR_START;					//	启动DMA2D
		
	while (DMA2D->CR & DMA2D_CR_START) ;			//	等待传输完成

}



