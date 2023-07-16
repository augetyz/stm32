
 
#include "stm32f10x.h"
#include "math.h"
#include "xpt2046.h"
#include "delay.h"
#include "spi.h"
#include "gui.h"
#include "tft.h"



/*
  xpt2046
  AD_DCLK  PC5
  AD_CS    PC6
  AD_DIN   PC7
  AD_OUT   PC3			读取触摸返回数据
  AD_PEN   PC1
*/






//初始化 触摸芯片XPT2046 SPI片选IO 及判断IO
void XPT2046_Init(void)
{	
  	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );//PORTB时钟使能 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_7;//PC5 PC6 PC7设置为推挽输出 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1| GPIO_Pin_3;//PC1/PC3 设置为上拉输入 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);


}  


//默认为touchtype=0的数据.
u8 CMD_RDX=0XD0;
u8 CMD_RDY=0X90;



//SPI写数据
//向触摸屏IC写入1byte数据    
//num:要写入的数据
void TP_Write_Byte(u8 num)    
{  
	u8 count=0;   
	for(count=0;count<8;count++)  
	{ 	  
		if(num&0x80)TP_DIN=1;  
		else TP_DIN=0;   
		num<<=1;    
		TP_CLK=0; 
		delay_us(1);
		TP_CLK=1;		//上升沿有效	        
	}		 			    
} 




//SPI读数据 
//从触摸屏IC读取adc值
//CMD:指令
//返回值:读到的数据	   
u16 TP_Read_AD(u8 CMD)	  
{ 	 
	u8 count=0; 	  
	u16 Num=0; 
	TP_CLK=0;		//先拉低时钟 	 
	TP_DIN=0; 	//拉低数据线
	TP_CS=0; 		//选中触摸屏IC
	TP_Write_Byte(CMD);//发送命令字
	delay_us(6);//ADS7846的转换时间最长为6us
	TP_CLK=0; 	     	    
	delay_us(1);    	   
	TP_CLK=1;		//给1个时钟，清除BUSY
	delay_us(1);    
	TP_CLK=0; 	     	    
	for(count=0;count<16;count++)//读出8位数据 
	{ 				  
		Num<<=1; 	 
		TP_CLK=0;	//下降沿有效  	    	   
		delay_us(1);    
 		TP_CLK=1;
 		if(TP_OUT)Num++; 		 
	}  	
	Num>>=4;   	//只有高12位有效.
	TP_CS=1;		//释放片选	 
	return(Num);   
}



//读取一个坐标值(x或者y)
//连续读取READ_TIMES次数据,对这些数据升序排列,
//然后去掉最低和最高LOST_VAL个数,取平均值 
//xy:指令（CMD_RDX/CMD_RDY）
//返回值:读到的数据
#define READ_TIMES 5 	//读取次数
#define LOST_VAL 1	  	//丢弃值
u16 TP_Read_XOY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);		 		    
	for(i=0;i<READ_TIMES-1; i++)//排序
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//升序排列
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 




//读取x,y坐标
//最小值不能少于100.
//x,y:读取到的坐标值
//返回值:0,失败;1,成功。
u8 TP_Read_XY(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=TP_Read_XOY(CMD_RDX);
	ytemp=TP_Read_XOY(CMD_RDY);	  												   
	//if(xtemp<100||ytemp<100)return 0;//读数失败
	*x=xtemp;
	*y=ytemp;
	return 1;//读数成功
}







//SPI总线法 读取XPT2046数据
//采集触摸时xpt输出的物理坐标 x y  
//此函数没有转换成LCD的实际坐标 
//为校准函数做读取
//返回 xpt2046ad.x  物理x坐标
//     xpt2046ad.y  物理y坐标
//     xpt2046ad.flag 采集成功标志
struct TFT_Pointer xpt2046ad()		                                 
{
 struct TFT_Pointer result;
// u8   ax[8];
 u16 x1,y1;
 u16 x2,y2;

 result.x=0;
 result.y=0;
 result.flag=0;
 
#define ERR_RANGE 20 //误差范围 
  
 if(xpt2046_isClick==0)
 {	 
  delay_ms(1);
  if(xpt2046_isClick==0)
  {
    TP_CS=0; 		//开片选
   
   /*这里采用16时钟周期采集  因为 此触摸功能采用的是SPI总线
     而SPI功能是只能8位传输  XPT2046的AD分辨率为12位  
	 这样8位的SPI接收是不行的
	 所以 根据XPT2046手册中 16时钟周期 时序图 可以看出
	 发送采集数据  接收一次SPI数据后 在发送空功能的SPI数据  就会把剩下的部分接收到
	 这样先接收的 是低字节数据  第二次接收的是高字节数据  移位后 便是12位的AD值   
   */

	TP_Read_XY(&x1,&y1);
	TP_Read_XY(&x2,&y2);


if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-ERR_RANGE内
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
   {
   	result.flag=1;			//打开标志位
	result.x=(x1+x2)/2;
	result.y=(y1+y2)/2;
   }
   else result.flag=0;

   TP_CS=1; 		//关片选
   
  }
 } 

 return result;
}
												




//触摸数据转换屏实际坐标函数体
//返回 result.x坐标 result.y坐标 
struct TFT_Pointer TFT_Cm(void)		                                  
{
 u16 a,b;				//临时变量
 struct TFT_Pointer result;

 result=xpt2046ad();	 //读取AD值



//触摸板X Y
   a=result.x;
   b=result.y;
/* 触摸屏计算公式
   lcdx=xa*tpx+xb;
   lcdy=ya*tpy+yb;
   lcdx,lcdy为屏坐标  tpx,tpy为触屏板值 xa,ya为比例因子  xb,yb为偏移量

   计算方法 
   在屏幕上指定lcdx,lcdy位置画出十字图形 分别画在屏幕上的4个角位置
   用触摸笔分别点击 得到其中的触摸值
   根据上面的公式 计算	xa,ya  xb,yb  这样就能使得触摸板和屏幕校准
  */
	 
		 result.x=240-(0.065894*a-16);			//将得到的AD值带入公式 计算lcd屏的x y坐标 
		 result.y=320-(0.084031*b-14);		//如果y轴 上下颠倒 改为	result.y=0.084031*b-14;

 return result;								//返回坐标值
}


















