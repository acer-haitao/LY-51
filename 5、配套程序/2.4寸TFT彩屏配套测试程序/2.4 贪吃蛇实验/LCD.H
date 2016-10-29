#ifndef __LCD_H__
#define __LCD_H__


extern void Delayms(int) ;//廷时子程序
extern void WriteDAT(unsigned char a,unsigned char b);
extern void WriteCOM(unsigned char b);
extern void WriteDAT1(unsigned char b);
extern void Ini_ILI9163(void);
extern unsigned char code pic[];
extern void show_photo(void);
extern void  pause(void);
extern void SleepOut(void);
extern void SleepIn(void);
extern void display_hb(void);
extern void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor) ;



extern void SetXY(unsigned char x,unsigned char y);
extern void Put_pixel(unsigned char x,unsigned char y,unsigned int color);

extern void Line(	unsigned char X0,
			unsigned char Y0,
			unsigned char X1,
			unsigned char Y1,
			unsigned int color);

extern void Rectangle( unsigned char left,
				unsigned char top,
				unsigned char right,
				unsigned char bottom,
				unsigned int color);

extern void Bar(	unsigned char left,
			unsigned char top,
			unsigned char right,
			unsigned char bottom,
			unsigned int color);

extern void Bar3D( unsigned char left,
			unsigned char top,
			unsigned char right,
			unsigned char bottom,
			unsigned int color);

extern void LCDShow_uCharNumber(unsigned char x,
								unsigned char y,
								unsigned char uCharNumber,
								unsigned int  forecolor,
								unsigned int  bkcolor);


extern  void CLR_Screen(unsigned int color);
#endif

/*
		Put_pixel(0,0,0x2000); 		 //写入一个点
		Line(0,0,130,130,0xaa);		 //画一条线，起点（0，0）终点（130，130）颜色0xaa;
		Rectangle( 5,5,120,120,0xaa);//绘制一个矩形框,	  0-127
		Bar(5,5,120,120,0xff);       //填充一个矩形框     0-127
		Bar3D(5,5,120,120,0xff);	 //填充一个3D矩形框   0-127
	//	DispBMP(0,0,gImage_12);
*/