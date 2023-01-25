#include "lcd_LTDC.h"


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



#define ABS(X) ((X) > 0 ? (X) : -(X))


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



