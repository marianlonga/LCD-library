/* Copyright (c) 2014 Marian Longa. All rights reserved. 
 * http://marianlonga.com, http://github.com/marianlonga/LCD-display */

#include <xc.h>
#include "LCD-library.h"

#pragma config OSC = HS // High-Speed oscillator
#pragma config WDT = OFF // Watchdog timer OFF
#pragma config LVP = OFF // Low-voltage programming OFF

#define _XTAL_FREQ 20000000 // 20MHz crystal

void delay(int time)  {for(int i = 0; i < time; i++);}
void delay_ms(int ms) {for(int i = 0; i < ms; i++) __delay_ms(1);}
void delay_us(int us) {for(int i = 0; i < us; i++) __delay_us(1);}

int main(int argc, char** argv) {
    LCD_init();

    int min, sec, decisec;
    min = sec = decisec = 0;

    while(min < 2) { // repeat 2 minutes
        if(decisec == 10) {
            sec++;
            decisec = 0;
        }
        if(sec == 60) {
            min++;
            sec = 0;
        }
        LCD_setCursor(1,1); LCD_displayNumber(min);
        LCD_setCursor(3,1); LCD_displayChar(':');
        LCD_setCursor(4,1); LCD_displayNumber(sec);
        LCD_setCursor(6,1); LCD_displayChar('.');
        LCD_setCursor(7,1); LCD_displayNumber(decisec);
        LCD_delay_ms(100);
        decisec++;
    }

    while(1);
}