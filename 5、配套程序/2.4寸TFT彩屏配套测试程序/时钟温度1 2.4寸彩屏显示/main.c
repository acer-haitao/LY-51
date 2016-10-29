/*-----------------------------------------------
  名称：LCD1602显示实时时钟
  公司：上海浩豚电子科技有限公司
  网站：www.doflye.cn
  编写：师访
  日期：2009.5
  修改：无
  内容：通过读取ds1302信息直接显示到液晶屏上。有备用电池，断电后时间仍可以正常运行。通过串口调试软件更新时间。更新方式如下
        在发送栏填写时间信息，格式如下 2009071210102005 表示2009年7月12日 10点10分20秒 星期五，然后通过串口发送，硬件连接方式和
		串口通信相同。注意中间不能有空格
  -----------------------------------------------*/
#include<reg52.h>
#include"ds1302.h"
#include"9325tp.h"
#include "18b20.h"
/*-----------------------------------------------
                  全局变量
-----------------------------------------------*/
#define TOP    10
#define BOTTOM 10
#define LEFT   15
#define RIGHT  10
#define DISTANCE  20

#define CCOLOR 0xffff

#define BCOLOR 0x0000

unsigned int temp; //温度临时变量
unsigned char TempH,TempL;
bit SetFlag;       //更新时间标志位
unsigned char   time_buf2[16];
unsigned char timeold;
/*-----------------------------------------------
                  函数声明
-----------------------------------------------*/
void disp(void);
/*------------------------------------------------
              串口通讯初始化
------------------------------------------------*/
void UART_Init(void)
{
    SCON  = 0x50;		        // SCON: 模式 1, 8-bit UART, 使能接收  
    TMOD |= 0x20;               // TMOD: timer 1, mode 2, 8-bit 重装
    TH1   = 0xFD;               // TH1:  重装值 9600 波特率 晶振 11.0592MHz  
    TR1   = 1;                  // TR1:  timer 1 打开                         
    EA    = 1;                  //打开总中断
    ES    = 1;                  //打开串口中断
}

/*------------------------------------------------
                      主函数
------------------------------------------------*/
main()
{
  unsigned char i;

       UART_Init();
	   
       Ds1302_Init(); /*DS302初始化函数*/
       ILI9325_Initial(); //初始化LCD
       CLR_Screen(BCOLOR); //用背景色清屏
       //画矩形框
	   Rectangle(LEFT,TOP,LEFT+100,TOP+140,CCOLOR);
	   Rectangle(LEFT+1,TOP+1,LEFT+99,TOP+139,CCOLOR);

	   LCD_PutString(LEFT+10,TOP+10,"当前日期：",CCOLOR,BCOLOR);
       LCD_PutString(LEFT+10,DISTANCE*2+TOP+10,"当前时间：",CCOLOR,BCOLOR);
	   LCD_PutString(LEFT+10,DISTANCE*4+TOP+10,"星期",CCOLOR,BCOLOR);
	   LCD_PutString(LEFT+10,DISTANCE*5+TOP+12,"温度：   ℃",CCOLOR,BCOLOR);
       //画中间间隔线
	   Line(LEFT,TOP+DISTANCE+8,LEFT+100,TOP+DISTANCE+8,CCOLOR);
       Line(LEFT,TOP+DISTANCE*2+8,LEFT+100,TOP+DISTANCE*2+8,CCOLOR);
	   Line(LEFT,TOP+DISTANCE*3+8,LEFT+100,TOP+DISTANCE*3+8,CCOLOR);
	   Line(LEFT,TOP+DISTANCE*4+8,LEFT+100,TOP+DISTANCE*4+8,CCOLOR);
	   Line(LEFT,TOP+DISTANCE*5+8,LEFT+100,TOP+DISTANCE*5+8,CCOLOR);
  while(1)
       {
	    timeold=time_buf1[6]; // 用于检查时钟是否改变
	    Ds1302_Read_Time();//读取时钟信息

		if(timeold!=time_buf1[6])
		 {
         temp=ReadTemperature();//读取温度
		 TempH=temp>>4;
         TempL=temp&0x0F;
         TempL=TempL*6/10;//小数近似处理
         disp();         //液晶显示时间信息
         }
		   if(SetFlag)     //如果接收到串口信息则更新时钟
		     {
			 for(i=0;i<8;i++)
			 {
			 time_buf1[i]=time_buf2[2*i]*10+time_buf2[2*i+1];//数据整合，如2个数 1和5整合成15
			 }
			 Ds1302_Write_Time();
			 SetFlag=0;     //时钟信息更新后标志位清零
			 }
	     }
 
  }

/*------------------------------------------------
                  串口中断程序
------------------------------------------------*/
void UART_SER (void) interrupt 4 //串行中断服务程序
{
    unsigned char Temp;          //定义临时变量 
    unsigned char i;
    if(RI)                        //判断是接收中断产生
     {
	  RI=0;                      //标志位清零
	  Temp=SBUF;                 //读入缓冲区的值
	  time_buf2[i]=Temp&0x0F;
	  i++;
	  if(i==16)                  //连续接收16个字符信息
	   {
	    i=0;
		SetFlag=1;               //接收完成标志位置1
	   }
      SBUF=Temp; //把接收到的值再发回电脑端
	 }
   if(TI)  //如果是发送标志位，清零
     TI=0;
} 

/*------------------------------------------------
             显示处理函数
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
 case 1:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"一",CCOLOR,BCOLOR);break;
 case 2:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"二",CCOLOR,BCOLOR);break;
 case 3:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"三",CCOLOR,BCOLOR);break;
 case 4:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"四",CCOLOR,BCOLOR);break;
 case 5:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"五",CCOLOR,BCOLOR);break;
 case 6:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"六",CCOLOR,BCOLOR);break;
 case 7:LCD_PutString(LEFT+42,DISTANCE*4+TOP+10,"日",CCOLOR,BCOLOR);break;
 default:break;
}

 TempData[8]='0'+(TempH%100)/10;
 TempData[9]='0'+(TempH%100)%10; //这里只使用2位整数部分
LCD_PutString(LEFT+58,DISTANCE*5+TOP+12,&TempData[8],CCOLOR,BCOLOR);
}
