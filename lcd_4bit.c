
#include "compiler_defs.h"
#include "C8051F380_defs.h"
#include "lcd_4bit.h"
#include "delay.h"

void send_command(unsigned char dat);
void send_data(char cmd);
void send_4bit(unsigned char dat);

U8 _line=1,_position=0;

//=============================================================
//===============================LCD===========================
//=============================================================

void PulseE()
{
	P4=P4|0x08; //E=1
	delay_us(10);
	P4=P4& ~0x08; //E=0
}

//=======================CONFIG THE LCD=======================

void lcd_begin()      		//Initialization of The LCD
{
	delay_ms(100);

	P4=0;
	delay_ms(20);
	P4=0x30;//send_4bit(0x30);
	PulseE();
	delay_ms(10);
	P4=0x30;
	PulseE();
	delay_ms(10);
	P4=0x30;
	PulseE();
	delay_ms(10);
	P4=0x20;
	PulseE();
	delay_ms(10);

	send_command(0x28);     //4bit,2 line,5*7 dot
	delay_ms(10);
	send_command(0x0e);     //display on ,cursor on,cursor blink
	delay_ms(10);
	send_command(0x01);   	//clear_display
	delay_ms(10);
	send_command(0x06); 	// increment cursor,no display shift
	delay_ms(10);
	_line=1; _position=0;
}

void lcd_clearScreen()      //Initialization of The LCD
{
	send_command(0x01);   //clear_display
	delay_ms(10);
	send_command(0x02);// cursor at home
	delay_ms(10);
	_line=1; _position=0;
}



//===========================LCD LINE NUMBER & POSITION====================
void lcd_setCursor(U8 line_number,U8 p)
{
	if((line_number>0) && (line_number<=2) && (p<16)){
		_line=line_number; _position=p;
		switch(line_number)
		{
		case 1:
			send_command(0x80+p);
			break;

		case 2:
			send_command(0xc0+p);
			break;

		}
		delay_us(50);
	}
}


//================DISPLAY THE VARIABLE ON THE LCD=================

void lcd_write(int v)
{
	char buf[1];
	int i,j=10000;
	bit flag=0;
	if(v<0) { lcd_print("-"); v=-v;}
	for(i=0;i<5;i++)
	{
		buf[0]=v/j;
		if(buf[0]) flag=1;
		v=v%j;
		j=j/10;
		if(flag || j==0) { buf[0]+='0'; lcd_print(buf);}
	}
}

//================ PRINT STRING =================

void lcd_print(char str[])
{
	int i=0;
	while(str[i] )
	{
		if(_position<16)
		{
			send_data(str[i++]);
			_position++;
		}
		else
		{
			if(_line==1) { _line=2; send_command(0xc0); _position=0;}
			else { _line=1; send_command(0x80); _position=0;}
		}
		delay_us(50);
	}
}


void lcd_println(char str[])
{
	lcd_print(str);
	if(_line==1) { _line=2; send_command(0xc0); _position=0;}
	else { _line=1; send_command(0x80); _position=0;}
	delay_us(50);

}


//================ PRINT STRING WITH POSITION =================
void lcd_print_Position(U8 line_number,U8 p,char str[])
{
	lcd_setCursor(line_number,p);
	if((line_number>0) && (line_number<=2) && (p<16))
		lcd_print(str);
}


void send_command (char cmd)
{	
	P4=cmd&0xf0;//RS=0 4bit MSB
	PulseE();

	P4=cmd<<4;//RS=0 4bit LSB
	PulseE();
}

void send_data (unsigned char dat)
{	
	P4=(dat&0xf0)| 0x02;//RS=1 4bit MSB
	PulseE();

	P4=(dat<<4)| 0x02;//RS=1 4bit LSB
	PulseE();
}


