

#include "compiler_defs.h"
#include "C8051F380_defs.h"

#include "delay.h"


/*
TMR3CN= (TF3H,TF3L,TF3LEN,T3CE,T3SPLIT,TR3,T3CSS,T3XCLK)

TF3H: Timer 3 High Byte Overflow Flag
TF3L: Timer 3 Low Byte Overflow Flag
TF3LEN: Timer 3 Low Byte Interrupt Enable
T3CE: Timer 3 Capture Enable
T3SPLIT: Timer 3 Split Mode Enable
0: Timer 3 operates in 16-bit auto-reload mode.
1: Timer 3 operates as two 8-bit auto-reload timers.
TR3: Timer 3 Run Control. 
T3CSS: Timer 3 Capture Source Select
T3XCLK: Timer 3 External Clock Select
*/



void delay_ms(unsigned int ms)
{
	while (ms) 
	{
		TMR3CN=0;     //TR3 = 0, TF3=0
		TMR3=-4000;   // F_OSC/12000 ,  Overflow in 1ms			

		TMR3CN=TMR3CN|4;    //TR3 = 1 , Start Timer
		while(!(TMR3CN&0x80));     // Wait for overflow
		ms--;               // Update ms counter
	}

	TMR3CN=0;     //TR3 = 0
} 


void delay_us(unsigned int us)  //max us=65536/4=16384
{
	TMR3CN=0; //TR3 = 0, TF3=0 

	TMR3=-(us*4); //  us*F_OSC/12

	TMR3CN=TMR3CN|4;   //TR3 = 1 , Start Timer
	while(!(TMR3CN&0x80));   // Wait for overflow
	TMR3CN=0; //TR3 = 0	
}

