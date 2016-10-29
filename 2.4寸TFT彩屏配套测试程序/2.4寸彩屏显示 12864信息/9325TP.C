/*----------------------------------------------------------------
 320x240彩屏液晶驱动程序
----------------------------------------------------------------*/
#include"9325tp.h"
#include"reg52.h"
/*----------------------------------------------------------------
                            全局变量
----------------------------------------------------------------*/
#define WINDOW_XADDR_START	0x0050 // Horizontal Start Address Set
#define WINDOW_XADDR_END	0x0051 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0052 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0053 // Vertical End Address Set
#define GRAM_XADDR		    0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		    0x0021 // GRAM Vertical Address Set
#define GRAMWR 			    0x0022 // memory write

#define DataPort P0                //数据口使用DataPort

/*----------------------------------------------------------------
                           定义硬件端口
----------------------------------------------------------------*/
sbit CS=P2^2;		//片选
sbit RES=P2^1;		//复位
sbit RS=P2^4;		//数据/命令选择
sbit RW=P2^5;
/*----------------------------------------------------------------
                           清屏函数
输入参数：bColor 清屏所使用的背景色
----------------------------------------------------------------*/
void CLR_Screen(unsigned int bColor)
{
 unsigned int i,j;
 LCD_SetPos(0,240,0,320);//320x240
 for (i=0;i<320;i++)
	{
	
	   for (j=0;j<240;j++)
	       Write_Data_U16(bColor);

	}
}
/*----------------------------------------------------------------
                            显示英文字符
输入参数：x 横坐标
          y 纵坐标
		  c 需要显示的字符
		  fColor 字符颜色
		  bColor 字符背景颜色
----------------------------------------------------------------*/
#include "8X16.h"
void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor)
{
 unsigned int i,j;
 LCD_SetPos(x,x+8-1,y,y+16-1);
 for(i=0; i<16;i++) {
		unsigned char m=Font8x16[c*16+i];
		for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				Write_Data_U16(fColor);
				}
			else {
				Write_Data_U16(bColor);
				}
			m<<=1;
			}
		}
}

/*----------------------------------------------------------------
                            显示英文字符
输入参数：x 横坐标
          y 纵坐标
		  c 需要显示的字符
		  fColor 字符颜色
		  bColor 字符背景颜色
----------------------------------------------------------------*/
void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor) {

		LCD_PutChar8x16( x, y, c, fColor, bColor );
	}

/*----------------------------------------------------------------
                            显示汉字
输入参数：x 横坐标
          y 纵坐标
		  c 需要显示的汉字码
		  fColor 字符颜色
		  bColor 字符背景颜色
----------------------------------------------------------------*/
#include "GB1616.h"	//16*16汉字字模

void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor){
	unsigned int i,j,k;

	LCD_SetPos(x,  x+16-1,y, y+16-1);

	for (k=0;k<64;k++) { //64标示自建汉字库中的个数，循环查询内码
	  if ((codeGB_16[k].Index[0]==c[0])&&(codeGB_16[k].Index[1]==c[1])){ 
    	for(i=0;i<32;i++) {
		  unsigned short m=codeGB_16[k].Msk[i];
		  for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				Write_Data_U16(fColor);
				}
			else {
				Write_Data_U16(bColor);
				}
			m<<=1;
			} 
		  }
		}  
	  }	
}
/*----------------------------------------------------------------
                            显示字符串
可以中英文同时显示
输入参数：x 横坐标
          y 纵坐标
		  *s 需要显示的字符串
		  fColor 字符颜色
		  bColor 字符背景颜色
----------------------------------------------------------------*/
void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor) {
	 unsigned char l=0;
	while(*s) {
		if( *s < 0x80) 
		    {
			LCD_PutChar(x+l*8,y,*s,fColor,bColor);
			s++;l++;
			}
		else
		    {
			PutGB1616(x+l*8,y,(unsigned char*)s,fColor,bColor);
			s+=2;l+=2;
			}
		}
	}
/*----------------------------------------------------------------
                            显示RGB颜色
输入参数：x0，y0 起始坐标
          x1，y1 结束坐标
		  Color  背景颜色
----------------------------------------------------------------*/
void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color)
{
	unsigned int i,j;
	LCD_SetPos(x0,x1,y0,y1);
	for (i=y0;i<=y1;i++)
	{
	   for (j=x0;j<=x1;j++)
	       Write_Data_U16(Color);

	}
}
/*----------------------------------------------------------------
                            显示图片
图片必须是320x240，否则不能正确识别
----------------------------------------------------------------*/
/*void show_photo(void)
{
	unsigned char j;
	unsigned int i;
	unsigned long s=0;

	LCD_SetPos(0,240,0,320);//320x240

	for (i=0;i<75;i++)
	{
	for (j=0;j<240;j++)
	Write_Data(0xff,0xff);
		
	}

	for (i=0;i<170;i++)
	{
	for (j=0;j<55;j++)
		Write_Data(0xff,0xff);

		for (j=0;j<130;j++)
		Write_Data(pic[s++],pic[s++]);
		
		for (j=0;j<55;j++)
		Write_Data(0xff,0xff);
	}

    for (i=0;i<75;i++)
	{
	for (j=0;j<240;j++)
	Write_Data(0xff,0xff);
		
	}
}
*/
/*----------------------------------------------------------------
                         写命令、写数据
输入参数：x 需要输入的命令 16位
          y 需要输入的数据 16位
----------------------------------------------------------------*/
void  Write_Cmd_Data (unsigned char x,unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Cmd(0x00,x);
	Write_Data(m,n);

}

