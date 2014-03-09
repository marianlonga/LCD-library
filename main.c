/* Copyright (c) 2014 Marian Longa. All rights reserved. 
 * http://marianlonga.com, http://github.com/marianlonga/LCD-display */

#include <xc.h>
#include "LCD-library.h"

// Change to your configuration bits
#pragma config OSC = HS  // High-Speed oscillator
#pragma config WDT = OFF // Watchdog timer OFF
#pragma config LVP = OFF // Low-voltage programming OFF

// Change to your oscillator frequency in Hz
#define _XTAL_FREQ 20000000 // 20MHz oscillator

void delay_ms(int ms) {for(int i = 0; i < ms; i++) __delay_ms(1);}

int main() {
    // Initializes LCD with settings from `LCD-library.h`
    LCD_init();

    // Write "Hello, World!" starting at (2nd column, 1st row)
    LCD_setCursor(2,1);
    LCD_displayString("Hello, World!");

    // Display characters 'a', '!' and '$' on positions (3,2), (4,2), (5,2)
    LCD_setCursor(3,2);
    LCD_displayChar('a');
    LCD_displayChar('!');
    LCD_displayChar('$');

    // Write number -123 starting at (7th column, 2nd row)
    LCD_setCursor(7,2);
    LCD_displayNumber(-123);

    // In one second intervals display numbers 1-10 at position (12,2)
    for(int i = 1; i <= 10; i++) {
        LCD_setCursor(13,2);
        LCD_displayNumber(i);
        LCD_delay_ms(1000);
    }

    // Wait infinitely long
    while(1);
}