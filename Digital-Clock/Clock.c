#include<reg52.h>
sbit dscs = P1^4;
sbit dsas = P1^5;
sbit dsrw = P1^6;
sbit dsds = P1^7;
sbit dsirq = P3^3;
//sbit K1 = P3^2;
sbit K2 = P3^1;
sbit K3 = P3^0;
sbit beep = P3^4;
sbit LCD_RS=P1^0;		
sbit LCD_RW=P1^1;		
sbit LCD_E=P1^2;		
#define uchar unsigned char
uchar code table0[] = "Mon Tue Wed Thu Fri Sat Sun";
uchar code table1[] = "Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec";
uchar s1num,clear;
char miao, shi, fen;
uchar day,date,year, month,flag;

void delay(uchar z)
{
	uchar x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void buzz()
{
	beep=0;
	delay(50);
	beep=1;
}


void write_ds(uchar address, uchar dataa) 
{
	dscs = 0;
	dsds = 1;   
	dsrw = 1;
	dsas = 1;
	P0 = address;     
	dsas=0;         
	dsrw = 0;        
	P0 = dataa;
	dsrw = 1;
	dsas = 1;
	dscs = 1;
}

uchar read_ds(uchar address)
{
	uchar ds_dataa;    
	dsds = 1;
	dsrw = 1;
	dsas = 1;
	dscs = 0;
	P0 = address;
	dsas = 0;
	dsds=0;
	ds_dataa = P0;
	dsds = 1;
	dsas = 1;
	dscs=1;
	return ds_dataa;
}

void write_com(uchar com)                       
{
	LCD_RS = 0;
	P2 = com;
	delay(5);
	LCD_E= 1;
	delay(5);
	LCD_E=0;
}

void write_data(uchar dataa)                       
{
	LCD_RS = 1;
	P2 = dataa;
	delay(5);
	LCD_E = 1;
	delay(5);
	LCD_E =0;
}	

void write_sfm(uchar pos,uchar date)
{
	uchar shi,ge;
	shi=date/10;
	ge=date%10;
	write_com(0x80+0x40+pos);
	write_data(0x30+shi);                       
	write_data(0x30+ge);
}

void write_day(uchar pos,uchar date)
{
	write_com(0x80+0x40+pos);
	write_data(table0[4*(date%7)-4]);
	write_data(table0[4*(date%7)-3]);
	write_data(table0[4*(date%7)-2]);
}
	
void write_year(uchar pos,uchar date)
{
	uchar shi,ge;
	shi = date/10;
	ge = date%10;
	write_com(0x80+pos);
	write_data('2');            
	write_data(0x30+0);
	write_data(0x30+shi);
	write_data(0x30+ge);
}

void write_date(uchar pos, uchar date)
{
	uchar shi,ge;
	shi = date/10;
	ge = date%10;
	write_com(0x80+pos);
	write_data(0x30+shi);
	write_data(0x30+ge);
}

void write_month(uchar pos,uchar date)
{
	write_com(0x80+pos);
	write_data(table1[4*(date%12)-4]);
	write_data(table1[4*(date%12)-3]);
	write_data(table1[4*(date%12)-2]);
}

// void keyScan()                            
// {
// 	K1=1;
// 	K2=1;
// 	K3=1;
// 	if (K1==0)
// 	{
// 		delay(10);
// 		if (K1==0)
// 		{
// 			flag =1;
// 			s1num++;
// 			while(!K1);
// 			buzz();
// 			switch(s1num)
// 			{
// 				case 1: write_com(0x80+0x40+13);write_com(0x0f);  //光标到秒；闪烁
// 					break;
// 				case 2: write_com(0x80+0x40+10);
// 				  break;
// 				case 3: write_com(0x80+0x40+7);
// 					break;
// 				case 4: s1num=0; write_com(0x0c);flag=0;//取消光标闪烁 时钟开始走
// 			}
// 		}		
// 	}
// 	if(s1num !=0)
// 	{
// 		if(K2 == 0)
// 		{
// 			delay(10);
// 			if(K2==0)
// 			{
// 				while(!K2);
// 				buzz();
// 				switch(s1num)
// 				{
// 					case 1: //在秒处调节
// 						miao++;
// 					  if(miao==60)
// 						{miao=0;}
// 						write_sfm(13,miao);
// 						write_com(0x80+0x40+13);
// 						write_ds(0,miao);
// 						
// 						break;
// 					case 2://在分处调节
// 						fen++;
// 						if(fen==60)
// 						{fen=0;}
// 						write_sfm(10,fen);
// 						write_com(0x80+0x40+10);
// 						write_ds(2,fen);
// 						
// 						break;
// 					case 3://在时处调节
// 						shi++;
// 						if(shi==24)
// 						{shi=0;}
// 						write_sfm(7,shi);
// 						write_com(0x80+0x40+7);
// 						write_ds(4,shi);
// 					}
// 	
// 			}
// 		}
// 	  //测试k3
// 		if(K3==0)
// 		{
// 			delay(10);
// 			if(K3==0)
// 			{
// 				while(!K3);
// 				buzz();
// 				switch(s1num)
// 				{
// 					case 1: //在秒处调节
// 						miao--;
// 					  if(miao==-1)
// 						{miao=59;}
// 						write_sfm(10,miao);
// 						write_com(0x80+0x40+10);
// 						break;
// 					case 2://在分处调节
// 						fen--;
// 						if(fen==-1)
// 						{fen=59;}
// 						write_sfm(7,fen);
// 						write_com(0x80+0x40+7);
// 						break;
// 					case 3://在时处调节
// 						shi--;
// 						if(shi==-1)
// 						{shi=23;}
// 						write_sfm(4,shi);
// 						write_com(0x80+0x40+4);
// 					}
// 			}
// 		}
// 	}
// }
			
void set_alarm(uchar ashi, uchar afen,uchar amiao)
{
	write_ds(3,afen);
	write_ds(5,ashi);
	write_ds(1,amiao);
}



void init()
{
	EA = 1;
	EX0 = 1;
	IT0=1;
	flag=0;
	LCD_E = 0;
	LCD_RW = 0;
	fen = 0;
	miao = 0;
	shi=0;
	day = 0;
	date = 0;
	month = 0;
	s1num = 0;
	write_com(0x38);                                //初始化1602
	write_com(0x0f);
	write_com(0x01);
	write_com(0x06);
	write_com(0x0c);
	write_com(0x80);
	write_com(0x80+0x40+9);                         //写第二行的冒号
	write_data(':');
	delay(5);
	write_com(0x80+0x40+12);
	write_data(':');
	delay(5);
	write_sfm(13,miao);                            //把0先都写上
	write_sfm(10,fen);
	write_sfm(7,shi);
}

// void set_time()
// {
// 	write_ds(0x0b,0x04);
// 	write_ds(4,21);
// 	write_ds(2,39);
// 	write_ds(6,5)
// }

void main()
{
	
	init();
	set_alarm(10,2,50);
	write_ds(0x0b,0x26);
	read_ds(0x0c);
	write_year(1,12);
	//set_time();
	while(1)
	{
		//write_ds(0x0a,0x20);//开启DS12C887内部晶体振荡器
		//write_ds(0x0b,0x06); //设置bcd码，24小时制，   (0x0b,0x04) 是二进制
		if (flag==0)
		{
	  miao = read_ds(0);
 	  write_sfm(13,miao);
 		fen = read_ds(2);
 		write_sfm(10,fen);
		shi = read_ds(4);
		write_sfm(7,shi);
		day = read_ds(6);
		write_day(2,day);
		year=read_ds(9);
		write_year(1,year);
		month=read_ds(8);
		write_month(6,month);
		date =read_ds(7);
		write_date(10,date);
		}
		//keyScan();
	}

}

void exter() interrupt 0
{
	beep = 0;
	clear = read_ds(0x0c);
}
			
