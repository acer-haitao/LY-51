/*-----------------------------------------------
  ���ƣ�PS2����lcd1602��ʾ
  ��̳��www.doflye.net
  ��д��shifang
  ���ڣ�2009.5
  �޸ģ���
  ���ݣ�����Ps2���̶�����Ϣ  
------------------------------------------------*/
#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include "delay.h"
#include "1602.h"
#include "ps2.h"

void main(void)
{


 LCD_Init();
 DelayMs(10);
 LCD_Clear();
 PS2_Init();
 LCD_Write_String(0,0,"www.doflye.net ");
 LCD_Write_String(0,1,"press the key! ");
 

 while(1)
 {
  Read_KeyBoard(); //��ȡ����ֵ��ѭ����ʾ��Һ��
 }
}
