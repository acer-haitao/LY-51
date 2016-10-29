
#include <reg52.h>
#include<intrins.h>



sbit SCK=P3^6;		
sbit SDA=P3^4;		
sbit RST=P3^5;
/*��λ��*/
#define RST_CLR	RST=0/*��ƽ�õ�*/
#define RST_SET	RST=1/*��ƽ�ø�*/


/*˫������*/
#define IO_CLR	SDA=0/*��ƽ�õ�*/
#define IO_SET	SDA=1/*��ƽ�ø�*/
#define IO_R	SDA/*��ƽ��ȡ*/


/*ʱ���ź�*/
#define SCK_CLR	SCK=0/*ʱ���ź�*/
#define SCK_SET	SCK=1/*��ƽ�ø�*/


#define ds1302_sec_add			0x80		//�����ݵ�ַ
#define ds1302_min_add			0x82		//�����ݵ�ַ
#define ds1302_hr_add			0x84		//ʱ���ݵ�ַ
#define ds1302_date_add			0x86		//�����ݵ�ַ
#define ds1302_month_add		0x88		//�����ݵ�ַ
#define ds1302_day_add			0x8a		//�������ݵ�ַ
#define ds1302_year_add			0x8c		//�����ݵ�ַ
#define ds1302_control_add		0x8e		//�������ݵ�ַ
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

unsigned char time_buf1[8] = {20,9,3,13,18,51,00,6};//��������ʱ������
unsigned char time_buf[8] ;//��������ʱ������
/*��DS1302д��һ�ֽ�����*/
void ds1302_write_byte(unsigned char addr, unsigned char d) {

	unsigned char i;
	RST_SET;					/*����DS1302����*/
	
	/*д��Ŀ���ַ��addr*/
	addr = addr & 0xFE;/*���λ����*/
	for (i = 0; i < 8; i ++) {
	    
		if (addr & 0x01) {
			IO_SET;
			}
		else {
			IO_CLR;
			}
		SCK_SET;
		SCK_CLR;
		addr = addr >> 1;
		}
	
	/*д�����ݣ�d*/
	for (i = 0; i < 8; i ++) {
	    
		if (d & 0x01) {
			IO_SET;
			}
		else {
			IO_CLR;
			}
		SCK_SET;
		SCK_CLR;
		d = d >> 1;
		}
	RST_CLR;					/*ֹͣDS1302����*/
}

/*��DS1302����һ�ֽ�����*/
unsigned char ds1302_read_byte(unsigned char addr) {

	unsigned char i;
	unsigned char temp;
	RST_SET;					/*����DS1302����*/

	/*д��Ŀ���ַ��addr*/
	addr = addr | 0x01;/*���λ�ø�*/
	for (i = 0; i < 8; i ++) {
	     
		if (addr & 0x01) {
			IO_SET;
			}
		else {
			IO_CLR;
			}
		SCK_SET;
		SCK_CLR;
		addr = addr >> 1;
		}
	
	/*������ݣ�temp*/
	for (i = 0; i < 8; i ++) {
		temp = temp >> 1;
		if (IO_R) {
			temp |= 0x80;
			}
		else {
			temp &= 0x7F;
			}
		SCK_SET;
		SCK_CLR;
		}
	
	RST_CLR;					/*ֹͣDS1302����*/
	return temp;
}

/*��DS302д��ʱ������*/
void ds1302_write_time(void) {
     
    unsigned char i,tmp;
	for(i=0;i<8;i++){           //BCD����
		tmp=time_buf1[i]/10;
		time_buf[i]=time_buf1[i]%10;
		time_buf[i]=time_buf[i]+tmp*16;
	}
	ds1302_write_byte(ds1302_control_add,0x00);			//�ر�д���� 
	ds1302_write_byte(ds1302_sec_add,0x80);				//��ͣ 
	//ds1302_write_byte(ds1302_charger_add,0xa9);			//������ 
	ds1302_write_byte(ds1302_year_add,time_buf[1]);		//�� 
	ds1302_write_byte(ds1302_month_add,time_buf[2]);	//�� 
	ds1302_write_byte(ds1302_date_add,time_buf[3]);		//�� 
	ds1302_write_byte(ds1302_day_add,time_buf[7]);		//�� 
	ds1302_write_byte(ds1302_hr_add,time_buf[4]);		//ʱ 
	ds1302_write_byte(ds1302_min_add,time_buf[5]);		//��
	ds1302_write_byte(ds1302_sec_add,time_buf[6]);		//��
	ds1302_write_byte(ds1302_day_add,time_buf[7]);		//�� 
	ds1302_write_byte(ds1302_control_add,0x80);			//��д���� 
}

/*��DS302����ʱ������*/
void ds1302_read_time(void)  { 
   	    unsigned char i,tmp;
	time_buf[1]=ds1302_read_byte(ds1302_year_add);		//�� 
	time_buf[2]=ds1302_read_byte(ds1302_month_add);		//�� 
	time_buf[3]=ds1302_read_byte(ds1302_date_add);		//�� 
	time_buf[4]=ds1302_read_byte(ds1302_hr_add);		//ʱ 
	time_buf[5]=ds1302_read_byte(ds1302_min_add);		//�� 
	time_buf[6]=(ds1302_read_byte(ds1302_sec_add))&0x7F;//�� 
	time_buf[7]=ds1302_read_byte(ds1302_day_add);		//�� 


	for(i=0;i<8;i++){           //BCD����
		tmp=time_buf[i]/16;
		time_buf1[i]=time_buf[i]%16;
		time_buf1[i]=time_buf1[i]+tmp*10;
	}
}

/*DS302��ʼ������*/
void ds1302_init(void) {
	
	RST_CLR;			/*RST���õ�*/
	SCK_CLR;			/*SCK���õ�*/
    ds1302_write_byte(ds1302_sec_add,0x00);				 
}
