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

    LCD_setCursor(6,1);
    LCD_displayNumber(5678);
    
    LCD_moveDown(1);
    LCD_displayNumberRight(1234);

    while(1);

    // The above will produce following output:
    // +----------------+
    // |     5678       |
    // |  1234          |
    // +----------------+
}
