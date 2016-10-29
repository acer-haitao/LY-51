
#include<reg52.h>     //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include<math.h>
#include<INTRINS.H>

#ifndef __18B20_H__
#define __18B20_H__


#ifndef uchar
#define uchar unsigned char 
#endif

#ifndef uint
#define uint unsigned int 
#endif
/******************************************************************/
/*                    定义端口                                    */
/******************************************************************/

sbit DQ=P1^3;//ds18b20 端口

/******************************************************************/
/*                   函数声明                                     */
/******************************************************************/
void delay1(uchar MS);
unsigned int ReadTemperature(void);
void Init_DS18B20(void);
unsigned char ReadOneChar(void);
void WriteOneChar(unsigned char dat);
void delay(unsigned int i);


#endif