/*----------------------------------------------------------------
                         写16位数据
----------------------------------------------------------------*/
void  Write_Data_U16(unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Data(m,n);

}
/*----------------------------------------------------------------
                           写命令
----------------------------------------------------------------*/

void Write_Cmd(unsigned char DH,unsigned char DL)
{
	CS=0;
	RS=0;

	DataPort=DH;
	RW=0;
	RW=1;

	DataPort=DL;
	
	RW=0;
	RW=1;
	CS=1;
}

/*----------------------------------------------------------------
                           写数据 双8位
----------------------------------------------------------------*/

void Write_Data(unsigned char DH,unsigned char DL)
{
	
	CS=0;
	
	RS=1;
	DataPort=DH;
	RW=0;
    RW=1;

	DataPort=DL;	
	RW=0;
	RW=1;
	CS=1;
}
/*----------------------------------------------------------------
                        延时函数
----------------------------------------------------------------*/
void delayms(unsigned int count)
{
    int i,j;                                                                                
    for(i=0;i<count;i++)                                                                    
       {
	     for(j=0;j<260;j++);
       }                                                                                     
}



/*----------------------------------------------------------------
                            液晶初始化
----------------------------------------------------------------*/
void ILI9325_Initial(void)
{ 
    CS=1;
	delayms(5);
	RES=0;
	delayms(5);
	RES=1;
 delayms(50);
 Write_Cmd_Data(0x0001,0x0100); 
 Write_Cmd_Data(0x0002,0x0700); 
 Write_Cmd_Data(0x0003,0x1030); 
 Write_Cmd_Data(0x0004,0x0000); 
 Write_Cmd_Data(0x0008,0x0207);  
 Write_Cmd_Data(0x0009,0x0000);
 Write_Cmd_Data(0x000A,0x0000); 
 Write_Cmd_Data(0x000C,0x0000); 
 Write_Cmd_Data(0x000D,0x0000);
 Write_Cmd_Data(0x000F,0x0000);
//power on sequence VGHVGL
 Write_Cmd_Data(0x0010,0x0000);   
 Write_Cmd_Data(0x0011,0x0007);  
 Write_Cmd_Data(0x0012,0x0000);  
 Write_Cmd_Data(0x0013,0x0000); 
//vgh 
 Write_Cmd_Data(0x0010,0x1290);   
 Write_Cmd_Data(0x0011,0x0227);
 //delayms(100);
 //vregiout 
 Write_Cmd_Data(0x0012,0x001d); //0x001b
 //delayms(100); 
 //vom amplitude
 Write_Cmd_Data(0x0013,0x1500);
 //delayms(100); 
 //vom H
 Write_Cmd_Data(0x0029,0x0018); 
 Write_Cmd_Data(0x002B,0x000D); 

//gamma
 Write_Cmd_Data(0x0030,0x0004);
 Write_Cmd_Data(0x0031,0x0307);
 Write_Cmd_Data(0x0032,0x0002);// 0006
 Write_Cmd_Data(0x0035,0x0206);
 Write_Cmd_Data(0x0036,0x0408);
 Write_Cmd_Data(0x0037,0x0507); 
 Write_Cmd_Data(0x0038,0x0204);//0200
 Write_Cmd_Data(0x0039,0x0707); 
 Write_Cmd_Data(0x003C,0x0405);// 0504
 Write_Cmd_Data(0x003D,0x0F02); 
 //ram
 Write_Cmd_Data(0x0050,0x0000); 
 Write_Cmd_Data(0x0051,0x00EF);
 Write_Cmd_Data(0x0052,0x0000); 
 Write_Cmd_Data(0x0053,0x013F);  
 Write_Cmd_Data(0x0060,0xA700); 
 Write_Cmd_Data(0x0061,0x0001); 
 Write_Cmd_Data(0x006A,0x0000); 
 //
 Write_Cmd_Data(0x0080,0x0000); 
 Write_Cmd_Data(0x0081,0x0000); 
 Write_Cmd_Data(0x0082,0x0000); 
 Write_Cmd_Data(0x0083,0x0000); 
 Write_Cmd_Data(0x0084,0x0000); 
 Write_Cmd_Data(0x0085,0x0000); 
 //
 Write_Cmd_Data(0x0090,0x0010); 
 Write_Cmd_Data(0x0092,0x0600); 
 Write_Cmd_Data(0x0093,0x0003); 
 Write_Cmd_Data(0x0095,0x0110); 
 Write_Cmd_Data(0x0097,0x0000); 
 Write_Cmd_Data(0x0098,0x0000);
 Write_Cmd_Data(0x0007,0x0133);

	
	
//	Write_Cmd_Data(0x0022);//		
}

