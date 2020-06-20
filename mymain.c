#include "compiler_defs.h"
#include "C8051F380_defs.h"
#include "lcd_4bit.h"
#include "delay.h"

void Init_Device(void);

void main(void)
{
	int t1=0;
	int t2=0;

	Init_Device();
	lcd_begin();
	lcd_println("  Shai & Avi");

	while(1){
		lcd_setCursor(2,0);
		lcd_print("t1=");
		lcd_write(t1++);
		lcd_setCursor(2,7);
		lcd_print("t2=");
		lcd_write(t2--);
		delay_ms(1000);
	}
}