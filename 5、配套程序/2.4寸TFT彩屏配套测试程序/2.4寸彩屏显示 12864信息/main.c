/*-----------------------------------------------
  ���ƣ�������ʾ����
  ��̳��www.doflye.net
  ��д��shifang
  ���ڣ�2009.5
  �޸ģ���
  ���ݣ�
  -----------------------------------------------*/
#include<reg52.h>
#include"9325tp.h"

/*-----------------------------------------------
                  ȫ�ֱ���
-----------------------------------------------*/
#define TOP    10
#define BOTTOM 10
#define LEFT   15
#define RIGHT  10
#define DISTANCE  20

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0




/*------------------------------------------------
                      ������
------------------------------------------------*/
main()
{
 // unsigned char i;

       ILI9325_Initial(); //��ʼ��LCD
       CLR_Screen(White); //�ñ���ɫ����
       //���ƾ���ƽ��
	   Show_RGB(0,120,0,64,Blue2);
	   Show_RGB(120,240,0,64,Black);
       Show_RGB(0,120,64,128,White);
       Show_RGB(120,240,64,128,Blue);
       Show_RGB(0,120,128,192,Red);
       Show_RGB(120,240,128,192,Magenta);
	   Show_RGB(0,120,192,256,Green);
	   Show_RGB(120,240,192,256,Cyan);
       Show_RGB(0,120,256,320,Yellow);
	   Show_RGB(120,240,256,320,Red);
       
	   LCD_PutString(0,0,"רҵ������̳",White,Blue2);
	   LCD_PutString(0,16,"www.doflye.net",White,Blue2);
	   LCD_PutString(0,32,"רҵ������",White,Blue2);
	   LCD_PutString(0,48,"������ӿƼ�",White,Blue2);

  while(1)
       {
	   
	   }
 
  }



