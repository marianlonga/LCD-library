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
    LCD_init();

    LCD_setCursor(10,1);
    for(int i = 0; i < 100000; i++) {
        LCD_displayNumberRight(i);
        LCD_moveLeft(1);
        LCD_delay_ms(10);
    }

    while(1);
}
