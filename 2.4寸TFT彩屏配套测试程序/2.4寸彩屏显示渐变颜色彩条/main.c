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
  unsigned int color;
  unsigned  int x,y;
  ILI9325_Initial(); //��ʼ��LCD


//����ɫ32��ֵ��ÿ��һ����ɫ
 for (y=0;y<32;y++)
	{	
	   for (x=0;x<240;x++)
	       {
	       Show_RGB(x,x,y,y,y);
            }
	}
 //����ɫ64��ֵ��ÿ��һ����ɫ
 for (y=32;y<96;y++)
	{	
	   for (x=0;x<240;x++)
	       {
	       Show_RGB(x,x,y,y,(y-32)<<5);
            }
	}
 //����ɫ32��ֵ��ÿ��һ����ɫ
 for (y=96;y<128;y++)
	{	
	   for (x=0;x<240;x++)
	       {
	       Show_RGB(x,x,y,y,(y-96)<<11);
            }
	}
 //�����ۺ���ɫ32��ֵ��ÿ��һ����ɫ
 for (y=128;y<160;y++)
	{	
	   for (x=0;x<240;x++)
	       {
	       Show_RGB(x,x,y,y,((y-128)<<11 | (y-128)));
            }
	}
 //�����ۺ���ɫ32��ֵ��ÿ��һ����ɫ
  for (y=160;y<192;y++)
	{	
	   for (x=0;x<240;x++)
	       {
	       Show_RGB(x,x,y,y,((y-160)<<11 | (y-160)<<5));
            }
	}
 //�����ۺ���ɫ32��ֵ��ÿ��һ����ɫ
  for (y=192;y<224;y++)
	{	
	   for (x=0;x<240;x++)
	       {
	       Show_RGB(x,x,y,y,((y-192)<<5 | (y-192)));
            }
	}
 //�������ۺ���ɫ32��ֵ��ÿ��һ����ɫ
  for (y=224;y<256;y++)
	{	
	   for (x=0;x<240;x++)
	       {
	       Show_RGB(x,x,y,y,((y-224)<<11 | (y-224)<<5 | (y-224)));
            }
	}
  //����ɫ64��ֵ��ÿ��һ����ɫ
  for (y=256;y<320;y++)
	{	
	   for (x=0;x<240;x++)
	       {
	       Show_RGB(x,x,y,y,(y-256)<<5);
            }
	}
  while(1)
       {
	   
	   }
 
  }