/*----------------------------------------------------------------
                            画点
输入参数：x，y 需要画点坐标
          color 点的颜色
----------------------------------------------------------------*/
/*void Put_pixel(uchar x,uchar y,unsigned int color)
{
	LCD_SetPos(x,x,y,y);
	Write_Data_U16(color);
}
*/
/*----------------------------------------------------------------
                         设置坐标
----------------------------------------------------------------*/
static void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{
  Write_Cmd_Data(WINDOW_XADDR_START,x0);
  Write_Cmd_Data(WINDOW_XADDR_END,x1);
  Write_Cmd_Data(WINDOW_YADDR_START,y0);
  Write_Cmd_Data(WINDOW_YADDR_END,y1);
  Write_Cmd_Data(GRAM_XADDR,x0);
  Write_Cmd_Data(GRAM_YADDR,y0);
  Write_Cmd (0x00,0x22);//LCD_WriteCMD(GRAMWR);
}
/*----------------------------------------------------------------
                           在屏幕上画线
输入参数：  起始坐标X0，Y0，终止坐标X1，Y1
			color 线颜色
----------------------------------------------------------------*/
/*void Line(	uchar X0,
			uchar Y0,
			uchar X1,
			uchar Y1,
			unsigned int color)
{
	int dx = X1 - X0;
	int dy = Y1 - Y0;
	int P  = 2 * dy - dx;
	int dobDy = 2 * dy;
	int dobD = 2 * (dy - dx);
	int PointX = 0,PointY = 0;
	int incx = 0,incy = 0;
	int distance = 0,xerr = 0,yerr = 0;
	unsigned int i = 0;

	if(dx == 0)		//k=1斜率为1
	{
		PointX = X0;
		if(Y0 < Y1)
		{
			PointY = Y0;
		}
		else
		{
			PointY = Y1;
		}
		for(i = 0;i <= ((Y0<Y1) ? (Y1-Y0) : (Y0-Y1));i++)
		{

				Put_pixel(PointX,PointY,color);
			PointY++;
		}
		return;
	}
	if(dy == 0)		//k=0斜率为0
	{
		PointY = Y0;
		if(X0 < X1)
		{
			PointX = X0;
		}
		else
		{
			PointX = X1;
		}
		for(i = 0;i <= ((X0<X1) ? (X1-X0) : (X0-X1));i++)
		{

				Put_pixel(PointX,PointY,color);
			PointX++;
		}
		return;
	}

	if(dx > 0)
		incx = 1;
	else if(dx == 0)
		incx = 0;
	else
		incx = -1;

	if(dy > 0)
		incy = 1;
	else if(dy == 0)
		incy = 0;
	else
		incy = -1;

    dx = ((X0>X1) ? (X0-X1) : (X1-X0));
    dy = ((Y0>Y1) ? (Y0-Y1) : (Y1-Y0));

    if(dx>dy) distance=dx;
    else distance=dy;

    PointX = X0;
    PointY = Y0;
    for(i=0;i<=distance+1;i++)
    {

    		Put_pixel(PointX,PointY,color);
        xerr+=dx;
        yerr+=dy;
        if(xerr>distance)
        {
            xerr-=distance;
            PointX+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            PointY+=incy;
        }
    }
}*/
/*---------------------------------------------------------------------------
                            绘制矩形框
输入参数：矩形的起始位置left,top 
 		  矩形的结束位置right,bottom 
 		 矩形框的颜色color

-----------------------------------------------------------------------------*/
/*void Rectangle( uchar left,
				uchar top,
				uchar right,
				uchar bottom,
				unsigned int color)
{
	Line(left,top,right,top,color);
	Line(left,top,left,bottom,color);
	Line(right,top,right,bottom,color);
	Line(left,bottom,right,bottom,color);
}*/
/*---------------------------------------------------------------------------
                            绘制平面矩形
输入参数：矩形的起始位置left,top 
 		  矩形的结束位置right,bottom 
 		 矩形框的颜色color
-----------------------------------------------------------------------------*/
/*void Bar(	uchar left,
			uchar top,
			uchar right,
			uchar bottom,
			unsigned int color)
{
	uchar i = 0,k = 0;
	for(k = top;k < bottom;k++)
	{
		for(i = left+1;i <= right;i++)
		{
		 LCD_SetPos(i,i,k,k);
          Write_Data_U16(color);
		}
	}
}*/
/*---------------------------------------------------------------------------
                         向LCD发送一个0--255的数值
-----------------------------------------------------------------------------*/
/*void LCDShow_uCharNumber(	uchar x,
							uchar y,
							uchar uCharNumber,
							unsigned int forecolor,
							unsigned int bkcolor)
{
	LCD_PutChar(x,y,uCharNumber/100+'0',forecolor,bkcolor);
	LCD_PutChar(x+8,y,uCharNumber/10%10+'0',forecolor,bkcolor);
	LCD_PutChar(x+16,y,uCharNumber%10+'0',forecolor,bkcolor);
}*/
