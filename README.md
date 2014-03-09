LCD library by Marian Longa
===========================

Description
-----------
A library I've written in C, used for communication between LCD displays and PIC microcontrollers.  
Written for LCDs using HD44780 driver or compatible. Tested with PIC18F452 (8bit MCU).

Copyright
---------
**Copyright (c) Marian Longa 2014. All rights reserved.**
- If you would like to use this library commercially, please contact me.
- If you have any ideas what to improve, please contact me as well.  
**Email:**   marian _dot_ longa _at_ gmail _dot_ com  
**Website:** http://marianlonga.com  
**Github:**  https://github.com/marianlonga

Installation
------------
1. Import/copy files `LCD-library.h` and `LCD-library.c` into your project folder.
2. Include the header in your main file: `#include "LCD-library.h"`.
3. Configure settings in `LCD-library.h`. Important: set all appropriate `#define`s -- LCD pins, crystal frequency, number of rows, data length, font.
4. In your main file you can now use all LCD functions starting with `LCD_`.

Features
--------

###Functions
_Note: all prototypes of functions and their descriptions are in `LCD-library.h`_
- Initialize LCD: `LCD_init();`
- Display a character: `LCD_displayChar('a');`
- Display a string: `LCD_displayString("Hello, World!");`
- Display a string with typewriter effect: `LCD_typewriteString("This is a string");`
- Display a number: `LCD_displayNumber(42);`
- Clear display: `LCD_clear();`
- Return home: `LCD_home();`
- Turn display On/Off: `LCD_on();` / `LCD_off();`
- Set cursor position: `LCD_setCursor(12,1);`
- Turn cursor On/Off: `LCD_cursorOn();` / `LCD_cursorOff();`
- Turn cursor blinking On/Off: `LCD_blinkCursor();` / `LCD_stopCursorBlinking();`
- Execute a custom LCD code: `LCD_code(0b1001000001);`

###Settings
_Note: all settings and their descriptions are in `LCD-library.h`_
- Set pins connected to LCD (data, busy flag, rs, rw, en)
- Choose between reading busy flag or delaying after command execution
- ~~Select data length (4 bits, 8 bits)~~ _Not implemented yet, only 8 bit interface availabe!_
- Set font (5x8 dots, 5x10 dots)
- Set number of rows of LCD
- Set inital cursor position
- Choose between cursor position increment/decrement
- Choose if display shift is On/Off
- Choose initial settings for display -- display On/Off, cursor On/Off, cursor blinking On/Off

Example
-------

```c
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
```
