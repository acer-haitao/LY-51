/*-----------------------------------------------
˵�����˳���ʹ�ñ�׼PS2�������룬LCD1602Һ���������ʾ����������������ʹ��
����ʹ��12M����11.0592M,������ʹ�ò�����ĸ�����ֲ��ԣ�������������ʹ�ã���
������������չ�����ڿ�����ͳ���ĸ��ֲ�����������û��ʹ����żУ�飬����֤û��
����,У�������������ӡ�
-------------------------------------------------*/

#include<reg52.h>        //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include "scancodes.h"
#include "ps2.h"
#include "1602.h"

sbit Key_Data = P3^3 ;   //����Keyboard����
sbit Key_CLK  = P3^2;      //ʹ���ж�


bit BF=0;          
bit Shift;               //�����ϵ�����־
bit Key_UP;              //����ͨ������־
unsigned char KeyV;
unsigned char IntNum;
unsigned char DisNum;

/*-----------------------------------------------
              �ⲿ�ж϶�����Ϣ
-----------------------------------------------*/
void Keyboard_out(void) interrupt 0
{
if ((IntNum > 0) && (IntNum < 9))
   { 
	KeyV = KeyV >> 1;                //����������ǵ�>>�ߣ������һ����������һλ
	if (Key_Data)
    	KeyV = KeyV | 0x80;          //������������Ϊ1ʱ�����λ
	}
	IntNum++;
	while (!Key_CLK);                //�ȴ�PS/2CLK����

	if (IntNum > 10)
	   { 
 		IntNum = 0;                  //���ж�11�κ��ʾһ֡�������꣬�����׼����һ�ν���
 		BF = 1;                      //��ʶ���ַ���������
		EA = 0;                      //���жϵ���ʾ����ٿ��ж� 
		}
}

/*-----------------------------------------------
                ������Ϣ
ע��:��SHIFT+GΪ12H 34H F0H 34H F0H 12H
Ҳ����˵shift��ͨ��+G��ͨ��+shift�Ķ���+G�Ķ���
-----------------------------------------------*/
void Decode(unsigned char ScanCode) //
{
unsigned char TempCyc,Val; 
if (!Key_UP)                        //�����̰���ʱ
	{
	switch (ScanCode)
			{
			case 0xF0 :             // ���յ�0xF0��Key_UP��1��ʾ���뿪ʼ
				Key_UP = 1;
				break;

			case 0x12 :             // �� SHIFT
				Shift = 1;
				break;

			case 0x59 :             // �� SHIFT
				Shift = 1;
				break;

			default: 
				if(!Shift)          //���SHIFTû����
					{
					for (TempCyc = 0;(UnShifted[TempCyc][0]!=ScanCode)&&(TempCyc<59); TempCyc++); //�����ʾ
					if (UnShifted[TempCyc][0] == ScanCode)
						{
   						Val= UnShifted[TempCyc][1];
						LCD_Write_Char(DisNum%16,DisNum/16,Val);
						DisNum++;
   						if(DisNum==33)
     					  {
	  					  LCD_Clear(); //����
	  					  DisNum=0;    //��ͷд����
	 				      }
 					     }
                     } 
				else //����SHIFT
                    {
					for(TempCyc = 0; (Shifted[TempCyc][0]!=ScanCode)&&(TempCyc<59); TempCyc++); //�����ʾ
					if (Shifted[TempCyc][0] == ScanCode)
                       {
  						Val= Shifted[TempCyc][1];
                        LCD_Write_Char(DisNum%16,DisNum/16,Val);
						DisNum++;
   						if(DisNum==33)
     					  {
	  					  LCD_Clear(); //����
	  					  DisNum=0;    //��ͷд����
	 				      }
  						}
                      }
					break;
 			}
	}
else
	{ 
	Key_UP = 0;
	switch (ScanCode) //�����ɿ�ʱ���������룬��G 34H F0H 34H ��ô�ڶ���34H���ᱻ����
			{
			case 0x12 : // �� SHIFT
				Shift = 0;
				break;

			case 0x59 : // �� SHIFT
				Shift = 0;
				break;
			}
	}
BF = 0; //��ʶ�ַ���������

} 

/*-----------------------------------------------
     ps2��ʼ����ʵ�ʳ�ʼ���ⲿ�жϣ�
-----------------------------------------------*/
void PS2_Init(void)
{
 IT1 = 0;                              //���ⲿ�ж�1Ϊ�͵�ƽ����
 EA = 1;                               //�ⲿ�жϿ�
 EX0 = 1;                              //���ж�
}
/*-----------------------------------------------
                   ��ȡ����ֵ
-----------------------------------------------*/
void Read_KeyBoard(void)
{

 if (BF)
   Decode(KeyV);
 else
   EA = 1; //���ж�
}

