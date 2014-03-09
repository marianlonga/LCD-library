LCD library by Marian Longa
===========================

Copyright
---------
**Copyright (c) Marian Longa 2014. All rights reserved.**
- If you would like to use this library commercially, please contact me.
- If you have any ideas what to improve, please contact me as well.
**Email:**   marian _dot_ longa _at_ gmail _dot_ com
**Website:** http://marianlonga.com
**Github:**  https://github.com/marianlonga

Description
-----------
A library I've written in C, used for communication between LCD displays and PIC microcontrollers. 
Written for LCDs using HD44780 driver or compatible. Tested with PIC18F452 (8bit MCU).

Installation
------------
1. Import/copy files `LCD-library.h` and `LCD-library.c` into your project folder.
2. Include the header in your main file: `#include "LCD-library.h"`.
3. Configure settings in `LCD-library.h`. Important: set all appropriate `#define`s -- LCD pins, crystal frequency, number of rows, data length, font.

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
- Choose between reading busy flag or delaying after command execution
- ~~Select data length (4 bits, 8 bits)~~ _Not implemented yet, only 8 bit interface availabe!_
- Select font (5x8 dots, 5x10 dots)
- Select number of rows of LCD
- Select inital cursor position
- Select cursor position increment/decrement
- Select if display shift is On/Off
- Select initial settings for display -- display On/Off, cursor On/Off, cursor blinking On/Off