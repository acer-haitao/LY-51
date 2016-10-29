#ifndef __ILI9325_H__
#define __ILI9325_H__



//unsigned char code pic[];

void ILI9325_Initial(void);
void show_colour_bar (void);
void Write_Cmd_Data(unsigned char x, unsigned int y);
void Write_Cmd(unsigned char DH,unsigned char DL);
void Write_Data(unsigned char DH,unsigned char DL);
void delayms(unsigned int tt);
void show_photo(void);
void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color);

void  Write_Data_U16(unsigned int y);
static void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
void CLR_Screen(unsigned int bColor);
void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void LCD_PutString(unsigned short x, unsigned short y, char *s, unsigned int fColor, unsigned int bColor);
void LCD_PutChar8x8(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void Put_pixel(unsigned int x,unsigned int y,unsigned int color);
static void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
void Line(	unsigned int X0,
			unsigned int Y0,
			unsigned int X1,
			unsigned int Y1,
			unsigned int color);
void Rectangle( unsigned int left,
				unsigned int top,
				unsigned int right,
				unsigned int bottom,
				unsigned int color);

				
#endif
