
#include<reg52.h>     //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
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
/*                    ����˿�                                    */
/******************************************************************/

sbit DQ=P1^3;//ds18b20 �˿�

/******************************************************************/
/*                   ��������                                     */
/******************************************************************/
void delay1(uchar MS);
unsigned int ReadTemperature(void);
void Init_DS18B20(void);
unsigned char ReadOneChar(void);
void WriteOneChar(unsigned char dat);
void delay(unsigned int i);


#endif
