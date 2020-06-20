#ifndef _LCD_H
#define _LCD_H

#include "C8051F380_defs.h"
#include "compiler_defs.h"

/********************* LCD ******************************/
void lcd_begin() ;
void lcd_clearScreen();
void lcd_setCursor(char line_number,char p);
//void lcd_write(char character);
void lcd_write(int v);
void lcd_print(char str[]);
void lcd_println(char str[]);
void lcd_print_Position(unsigned char line_number,unsigned char p,char str[]);
/********************************************************/



#endif /* _LCD_H */   
