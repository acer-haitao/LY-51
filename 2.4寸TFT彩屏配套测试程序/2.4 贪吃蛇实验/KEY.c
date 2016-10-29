
#include <reg52.h>
#include <KEY_SWEEP.H>

unsigned char Key_Value=0;
unsigned char Key_flag =0;

/*
void Interrupt0_Key (void)
{
	IT0=1;            //�����½����д���
	EA=1;	          //�����ж�
	EX0=1;	          //���ⲿ�ж�
	Key_Port=0X0f;
}
*/							   
unsigned char code Key_code[]=
{
	//p0    p1   p2  p3
	0xee,0xed,0xeb,0xe7,   //p4
	0xde,0xdd,0xdb,0xd7,   //p5
	0xbe,0xbd,0xbb,0xb7,   //p6
	0x7e,0x7d,0x7b,0x77    //p7
};

//����Ϊ���룬����������˳��Ϳ��Ի�ص
void Key (void) 
{
	unsigned char 	KeyV_l,KeyV_h,KeyV,i;
			  	
	if(Key_Port!=0X0f)		  //0000 1111  �а�����ʱ��Ϳ�����0000 1110��
	{
		//Delay();
		if(Key_Port!=0X0f)		  //0000 1111  �а�����ʱ��Ϳ�����0000 1110��
		{
			KeyV_l=Key_Port&0x0f; //ȡ������� ��4λ
			Key_Port=0XF0;
			KeyV_h=Key_Port&0xf0; //ȡ������� ��4λ
			KeyV=KeyV_h+KeyV_l;	  //�ϲ�����
	
			/*************************************
		    ��������         ��Ӧ         ��ֵ
			Ee   ed   eb  e7		 1	5  9   13
			De   dd   db  d7		 2	6  10  14
			Be   bd   bb  b7		 3	7  11  15
			7e   7d   7b  77		 4	8  12  16
			*************************************/
			for(i=0;i<16;i++)   	//���ü�����Ҽ�ֵ
			{
				if(Key_code[i]==KeyV)
				Key_Value=(i+1);
			}
			Key_Port=0X0f;
		}
	}

	Key_flag =1;
}