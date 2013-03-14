#include<reg52.h>
#include<intrins.h>
unsigned char count,a;
// Use P0 to control columns, 0 = light on, 1 = light off
// Use P2 to control rows, 1 = light on, 0 = light off
unsigned char code column[] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
unsigned char code row[] = {0x78,0xfc,0x7e,0x3f,0x3f,0x7e,0xfc,0x78};

void main()
{
	count=0;
	EA=1;
	TMOD=0x01;
	ET0=1;
	TH0=(65536-500)/256;
	TL0=(65536-500)%256;
	TR0=1;
	while(1)
	{
		if (a==5)
		{
			a=0;
			P0 = column[count%8];
			P2 = row[count%8];
			count++;
		}
	}

}

void time() interrupt 1
{
	TH0=(65536-500)/256;
	TL0=(65536-500)%256;
  a++;	
}