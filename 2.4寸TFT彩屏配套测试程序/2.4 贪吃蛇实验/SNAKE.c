/***********************************************************************************
/* 文件名称：	SNAKE.c
/* 功	 能：	贪吃蛇游戏代码
/* 署	 名：	张先永(原作者)
/* 时	 间：	2009年10月11日
/* 备	 注：
/*               游戏按键由于需要快速的响应，所有按键通过线与扩展为中断按键
/*               LCD 液晶显示器在PO口 需要上拉电阻
/***********************************************************************************/

#include <reg52.H>  
#include <KEY_SWEEP.H> 
#include"9325tp.h"
#include "SNAKE.h"


#define uchar unsigned char
//=================================================================
//    使用结构体定义变量   使程序的名称更加的清楚
//=================================================================
struct 
{
	uchar X;
	uchar Y;			 
	uchar Yes;
}Food;	//食物结构体

#define SNAKE_Max_Long 20                 //最大长度
struct 
{
	uchar X[SNAKE_Max_Long];
	uchar Y[SNAKE_Max_Long];
	uchar Long;  
	uchar Life; 
	uchar Score;					//蛇的分数
	uchar Level;					//蛇的等级              
}Snake;	//蛇结构体

uchar Key_V_temp=0;     				//取出上次按键值

//=================================================================
//函数功能：1ms延时函数
//晶    振：11.0592	M
//入口参数：n
//出口参数：无
//=================================================================
void Delay_1mS(unsigned int n)
{
	unsigned int  i;
	unsigned char j;
	
	for(i=0;i<n;i++)
		for(j=0;j<120;j++) 	;
}

