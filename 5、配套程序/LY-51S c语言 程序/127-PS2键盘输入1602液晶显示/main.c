/*-----------------------------------------------
  名称：PS2键盘lcd1602显示
  论坛：www.doflye.net
  编写：shifang
  日期：2009.5
  修改：无
  内容：测试Ps2键盘读入信息  
------------------------------------------------*/
#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
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
  Read_KeyBoard(); //读取键盘值，循环显示到液晶
 }
}
