/*-----------------------------------------------
  名称：写彩屏
  公司：上海浩豚电子科技有限公司
  网站：www.doflye.net
  编写：师访
  日期：2009.12
  修改：无
  内容：320x240像素、16位BMP图片的HEX数据，依次写到屏上，还原图片
  注意事项：
------------------------------------------------*/
#include"reg52.h"
//============================================================
//根据芯片资料定义
#define WINDOW_XADDR_START	0x0050 // Horizontal Start Address Set
#define WINDOW_XADDR_END	0x0051 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0052 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0053 // Vertical End Address Set
#define GRAM_XADDR		    0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		    0x0021 // GRAM Vertical Address Set
#define GRAMWR 			    0x0022 // memory write

//=============================================================
//定义液晶屏接口
sbit CS=P2^2;		//片选
sbit RES=P2^1;		//复位
sbit RS=P2^4;		//数据/命令选择
sbit RW=P2^5;
                    //数据口使用P0
//====================================================//
//函数声明
void ILI9325_Initial(void);
void Write_Cmd_Data(unsigned char x, unsigned int y);
void Write_Cmd(unsigned char DH,unsigned char DL);
void Write_Data(unsigned char DH,unsigned char DL);
void delayms(unsigned int tt);
void  Write_Data_U16(unsigned int y);
static void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
void ClearScreen(unsigned int bColor);

//===============================================================
//清屏
void ClearScreen(unsigned int bColor)
{
 unsigned int i,j;
 LCD_SetPos(0,240,0,320);//320x240
 for (i=0;i<320;i++)
	{
	
	   for (j=0;j<240;j++)
	       Write_Data_U16(bColor);
	}
}


//===============================================================
//写命令数据

void  Write_Cmd_Data (unsigned char x,unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Cmd(0x00,x);
	Write_Data(m,n);

}

//==============================================================
//写16位数据
void  Write_Data_U16(unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Data(m,n);

}
//=============================================================
//写命令

void Write_Cmd(unsigned char DH,unsigned char DL)
{
  
	CS=0;
	RS=0;

	P0=DH;
	RW=0;
	RW=1;

	P0=DL;
	
	RW=0;
	RW=1;
	CS=1;
}

//===================================================================
//写数据

void Write_Data(unsigned char DH,unsigned char DL)
{
 
  
	
	CS=0;
	
	RS=1;
	P0=DH;
	RW=0;
    RW=1;

	P0=DL;	
	RW=0;
	RW=1;
	CS=1;
}





//============================================================
//延时程序
void delayms(unsigned int count)
{
    int i,j;                                                                                
    for(i=0;i<count;i++)                                                                    
       {
	     for(j=0;j<260;j++);
       }                                                                                     
}



//=============================================================
//液晶初始化

void ILI9325_Initial(void)
{ 

 delayms(50);                     //根据不同晶振速度可以调整延时，保障稳定显示
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



//===============================================================
//定义坐标
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




