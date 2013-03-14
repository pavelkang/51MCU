#include<reg52.h>
unsigned char a;
sbit beep = P3^4;
unsigned char flag;
void init()
{
	EA=1;
	ES=1;
	REN = 1;//串口允许接收
	SM0 = 0;
	SM1 = 1;
	TMOD=0X20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
}
	
	
	
void main()
{
	init();
	flag = 0;
	while(1)
	{
		if (flag==1)
		{
			ES=0;
			SBUF = a;
			flag = 0;
			while(!TI);
			TI=0;
			ES=1;
		}

	}
}

void ser() interrupt 4
{
	RI=0;
	P2=SBUF;
	a = SBUF;
	flag=1;
}
		
		