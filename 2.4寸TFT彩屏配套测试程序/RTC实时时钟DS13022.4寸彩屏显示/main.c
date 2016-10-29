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
#include"9325TP.h"



bit SetFlag;      //����ʱ���־λ
unsigned char time_buf2[16];
///////////////////////////////////////////////////////////////////////////////
void disp(void);
///////////////////////////////////////////////////////////////////////////////
void delay(unsigned int U)
{
 while(--U);
}
//////////////////////////////////////////////////////////////////////////////
void UART_Init(void)
{
    SCON  = 0x50;		        /* SCON: ģʽ 1, 8-bit UART, ʹ�ܽ���         */
    TMOD |= 0x20;               /* TMOD: timer 1, mode 2, 8-bit reload        */
    TH1   = 0xFD;               /* TH1:  reload value for 9600 baud @ 11.0592MHz   */
    TR1   = 1;                  /* TR1:  timer 1 run                          */
    EA    = 1;                  /*�����ж�*/
    ES    = 1;                  /*�򿪴����ж�*/

}
/////////////////////////////////////////////////////////////////////////////////
main()
{
  unsigned char i;

       UART_Init();
	  
       ds1302_init(); /*DS302��ʼ������*/
       //ds1302_write_time();
       ILI9325_Initial();  //��ʼ��LCD
       ClearScreen(0xff00);
	   LCD_PutString(80,100,"��ǰ����",0x00ff,0xff00);
       LCD_PutString(80,140,"��ǰʱ��",0x00ff,0xff00);

  while(1)
       {
	    ds1302_read_time();//��ȡʱ����Ϣ

           disp();         //Һ����ʾʱ����Ϣ

           //KeyPro();
		   if(SetFlag)     //������յ�������Ϣ�����ʱ��
		     {
			 for(i=0;i<8;i++)
			 {
			 time_buf1[i]=time_buf2[2*i]*10+time_buf2[2*i+1];//�������ϣ���2���� 1��5���ϳ�15
			 }
			 ds1302_write_time();
			 SetFlag=0;     //ʱ����Ϣ���º��־λ����
			 }
	     }
 
  }

/******************************************************************/
/*                  �����жϳ���                                  */
/******************************************************************/
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
	  //P1=Temp&0x0F; //����ʱ����ʾ
	 }
   if(TI)  //����Ƿ��ͱ�־λ������
     TI=0;
} 

////////////////////////////////////////////////////////////////////
void disp(void)

{
 
 unsigned char  FirstLine[10];

 FirstLine[0]='2';
 FirstLine[1]='0';
 FirstLine[2]='0'+time_buf1[1]/10;
 FirstLine[3]='0'+time_buf1[1]%10;
 FirstLine[4]='-';
 FirstLine[5]='0'+time_buf1[2]/10;
 FirstLine[6]='0'+time_buf1[2]%10;
 FirstLine[7]='-';
 FirstLine[8]='0'+time_buf1[3]/10;
 FirstLine[9]='0'+time_buf1[3]%10;

 LCD_PutString(80,120,FirstLine,0x00ff,0xff00);


 
 FirstLine[0]='0'+time_buf1[4]/10;
 FirstLine[1]='0'+time_buf1[4]%10;
 FirstLine[2]=':';
 FirstLine[3]='0'+time_buf1[5]/10;
 FirstLine[4]='0'+time_buf1[5]%10;
 FirstLine[5]=':';
 FirstLine[6]='0'+time_buf1[6]/10;
 FirstLine[7]='0'+time_buf1[6]%10;
 FirstLine[8]=' ';
 FirstLine[9]='0'+time_buf1[7]%10;


LCD_PutString(80,160,FirstLine,0x00ff,0xff00);



}
