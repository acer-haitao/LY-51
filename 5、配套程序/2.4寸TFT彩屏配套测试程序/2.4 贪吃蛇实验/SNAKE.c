/***********************************************************************************
/* �ļ����ƣ�	SNAKE.c
/* ��	 �ܣ�	̰������Ϸ����
/* ��	 ����	������(ԭ����)
/* ʱ	 �䣺	2009��10��11��
/* ��	 ע��
/*               ��Ϸ����������Ҫ���ٵ���Ӧ�����а���ͨ��������չΪ�жϰ���
/*               LCD Һ����ʾ����PO�� ��Ҫ��������
/***********************************************************************************/

#include <reg52.H>  
#include <KEY_SWEEP.H> 
#include"9325tp.h"
#include "SNAKE.h"


#define uchar unsigned char
//=================================================================
//    ʹ�ýṹ�嶨�����   ʹ��������Ƹ��ӵ����
//=================================================================
struct 
{
	uchar X;
	uchar Y;			 
	uchar Yes;
}Food;	//ʳ��ṹ��

#define SNAKE_Max_Long 20                 //��󳤶�
struct 
{
	uchar X[SNAKE_Max_Long];
	uchar Y[SNAKE_Max_Long];
	uchar Long;  
	uchar Life; 
	uchar Score;					//�ߵķ���
	uchar Level;					//�ߵĵȼ�              
}Snake;	//�߽ṹ��

uchar Key_V_temp=0;     				//ȡ���ϴΰ���ֵ

//=================================================================
//�������ܣ�1ms��ʱ����
//��    ��11.0592	M
//��ڲ�����n
//���ڲ�������
//=================================================================
void Delay_1mS(unsigned int n)
{
	unsigned int  i;
	unsigned char j;
	
	for(i=0;i<n;i++)
		for(j=0;j<120;j++) 	;
}

//=================================================================
//�������ƣ�void Init_time0 (void)
//�������ܣ���ʼ����ʱ��1  ���ڲ������������ �����ڷ���ʵ��
//��ڲ�������
//���ڲ�������
//=================================================================
void Init_time0 (void)
{
	EA=1;
	ET1=1;
	TMOD|=0x10;
	TH1=0X00;
	TL1=0X00;
	TR1=1;
}
void time1 (void) interrupt  3
{
	TH1=0X00;
	TL1=0X00;
}


//=================================================================
//�������ƣ�Trun_On_Point     Trun_Off_Point (uchar x,uchar y)
//�������ܣ���������Ϩ�� һ���㡣������ʾ������
//��ڲ�������
//���ڲ�������
//�ر�˵������ Trun_On���������������ľͿ��Լ���������Һ��
//          ��8*8 ����   12864 ��
//=================================================================
void Trun_On_Point (uchar x,uchar y,uchar color)
{
	Bar((4*(x+2)),(4*(y+2)),(4*(x+3)),(4*(y+3)),color);
}

void Trun_Off_Point (uchar x,uchar y)
{
	Bar((4*(x+2)),(4*(y+2)),(4*(x+3)),(4*(y+3)),0xBE5F);	
}

//=================================================================
//�������ƣ�void Init_SNAKE(void)  
//�������ܣ�������Ϸ���棬��ʼ����Ϸ�ȼ��Ȳ���
//��ڲ�������
//���ڲ�������
//=================================================================
void Init_SNAKE(void)   
{
	uchar i;

	Init_time0();
	//***********������Ϸ����********************//
	CLR_Screen(0xBE5F);
	Rectangle(8,8-1,85,120,0xaa);//����һ�����ο�, 0-127
 	LCD_PutString(88,8,"Score",0x00ff,0xBE5F);
	LCDShow_uCharNumber(96,24,Snake.Score,0x00ff,0xBE5F);
 	LCD_PutString(88,81,"LEVEL",0x00ff,0xBE5F);
	LCDShow_uCharNumber(96,97,Snake.Level,0x00ff,0xBE5F);

	//***********��ʼ���߲���********************//
	Snake.Long=2;	    			//�����ʼ���ߵĳ���
	Snake.Life=0;	    			//��ʼ���߻�����
	Snake.Score=0;
	Food.Yes=1;					
	Key_Value=0;
    Key_V_temp=0;

	for(i=0;i<Snake.Long;i++)		//���߸���ֵ
	{
		Snake.X[i]=i+2;
		Snake.Y[i]=2;
	}							
	for(i=0;i<Snake.Long;i++)		//���߸�������
	{
		Trun_On_Point(Snake.X[i],Snake.Y[i],0xaa);
	}							
}
//=================================================================
//�������ƣ�void Display_dead(uchar i) 
//�������ܣ���ʾ��������
//��ڲ�������
//���ڲ�������
//=================================================================
void Display_dead(void)
{

	LCD_PutString(10,40,"GAME OVER",0x00ff,0xBE5F); 
	while(Key_Value!=Key_Enter)
	     {
		  Key();
		 }
	Init_SNAKE();
}

