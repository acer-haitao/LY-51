/*-----------------------------------------------
  ���ƣ���SD��д����
  ��˾���Ϻ�������ӿƼ����޹�˾
  ��վ��www.doflye.net
  ��д��ʦ��
  ���ڣ�2009.12
  �޸ģ���
  ���ݣ�ͨ������SD����320x240���ء�16λBMPͼƬ��HEX���ݣ�����д�����ϣ���ԭͼƬ
  ע���������SD��ʹ��SPIģʽ�������ǿ��ȡ(512Byte),������Ҫ��Ƭ���ṩ����512�Ŀ���RAM���Թ�����ʹ��
            �������ѡ��STC89c52RD+��STC89C58RD+��STC89C516RD+����׺RD+������չRAM��1024�ֽڣ�RC������չRAM256�ֽ�
------------------------------------------------*/
#include <reg52.h>
#include <stdio.h>
#include<9325TP.h>
//=============================================================
//����SD����Ҫ��4���ź���
sbit SD_CLK = P1^1;
sbit SD_DI  = P1^2;
sbit SD_DO  = P1^0;
sbit SD_CS  = P1^3;
//===========================================================
//���尴���˿�
sbit KEY = P3^2;
//===========================================================
//����512�ֽڻ�������ע����Ҫʹ�� xdata�ؼ���
unsigned char xdata DATA[512];

//===========================================================
//дһ�ֽڵ�SD��,ģ��SPI���߷�ʽ
void SdWrite(unsigned char n)
{

unsigned char i;

for(i=8;i;i--)
{
SD_CLK=0;
SD_DI=(n&0x80);
n<<=1;
SD_CLK=1;
}
SD_DI=1; 
} 
//===========================================================
//��SD����һ�ֽ�,ģ��SPI���߷�ʽ
unsigned char SdRead()
{
unsigned char n,i;
for(i=8;i;i--)
{
SD_CLK=0;
SD_CLK=1;
n<<=1;
if(SD_DO) n|=1;

}
return n;
}
//============================================================
//���SD������Ӧ
unsigned char SdResponse()
{
unsigned char i=0,response;

while(i<=8)
{
response = SdRead();
if(response==0x00)
break;
if(response==0x01)
break;
i++;
}
return response;
} 
//================================================================
//�����SD��
void SdCommand(unsigned char command, unsigned long argument, unsigned char CRC)
{

SdWrite(command|0x40);
SdWrite(((unsigned char *)&argument)[0]);
SdWrite(((unsigned char *)&argument)[1]);
SdWrite(((unsigned char *)&argument)[2]);
SdWrite(((unsigned char *)&argument)[3]);
SdWrite(CRC);
}
//================================================================
//��ʼ��SD��
unsigned char SdInit(void)
{
int delay=0, trials=0;
unsigned char i;
unsigned char response=0x01;

SD_CS=1;
for(i=0;i<=9;i++)
SdWrite(0xff);
SD_CS=0;

//Send Command 0 to put MMC in SPI mode
SdCommand(0x00,0,0x95);


response=SdResponse();

if(response!=0x01)
{
return 0;
} 

while(response==0x01)
{
SD_CS=1;
SdWrite(0xff);
SD_CS=0;
SdCommand(0x01,0x00ffc000,0xff);
response=SdResponse();
} 

SD_CS=1;
SdWrite(0xff);
return 1; 
}
//================================================================
//��SD��ָ����ַд����,һ�����512�ֽ�
unsigned char SdWriteBlock(unsigned char *Block, unsigned long address,int len)
{
unsigned int count;
unsigned char dataResp;
//Block size is 512 bytes exactly
//First Lower SS

SD_CS=0;
//Then send write command
SdCommand(0x18,address,0xff);

if(SdResponse()==00)
{
SdWrite(0xff);
SdWrite(0xff);
SdWrite(0xff);
//command was a success - now send data
//start with DATA TOKEN = 0xFE
SdWrite(0xfe);
//now send data
for(count=0;count<len;count++) SdWrite(*Block++);

for(;count<512;count++) SdWrite(0);
//data block sent - now send checksum
SdWrite(0xff); //���ֽ�CRCУ��, Ϊ0XFFFF ��ʾ������CRC
SdWrite(0xff);
//Now read in the DATA RESPONSE token
dataResp=SdRead();
//Following the DATA RESPONSE token
//are a number of BUSY bytes
//a zero byte indicates the MMC is busy

while(SdRead()==0);

dataResp=dataResp&0x0f; //mask the high byte of the DATA RESPONSE token
SD_CS=1;
SdWrite(0xff);
if(dataResp==0x0b)
{
//printf("DATA WAS NOT ACCEPTED BY CARD -- CRC ERROR\n");
return 0;
}
if(dataResp==0x05)
return 1;

//printf("Invalid data Response token.\n");
return 0;
}
//printf("Command 0x18 (Write) was not received by the MMC.\n");
return 0;
}

//=======================================================================
//��SD��ָ����ַ��ȡ����,һ�����512�ֽ�
unsigned char SdReadBlock(unsigned char *Block, unsigned long address,int len)
{
unsigned int count;
//Block size is 512 bytes exactly
//First Lower SS

 //printf("MMC_read_block\n");

SD_CS=0;
//Then send write command
SdCommand(0x11,address,0xff);

if(SdResponse()==00)
{
//command was a success - now send data
//start with DATA TOKEN = 0xFE
while(SdRead()!=0xfe);

for(count=0;count<len;count++) *Block++=SdRead(); 

for(;count<512;count++) SdRead();

//data block sent - now send checksum
SdRead();
SdRead();
//Now read in the DATA RESPONSE token
SD_CS=1;
SdRead();
return 1;
}
 //printf("Command 0x11 (Read) was not received by the MMC.\n");
return 0;
}

//============================================================
//������	
main()
{
 unsigned int x,y; //����Һ��������
 unsigned long j;  //ִ��ѭ����Ҫ����ʱ����
  unsigned int i;
  unsigned long AddTemp=328192;//SD����ַ��һ�����������ַ��ʼֵ��������winhex�鿴��������641����������512x641=328192������ʵ��SD�����ݸ���
  	CS=1;
	delayms(5);
	RES=0;
	delayms(5);
	RES=1;
	delayms(5);
	ILI9325_Initial();//Һ������ʼ��
	SdInit();         //SD����ʼ��
 while(1)
 {

 for(j=0;j<300;j++)   //300��ʾһ��ͼƬ����300x512�ֽڵ���Ϣ
    {
    SdReadBlock(DATA,AddTemp+(j*512),512);//ÿ�ζ���512�ֽڷŵ�������
    for(i=0;i<256;i++)                    //Ȼ��д��Һ������������ʾ256�����أ�ÿ������16λ��2���ֽ�
	   {   
   	   LCD_SetPos(x,x,y,y);
   	   Write_Data(DATA[2*i+1],DATA[2*i]);	 
	   x++;
	   if(x==240)                         //����Ƿ�д�����ı�Ե 240x320
	     {
	     y++;
	     x=0;
	     if(y==320)
	       y=0;
	     }
       }
     } 
     AddTemp = AddTemp+((j+20)*512);          //д��һ��ͼƬ���SD��ַ��300x512����һ��ͼƬ��ַ
     while(KEY);                         //�ȴ��������¼���ִ��ѭ����ʾ��һ��ͼƬ�����û�а�����ȴ�
	 
 } 
}


