
#include <reg52.h>
#include<intrins.h>



sbit SCK=P3^6;		
sbit SDA=P3^4;		
sbit RST=P3^5;
/*复位脚*/
#define RST_CLR	RST=0/*电平置低*/
#define RST_SET	RST=1/*电平置高*/


/*双向数据*/
#define IO_CLR	SDA=0/*电平置低*/
#define IO_SET	SDA=1/*电平置高*/
#define IO_R	SDA/*电平读取*/


/*时钟信号*/
#define SCK_CLR	SCK=0/*时钟信号*/
#define SCK_SET	SCK=1/*电平置高*/


#define ds1302_sec_add			0x80		//秒数据地址
#define ds1302_min_add			0x82		//分数据地址
#define ds1302_hr_add			0x84		//时数据地址
#define ds1302_date_add			0x86		//日数据地址
#define ds1302_month_add		0x88		//月数据地址
#define ds1302_day_add			0x8a		//星期数据地址
#define ds1302_year_add			0x8c		//年数据地址
#define ds1302_control_add		0x8e		//控制数据地址
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

unsigned char time_buf1[8] = {20,9,3,13,18,51,00,6};//空年月日时分秒周
unsigned char time_buf[8] ;//空年月日时分秒周
/*向DS1302写入一字节数据*/
void ds1302_write_byte(unsigned char addr, unsigned char d) {

	unsigned char i;
	RST_SET;					/*启动DS1302总线*/
	
	/*写入目标地址：addr*/
	addr = addr & 0xFE;/*最低位置零*/
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
	
	/*写入数据：d*/
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
	RST_CLR;					/*停止DS1302总线*/
}

/*从DS1302读出一字节数据*/
unsigned char ds1302_read_byte(unsigned char addr) {

	unsigned char i;
	unsigned char temp;
	RST_SET;					/*启动DS1302总线*/

	/*写入目标地址：addr*/
	addr = addr | 0x01;/*最低位置高*/
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
	
	/*输出数据：temp*/
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
	
	RST_CLR;					/*停止DS1302总线*/
	return temp;
}

/*向DS302写入时钟数据*/
void ds1302_write_time(void) {
     
    unsigned char i,tmp;
	for(i=0;i<8;i++){           //BCD处理
		tmp=time_buf1[i]/10;
		time_buf[i]=time_buf1[i]%10;
		time_buf[i]=time_buf[i]+tmp*16;
	}
	ds1302_write_byte(ds1302_control_add,0x00);			//关闭写保护 
	ds1302_write_byte(ds1302_sec_add,0x80);				//暂停 
	//ds1302_write_byte(ds1302_charger_add,0xa9);			//涓流充电 
	ds1302_write_byte(ds1302_year_add,time_buf[1]);		//年 
	ds1302_write_byte(ds1302_month_add,time_buf[2]);	//月 
	ds1302_write_byte(ds1302_date_add,time_buf[3]);		//日 
	ds1302_write_byte(ds1302_day_add,time_buf[7]);		//周 
	ds1302_write_byte(ds1302_hr_add,time_buf[4]);		//时 
	ds1302_write_byte(ds1302_min_add,time_buf[5]);		//分
	ds1302_write_byte(ds1302_sec_add,time_buf[6]);		//秒
	ds1302_write_byte(ds1302_day_add,time_buf[7]);		//周 
	ds1302_write_byte(ds1302_control_add,0x80);			//打开写保护 
}

/*从DS302读出时钟数据*/
void ds1302_read_time(void)  { 
   	    unsigned char i,tmp;
	time_buf[1]=ds1302_read_byte(ds1302_year_add);		//年 
	time_buf[2]=ds1302_read_byte(ds1302_month_add);		//月 
	time_buf[3]=ds1302_read_byte(ds1302_date_add);		//日 
	time_buf[4]=ds1302_read_byte(ds1302_hr_add);		//时 
	time_buf[5]=ds1302_read_byte(ds1302_min_add);		//分 
	time_buf[6]=(ds1302_read_byte(ds1302_sec_add))&0x7F;//秒 
	time_buf[7]=ds1302_read_byte(ds1302_day_add);		//周 


	for(i=0;i<8;i++){           //BCD处理
		tmp=time_buf[i]/16;
		time_buf1[i]=time_buf[i]%16;
		time_buf1[i]=time_buf1[i]+tmp*10;
	}
}

/*DS302初始化函数*/
void ds1302_init(void) {
	
	RST_CLR;			/*RST脚置低*/
	SCK_CLR;			/*SCK脚置低*/
    ds1302_write_byte(ds1302_sec_add,0x00);				 
}
