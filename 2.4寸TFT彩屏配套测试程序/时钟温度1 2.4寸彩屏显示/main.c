/*-----------------------------------------------
  ���ƣ�LCD1602��ʾʵʱʱ��
  ��˾���Ϻ�������ӿƼ����޹�˾
  ��վ��www.doflye.cn
  ��д��ʦ��
  ���ڣ�2009.5
  �޸ģ���
  ���ݣ�ͨ����ȡds1302��Ϣֱ����ʾ��Һ�����ϡ��б��õ�أ��ϵ��ʱ���Կ����������С�ͨ�����ڵ����������ʱ�䡣���·�ʽ����
        �ڷ�������дʱ����Ϣ����ʽ���� 2009071210102005 ��ʾ2009��7��12�� 10��10��20�� �����壬Ȼ��ͨ�����ڷ��ͣ�Ӳ�����ӷ�ʽ��
		����ͨ����ͬ��ע���м䲻���пո�
  -----------------------------------------------*/
#include<reg52.h>
#include"ds1302.h"
#include"9325tp.h"
#include "18b20.h"
/*-----------------------------------------------
                  ȫ�ֱ���
-----------------------------------------------*/
#define TOP    10
#define BOTTOM 10
#define LEFT   15
#define RIGHT  10
#define DISTANCE  20

#define CCOLOR 0xffff

#define BCOLOR 0x0000

unsigned int temp; //�¶���ʱ����
unsigned char TempH,TempL;
bit SetFlag;       //����ʱ���־λ
unsigned char   time_buf2[16];
unsigned char timeold;
/*-----------------------------------------------
                  ��������
-----------------------------------------------*/
void disp(void);
/*------------------------------------------------
              ����ͨѶ��ʼ��
------------------------------------------------*/
void UART_Init(void)
{
    SCON  = 0x50;		        // SCON: ģʽ 1, 8-bit UART, ʹ�ܽ���  
    TMOD |= 0x20;               // TMOD: timer 1, mode 2, 8-bit ��װ
    TH1   = 0xFD;               // TH1:  ��װֵ 9600 ������ ���� 11.0592MHz  
    TR1   = 1;                  // TR1:  timer 1 ��                         
    EA    = 1;                  //�����ж�
    ES    = 1;                  //�򿪴����ж�
}

/*------------------------------------------------
                      ������
------------------------------------------------*/
main()
{
  unsigned char i;

       UART_Init();
	   
       Ds1302_Init(); /*DS302��ʼ������*/
       ILI9325_Initial(); //��ʼ��LCD
       CLR_Screen(BCOLOR); //�ñ���ɫ����
       //�����ο�
	   Rectangle(LEFT,TOP,LEFT+100,TOP+140,CCOLOR);
	   Rectangle(LEFT+1,TOP+1,LEFT+99,TOP+139,CCOLOR);

	   LCD_PutString(LEFT+10,TOP+10,"��ǰ���ڣ�",CCOLOR,BCOLOR);
       LCD_PutString(LEFT+10,DISTANCE*2+TOP+10,"��ǰʱ�䣺",CCOLOR,BCOLOR);
	   LCD_PutString(LEFT+10,DISTANCE*4+TOP+10,"����",CCOLOR,BCOLOR);
	   LCD_PutString(LEFT+10,DISTANCE*5+TOP+12,"�¶ȣ�   ��",CCOLOR,BCOLOR);
       //���м�����
	   Line(LEFT,TOP+DISTANCE+8,LEFT+100,TOP+DISTANCE+8,CCOLOR);
       Line(LEFT,TOP+DISTANCE*2+8,LEFT+100,TOP+DISTANCE*2+8,CCOLOR);
	   Line(LEFT,TOP+DISTANCE*3+8,LEFT+100,TOP+DISTANCE*3+8,CCOLOR);
	   Line(LEFT,TOP+DISTANCE*4+8,LEFT+100,TOP+DISTANCE*4+8,CCOLOR);
	   Line(LEFT,TOP+DISTANCE*5+8,LEFT+100,TOP+DISTANCE*5+8,CCOLOR);
  while(1)
       {
	    timeold=time_buf1[6]; // ���ڼ��ʱ���Ƿ�ı�
	    Ds1302_Read_Time();//��ȡʱ����Ϣ

		if(timeold!=time_buf1[6])
		 {
         temp=ReadTemperature();//��ȡ�¶�
		 TempH=temp>>4;
         TempL=temp&0x0F;
         TempL=TempL*6/10;//С�����ƴ���
         disp();         //Һ����ʾʱ����Ϣ
         }
		   if(SetFlag)     //������յ�������Ϣ�����ʱ��
		     {
			 for(i=0;i<8;i++)
			 {
			 time_buf1[i]=time_buf2[2*i]*10+time_buf2[2*i+1];//�������ϣ���2���� 1��5���ϳ�15
			 }
			 Ds1302_Write_Time();
			 SetFlag=0;     //ʱ����Ϣ���º��־λ����
			 }
	     }
 
  }

