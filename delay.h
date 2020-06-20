
#ifndef _DELAY_H
#define _DELAY_H

//#include "C8051F380_defs.h"
//#include "compiler_defs.h"
/********************************* oscillator************************/
// F_OSC = 48    /* CLOCK frequency in MHz */
/********************************************************************/


/* period unit time  = 1msec   VALUE_TIMER0  -(F_0CS/12)/1000      */ 
void delay_ms(unsigned int ms);

void delay_us(unsigned int us);  //65536usec > t > 5usec


#endif /* _DELAY_H */   