//=================================================================
//函数名称：void Init_time0 (void)
//函数功能：初始化定时器1  用于产生随机数种子 ，用于放置实物
//入口参数：无
//出口参数：无
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
//函数名称：Trun_On_Point     Trun_Off_Point (uchar x,uchar y)
//函数功能：点亮或者熄灭 一个点。用于显示蛇身体
//入口参数：无
//出口参数：无
//特别说明：此 Trun_On，函数换成其他的就可以兼容其他的液晶
//          入8*8 点阵   12864 等
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
//函数名称：void Init_SNAKE(void)  
//函数功能：绘制游戏界面，初始化游戏等级等参数
//入口参数：无
//出口参数：无
//=================================================================
void Init_SNAKE(void)   
{
	uchar i;

	Init_time0();
	//***********绘制游戏界面********************//
	CLR_Screen(0xBE5F);
	Rectangle(8,8-1,85,120,0xaa);//绘制一个矩形框, 0-127
 	LCD_PutString(88,8,"Score",0x00ff,0xBE5F);
	LCDShow_uCharNumber(96,24,Snake.Score,0x00ff,0xBE5F);
 	LCD_PutString(88,81,"LEVEL",0x00ff,0xBE5F);
	LCDShow_uCharNumber(96,97,Snake.Level,0x00ff,0xBE5F);

	//***********初始化蛇参数********************//
	Snake.Long=2;	    			//定义初始化蛇的长度
	Snake.Life=0;	    			//初始化蛇还活着
	Snake.Score=0;
	Food.Yes=1;					
	Key_Value=0;
    Key_V_temp=0;

	for(i=0;i<Snake.Long;i++)		//将蛇给赋值
	{
		Snake.X[i]=i+2;
		Snake.Y[i]=2;
	}							
	for(i=0;i<Snake.Long;i++)		//将蛇给画出来
	{
		Trun_On_Point(Snake.X[i],Snake.Y[i],0xaa);
	}							
}
//=================================================================
//函数名称：void Display_dead(uchar i) 
//函数功能：显示死亡界面
//入口参数：无
//出口参数：无
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
//函数名称：void Display_Pass(uchar i)
//函数功能：显示过关界面
//入口参数：无
//出口参数：无
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
//函数名称：void Run_SNAKE(void)
//函数功能：蛇运动函数 （游戏精华）
//入口参数：无
//出口参数：无
//=================================================================
void Run_SNAKE(void)
{
	uchar i=0;

	/*********************根据按键选择蛇的运动方向*******************/
	if((Key_Value==Key_Right&&Key_V_temp!=Key_Left)||(Key_Value==Key_Left&&Key_V_temp==Key_Right))
	{
		Trun_Off_Point(Snake.X[0],Snake.Y[0]); 	       //先把蛇尾给熄灭掉 

		for(i=0;i<Snake.Long-1;i++)                    //蛇身都是它前一段的蛇身的位置
		{
			Snake.X[i]=Snake.X[i+1];
			Snake.Y[i]=Snake.Y[i+1];
		} 

		Snake.X[Snake.Long-1]=Snake.X[Snake.Long-2]+1;
		Snake.Y[Snake.Long-1]=Snake.Y[Snake.Long-2]+0; //蛇头向你要求的方向移动
		
		for(i=0;i<Snake.Long;i++)			            //这个让蛇显示出来的函数
		{
			Trun_On_Point(Snake.X[i],Snake.Y[i],0xaa);
		}
		Key_V_temp=Key_Right;
	}

	if((Key_Value==Key_Left&&Key_V_temp!=Key_Right)||(Key_Value==Key_Right&&Key_V_temp==Key_Left))
	{

		Trun_Off_Point(Snake.X[0],Snake.Y[0]); 		   //先把蛇尾给熄灭掉 
		
		for(i=0;i<Snake.Long-1;i++)                     //蛇身都是它前一段的蛇身的位置
		{
			Snake.X[i]=Snake.X[i+1];
			Snake.Y[i]=Snake.Y[i+1];
		} 
		
		Snake.X[Snake.Long-1]=Snake.X[Snake.Long-2]-1;
		Snake.Y[Snake.Long-1]=Snake.Y[Snake.Long-2]+0; //蛇头向你要求的方向移动
		
		for(i=0;i<Snake.Long;i++)			            //这个让蛇显示出来的函数
		{
			Trun_On_Point(Snake.X[i],Snake.Y[i],0xaa);
		}
		Key_V_temp=Key_Left;
	}
	if(( Key_Value==Key_Up&&Key_V_temp!=Key_Down)||( Key_Value==Key_Down&&Key_V_temp==Key_Up))
	{
		Trun_Off_Point(Snake.X[0],Snake.Y[0]); 		  //先把蛇尾给熄灭掉 
		
		for(i=0;i<Snake.Long-1;i++)                   //蛇身都是它前一段的蛇身的位置
		{
			Snake.X[i]=Snake.X[i+1];
			Snake.Y[i]=Snake.Y[i+1];
		} 
		
		Snake.X[Snake.Long-1]=Snake.X[Snake.Long-2]+0;
		Snake.Y[Snake.Long-1]=Snake.Y[Snake.Long-2]-1; //蛇头向你要求的方向移动
		
		for(i=0;i<Snake.Long;i++)			           //这个让蛇显示出来的函数
		{
			Trun_On_Point(Snake.X[i],Snake.Y[i],0xaa);
		}
		Key_V_temp=Key_Up;
	}
	if(( Key_Value==Key_Down&&Key_V_temp!=Key_Up)||( Key_Value==Key_Up&&Key_V_temp==Key_Down))
	{
		Trun_Off_Point(Snake.X[0],Snake.Y[0]); 		 //先把蛇尾给熄灭掉 
		
		for(i=0;i<Snake.Long-1;i++)                  //蛇身都是它前一段的蛇身的位置
		{
			Snake.X[i]=Snake.X[i+1];
			Snake.Y[i]=Snake.Y[i+1];
		} 
		
		Snake.X[Snake.Long-1]=Snake.X[Snake.Long-2]+0;
		Snake.Y[Snake.Long-1]=Snake.Y[Snake.Long-2]+1; //蛇头向你要求的方向移动
		
		for(i=0;i<Snake.Long;i++)			           //这个让蛇显示出来的函数
		{
			Trun_On_Point(Snake.X[i],Snake.Y[i],0xaa);
		}
		Key_V_temp=Key_Down;
	}
	

	/****************根据按键选择蛇的运动程序结束*******************/
	/////////////////////////////////////////////////////////////////

	
	/************************判断蛇是否死亡***********************/
	if(Snake.X[Snake.Long-1]>=19||Snake.Y[Snake.Long-1]>=28)//判蛇头是否撞到墙壁
	{
		Snake.Life=1;
	}
	for(i=3;i<Snake.Long;i++)//从第三节开始判断蛇头是否咬到自己
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
	/******************判断蛇是否死亡程序结束***********************/
	/////////////////////////////////////////////////////////////////


	/************************判断蛇是否最长了**********************/
	if(Snake.Long==SNAKE_Max_Long)
	{
		
		Display_Pass();
	}
	/////////////////////////////////////////////////////////////////										   

	/*************************判蛇是否吃到食物**********************/		
	if(Snake.X[Snake.Long-1]==Food.X&&Snake.Y[Snake.Long-1]==Food.Y)//
	{
		//Trun_Off_Point(Food.X,Food.Y); 		 //消隐食物
		Snake.Long++;//蛇节数加1
		Snake.X[Snake.Long-1]=Food.X;
		Snake.Y[Snake.Long-1]=Food.Y;
		Snake.Score+=10;
		LCDShow_uCharNumber(96,24,Snake.Score,0x00ff,0xBE5F);
		Food.Yes=1;  //食物标志置1
	}
	/////////////////////////////////////////////////////////////////
	

	/***************************放果子程序*************************/
	if(Food.Yes==0)
	{
		Trun_On_Point(Food.X,Food.Y,0xaa);
	}											   
	if(Food.Yes==1)
	{
		while(1)
		{
			Food.X=((TL1&0X24)>>1);      			//获得随机数
			Food.Y=TL1&0X1B;

		    for(i=0;i<Snake.Long;i++)				//判断产生的食物坐标是否和蛇身重合
			{
				if((Food.X==Snake.X[i])&&(Food.X==Snake.Y[i]))
					break;
			}
			if(i==Snake.Long)
			{
				Food.Yes=0;
				break;								//产生有效的食物坐标
			}
		}
	}
	/////////////////////////////////////////////////////////////////


    /**************************延时用于调整游戏速度************************/
	Delay_1mS(300-Snake.Level*50);
	/////////////////////////////////////////////////////////////////			
}


