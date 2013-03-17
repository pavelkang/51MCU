#include<reg52.h>
#include<intrins.h>
#include<math.h>
sbit K1 = P3^2;
sbit K2 = P3^3;
sbit beep = P3^4;
#define uchar unsigned char
#define Reset()   ((void (code *) (void)) 0x0000) ()
uchar code P0table[] = {0x1f,0x8f,0xc7,0xe3,0xf1,0xf8};
uchar code P2table[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
uchar code ballXtable[] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
uchar offset,ballX,ballY,timer1,DirY,DirX;

void delay(uchar z)
{
	uchar x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void D1(uchar);
void D2(uchar,uchar);
void testBoundary();
void clearScreen()
{
	uchar i;
	i=200000;
		P0=0x00;
		P2=0xff;
	delay(10000);
}

	
void key()
{
		if (K2==0)
		{	
				TH0=(65535-500)/256;
				TL0=(65535-500)%256;
			  //timer1 = 0;
			if(offset>0){offset = offset -1;}
				while(!K2)
				{
					D1(offset);
					D2(ballY,ballX);
				}
				timer1=0;
			}
		
		if (K1==0)
		{	
				TH0=(65535-500)/256;
				TL0=(65535-500)%256;
				//timer1=0;
				if(offset<5){offset = offset +1;}
				while(!K1)
				{
					D1(offset);
					D2(ballY,ballX);
				}
				timer1=0;
		}
}		

	
void D1(uchar offset)
{
	P2=P2table[0];
	P0=P0table[offset];
	delay(7);
	P0=0xff;
}	

void D2(uchar ballY,uchar ballX)
{
		P2=P2table[ballY];
		P0 = ballXtable[ballX];
		delay(5);
		P0=0xff;
}

void init()
{
	uchar i;
	i=0;
	offset = 0;
	P2=P2table[0];
	ballX = 2;
	ballY=3;
	DirX=1;
	DirY=1;
	EA=1;
	TMOD=0x01;
	ET0=1;
	TH0=(65535-500)/256;
	TL0=(65535-500)%256;
	TR0=1;
}		

			
void testBoundary()
{
		if(ballX ==0)
		{
			if(DirX == -1)
					{DirX = 1; }
		}
		
		if(ballX==7)
		{
				if(DirX==1)
				{
					DirX=-1;
				}
		}
				if(ballY ==7) 
		{
			if (DirY== 1)
				{DirY=-1;}
		}
		if (ballY == 1)
		{
			if(DirY==-1)
			{
				DirY=1;
			}
		}
	}

void buzz()
	{
		beep = 0;
		delay(2000);
		beep=1;
	}
void testCatch()
{
		if(ballY==1)
		{
				if(ballX!=offset)
				{						
					if(ballX != offset+1)
					{							
						if(ballX != offset+2)
						{TR0=0;buzz();}
					}		
			}
		}		
}
				

void main()
{
	init();
	while(1)
	{
		testCatch();
		testBoundary();		
		D1(offset);
		D2(ballY,ballX);
	}
}
		
void timer() interrupt 1
{
	TH0=(65535-500)/256;
	TL0=(65535-500)%256;
	timer1++;
	if (timer1==200)
	{
		timer1 = 0;	
		key();
		ballX = ballX+DirX;
		ballY = ballY+DirY;
	}
}

