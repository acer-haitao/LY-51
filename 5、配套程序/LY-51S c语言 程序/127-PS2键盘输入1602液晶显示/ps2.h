#ifndef __PS2_H__
#define __PS2_H__


#include<reg52.h>        //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���


void PS2_Init(void);

void Read_KeyBoard(void);

void Decode(unsigned char ScanCode);

#endif