//=================================================================
//�������ƣ�void Display_Pass(uchar i)
//�������ܣ���ʾ���ؽ���
//��ڲ�������
//���ڲ�������
//=================================================================
void Display_Pass(void)
{
	Snake.Level++;	
	LCD_PutString(18,40,"You are",0xcc88,0xBE5F); 
	LCD_PutString(34,56,"WIN!",0xcc88,0xBE5F); 
	while(Key_Value!=Key_Enter)
	     {
		  Key();
		 }
	Init_SNAKE();
}
//=================================================================
//�������ƣ�void Run_SNAKE(void)
//�������ܣ����˶����� ����Ϸ������
//��ڲ�������
//���ڲ�������
//=================================================================
void Run_SNAKE(void)
{
	uchar i=0;

	/*********************���ݰ���ѡ���ߵ��˶�����*******************/
	if((Key_Value==Key_Right&&Key_V_temp!=Key_Left)||(Key_Value==Key_Left&&Key_V_temp==Key_Right))
	{
		Trun_Off_Point(Snake.X[0],Snake.Y[0]); 	       //�Ȱ���β��Ϩ��� 

		for(i=0;i<Snake.Long-1;i++)                    //��������ǰһ�ε������λ��
		{
			Snake.X[i]=Snake.X[i+1];
			Snake.Y[i]=Snake.Y[i+1];
		} 

		Snake.X[Snake.Long-1]=Snake.X[Snake.Long-2]+1;
		Snake.Y[Snake.Long-1]=Snake.Y[Snake.Long-2]+0; //��ͷ����Ҫ��ķ����ƶ�
		
		for(i=0;i<Snake.Long;i++)			            //���������ʾ�����ĺ���
		{
			Trun_On_Point(Snake.X[i],Snake.Y[i],0xaa);
		}
		Key_V_temp=Key_Right;
	}

	if((Key_Value==Key_Left&&Key_V_temp!=Key_Right)||(Key_Value==Key_Right&&Key_V_temp==Key_Left))
	{

		Trun_Off_Point(Snake.X[0],Snake.Y[0]); 		   //�Ȱ���β��Ϩ��� 
		
		for(i=0;i<Snake.Long-1;i++)                     //��������ǰһ�ε������λ��
		{
			Snake.X[i]=Snake.X[i+1];
			Snake.Y[i]=Snake.Y[i+1];
		} 
		
		Snake.X[Snake.Long-1]=Snake.X[Snake.Long-2]-1;
		Snake.Y[Snake.Long-1]=Snake.Y[Snake.Long-2]+0; //��ͷ����Ҫ��ķ����ƶ�
		
		for(i=0;i<Snake.Long;i++)			            //���������ʾ�����ĺ���
		{
			Trun_On_Point(Snake.X[i],Snake.Y[i],0xaa);
		}
		Key_V_temp=Key_Left;
	}
	if(( Key_Value==Key_Up&&Key_V_temp!=Key_Down)||( Key_Value==Key_Down&&Key_V_temp==Key_Up))
	{
		Trun_Off_Point(Snake.X[0],Snake.Y[0]); 		  //�Ȱ���β��Ϩ��� 
		
		for(i=0;i<Snake.Long-1;i++)                   //��������ǰһ�ε������λ��
		{
			Snake.X[i]=Snake.X[i+1];
			Snake.Y[i]=Snake.Y[i+1];
		} 
		
		Snake.X[Snake.Long-1]=Snake.X[Snake.Long-2]+0;
		Snake.Y[Snake.Long-1]=Snake.Y[Snake.Long-2]-1; //��ͷ����Ҫ��ķ����ƶ�
		
		for(i=0;i<Snake.Long;i++)			           //���������ʾ�����ĺ���
		{
			Trun_On_Point(Snake.X[i],Snake.Y[i],0xaa);
		}
		Key_V_temp=Key_Up;
	}
	if(( Key_Value==Key_Down&&Key_V_temp!=Key_Up)||( Key_Value==Key_Up&&Key_V_temp==Key_Down))
	{
		Trun_Off_Point(Snake.X[0],Snake.Y[0]); 		 //�Ȱ���β��Ϩ��� 
		
		for(i=0;i<Snake.Long-1;i++)                  //��������ǰһ�ε������λ��
		{
			Snake.X[i]=Snake.X[i+1];
			Snake.Y[i]=Snake.Y[i+1];
		} 
		
		Snake.X[Snake.Long-1]=Snake.X[Snake.Long-2]+0;
		Snake.Y[Snake.Long-1]=Snake.Y[Snake.Long-2]+1; //��ͷ����Ҫ��ķ����ƶ�
		
		for(i=0;i<Snake.Long;i++)			           //���������ʾ�����ĺ���
		{
			Trun_On_Point(Snake.X[i],Snake.Y[i],0xaa);
		}
		Key_V_temp=Key_Down;
	}
	

	/****************���ݰ���ѡ���ߵ��˶��������*******************/
	/////////////////////////////////////////////////////////////////

	
	/************************�ж����Ƿ�����***********************/
	if(Snake.X[Snake.Long-1]>=19||Snake.Y[Snake.Long-1]>=28)//����ͷ�Ƿ�ײ��ǽ��
	{
		Snake.Life=1;
	}
	for(i=3;i<Snake.Long;i++)//�ӵ����ڿ�ʼ�ж���ͷ�Ƿ�ҧ���Լ�
	{
		if(Snake.X[i]==Snake.X[0]&&Snake.Y[i]==Snake.Y[0])
		{
			Snake.Life=1;
		}
	}
	if(Snake.Life==1)	  //if the snake over
	{
		
		Display_dead();
	}
	/******************�ж����Ƿ������������***********************/
	/////////////////////////////////////////////////////////////////


	/************************�ж����Ƿ����**********************/
	if(Snake.Long==SNAKE_Max_Long)
	{
		
		Display_Pass();
	}
	/////////////////////////////////////////////////////////////////										   

	/*************************�����Ƿ�Ե�ʳ��**********************/		
	if(Snake.X[Snake.Long-1]==Food.X&&Snake.Y[Snake.Long-1]==Food.Y)//
	{
		//Trun_Off_Point(Food.X,Food.Y); 		 //����ʳ��
		Snake.Long++;//�߽�����1
		Snake.X[Snake.Long-1]=Food.X;
		Snake.Y[Snake.Long-1]=Food.Y;
		Snake.Score+=10;
		LCDShow_uCharNumber(96,24,Snake.Score,0x00ff,0xBE5F);
		Food.Yes=1;  //ʳ���־��1
	}
	/////////////////////////////////////////////////////////////////
	

	/***************************�Ź��ӳ���*************************/
	if(Food.Yes==0)
	{
		Trun_On_Point(Food.X,Food.Y,0xaa);
	}											   
	if(Food.Yes==1)
	{
		while(1)
		{
			Food.X=((TL1&0X24)>>1);      			//��������
			Food.Y=TL1&0X1B;

		    for(i=0;i<Snake.Long;i++)				//�жϲ�����ʳ�������Ƿ�������غ�
			{
				if((Food.X==Snake.X[i])&&(Food.X==Snake.Y[i]))
					break;
			}
			if(i==Snake.Long)
			{
				Food.Yes=0;
				break;								//������Ч��ʳ������
			}
		}
	}
	/////////////////////////////////////////////////////////////////


    /**************************��ʱ���ڵ�����Ϸ�ٶ�************************/
	Delay_1mS(300-Snake.Level*50);
	/////////////////////////////////////////////////////////////////			
}


