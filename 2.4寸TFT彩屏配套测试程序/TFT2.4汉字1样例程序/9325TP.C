
#include"reg52.h"

#define WINDOW_XADDR_START	0x0050 // Horizontal Start Address Set
#define WINDOW_XADDR_END	0x0051 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0052 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0053 // Vertical End Address Set
#define GRAM_XADDR		    0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		    0x0021 // GRAM Vertical Address Set
#define GRAMWR 			    0x0022 // memory write



sbit CS=P2^2;		//片选
sbit RES=P2^1;		//复位
sbit RS=P2^4;		//数据/命令选择
sbit RW=P2^5;
                    //数据口使用P0
//====================================================//

void main (void);
void ILI9325_Initial(void);
void show_colour_bar (void);
void Write_Cmd_Data(unsigned char x, unsigned int y);
void Write_Cmd(unsigned char DH,unsigned char DL);
void Write_Data(unsigned char DH,unsigned char DL);
void delayms(unsigned int tt);
void show_photo(void);
void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color);
unsigned char code pic[];
void  Write_Data_U16(unsigned int y);
static void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
void ClearScreen(unsigned int bColor);
void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void LCD_PutString(unsigned short x, unsigned short y, char *s, unsigned int fColor, unsigned int bColor);

void LCD_PutChar8x8(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
//================================================//

void  main(void)
{   
	CS=1;
	delayms(5);
	RES=0;
	delayms(5);
	RES=1;
	delayms(5);
	ILI9325_Initial();
	while(1)
	{
	
	/*Show_RGB(0x0000);
	Show_RGB(0xffff);
	Show_RGB(0xf800);
	Show_RGB(0x07e0);	
	Show_RGB(0x001f);
*/
   // LCD_SetPos(48,68,29,69);
ClearScreen(0xf800);
//Show_RGB (0,240,0,320,0xf800);
/*Show_RGB (0,120,0,160,0x001f);
Show_RGB (0,120,161,320,0xffff);
Show_RGB (121,240,161,320,0x07e0);
Show_RGB (121,240,0,160,0x0000);
*/
//	show_colour_bar();	

LCD_PutString(40,40,"www.doflye.net",0x0000,0xffff);
LCD_PutString(40,60,"I LOVE MY JOB ",0x0000,0xf800);
LCD_PutString(10,80,"上海浩豚电子科技有限公司",0x0000,0xf800);
LCD_PutString(40,100,"专业技术支持论坛",0x07e0,0xf800);
LCD_PutString(40,120,"专业开发板工控板",0x001f,0xf800);
LCD_PutString(40,140,"1234567890",0x001f,0xf800);
LCD_PutString(0,160,"abcdefghijklmnopqistuvwxyz",0x001f,0xf800);
LCD_PutString(0,180,"`,./<>';:[]{}\|?)(-=+*&^%$",0x001f,0xf800);
//	show_colour_bar();	
//	show_photo();

		while(1);	


	}
}


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

/////////////////////////////////////////////////////////////
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


void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor) {

		LCD_PutChar8x16( x, y, c, fColor, bColor );
	}


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
//==================== 显示R G B 顔色 ====================//



void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color)
{
	unsigned int i,j;
	//address_set();
	LCD_SetPos(x0,x1,y0,y1);
	for (i=y0;i<=y1;i++)
	{
	   for (j=x0;j<=x1;j++)
	       Write_Data_U16(Color);

	}


}

//====================== 显示彩条 ======================//
void show_colour_bar (void)

{
	int V,H;
	LCD_SetPos(0,240,0,320);//320x240

	for(H=0;H<240;H++)
	{
		for(V=0;V<40;V++)
		Write_Data(0xf8,0x00);
	}

	for(H=0;H<240;H++)
	{
		for(V=40;V<80;V++)
		Write_Data(0x07,0xe0);
	}

	for(H=0;H<240;H++)
	{
		for(V=80;V<120;V++)
		Write_Data(0x00,0x1f);
	}

	for(H=0;H<240;H++)
	{
		for(V=120;V<160;V++)
		Write_Data(0xff,0xe0);
	}

	for(H=0;H<240;H++)
	{
		for(V=160;V<200;V++)
		Write_Data(0xf8,0x1f);
	}

	for(H=0;H<240;H++)
	{
		for(V=200;V<240;V++)
		Write_Data(0x07,0xff);
	}

	for(H=0;H<240;H++)
	{
		for(V=240;V<280;V++)
		Write_Data(0xff,0xff);
	}

	for(H=0;H<240;H++)
	{
		for(V=280;V<320;V++)
		Write_Data(0x00,0x00);
	}

}

void show_photo(void)
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

//=======================================================//



void  Write_Cmd_Data (unsigned char x,unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Cmd(0x00,x);
	Write_Data(m,n);

}


void  Write_Data_U16(unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Data(m,n);

}
//====================== 写命令 ==========================//

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

//===================== 写数据 ===========================//

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





//=======================================================
void delayms(unsigned int count)
{
    int i,j;                                                                                
    for(i=0;i<count;i++)                                                                    
       {
	     for(j=0;j<260;j++);
       }                                                                                     
}



//===================== 初始化代码 =======================//

void ILI9325_Initial(void)
{ 


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

 





/*===========================================================*/

/*************************************************************
函数名称:LCD_DefineDispWindow
功    能:定义显示窗体
参    数:x0:  窗体中X坐标中较小者
	 x1:  窗体中X坐标中较大者
	 y0:  窗体中Y坐标中较小者
	 y1:  窗体中Y坐标中较大者 
返 回 值:无
*************************************************************/
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