/*------------------------------------------------
                  �����жϳ���
------------------------------------------------*/
void UART_SER (void) interrupt 4 //�����жϷ������
{
    unsigned char Temp;          //������ʱ���� 
    unsigned char i;
    if(RI)                        //�ж��ǽ����жϲ���
     {
	  RI=0;                      //��־λ����
	  Temp=SBUF;                 //���뻺������ֵ
	  time_buf2[i]=Temp&0x0F;
	  i++;
	  if(i==16)                  //��������16���ַ���Ϣ
	   {
	    i=0;
		SetFlag=1;               //������ɱ�־λ��1
	   }
      SBUF=Temp; //�ѽ��յ���ֵ�ٷ��ص��Զ�
	 }
   if(TI)  //����Ƿ��ͱ�־λ������
     TI=0;
} 

/*------------------------------------------------
             ��ʾ������
------------------------------------------------*/
void disp(void)

{
 
 unsigned char  TempData[10];

 TempData[0]='2';
 TempData[1]='0';
 TempData[2]='0'+time_buf1[1]/10;
 TempData[3]='0'+time_buf1[1]%10;
 TempData[4]='-';
 TempData[5]='0'+time_buf1[2]/10;
 TempData[6]='0'+time_buf1[2]%10;
 TempData[7]='-';
 TempData[8]='0'+time_buf1[3]/10;
 TempData[9]='0'+time_buf1[3]%10;

 LCD_PutString(LEFT+10,DISTANCE+TOP+10,TempData,CCOLOR,BCOLOR);


 
 TempData[0]='0'+time_buf1[4]/10;
 TempData[1]='0'+time_buf1[4]%10;
 TempData[2]=':';
 TempData[3]='0'+time_buf1[5]/10;
 TempData[4]='0'+time_buf1[5]%10;
 TempData[5]=':';
 TempData[6]='0'+time_buf1[6]/10;
 TempData[7]='0'+time_buf1[6]%10;
 TempData[8]=' ';
 TempData[9]=' ';

LCD_PutString(LEFT+10,DISTANCE*3+TOP+10,TempData,CCOLOR,BCOLOR);

switch(time_buf1[7])
{
 case 1:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"һ",CCOLOR,BCOLOR);break;
 case 2:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"��",CCOLOR,BCOLOR);break;
 case 3:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"��",CCOLOR,BCOLOR);break;
 case 4:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"��",CCOLOR,BCOLOR);break;
 case 5:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"��",CCOLOR,BCOLOR);break;
 case 6:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"��",CCOLOR,BCOLOR);break;
 case 7:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"��",CCOLOR,BCOLOR);break;
 default:break;
}

 TempData[8]='0'+(TempH%100)/10;
 TempData[9]='0'+(TempH%100)%10; //����ֻʹ��2λ��������
LCD_PutString(LEFT+58,DISTANCE*5+TOP+12,&TempData[8],CCOLOR,BCOLOR);
}
