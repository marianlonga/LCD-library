/* Copyright (c) 2014 Marian Longa. All rights reserved.
 * http://marianlonga.com, http://github.com/marianlonga/LCD-display */

#ifndef LCD_LIBRARY_H
#define	LCD_LIBRARY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// crystal/oscillator frequency used for waits in Hz (default: 20000000)
#define _XTAL_FREQ 20000000

// wait by reading busy flag (1) or wait "LCD_command_delay" microseconds using LCD_delay (0)
#define LCD_USE_BUSY_FLAG 1
#define LCD_command_delay 500 // [500] amount of time to wait for LCD to process a command in us

// set number of rows and columns
#define LCD_columns 16
#define LCD_rows    2

// set data length: 8 - 8bit, 4 - 4bit
// WARNING: 4bit IS NOT IMPLEMENTED! USE 8bit INSTEAD!
#define LCD_data_length 8

// set font: 10 - 5x10 dots, 8 - 5x8 dots
#define LCD_font 8

// pins (PORT)
#define LCD_data PORTD
#define LCD_busy PORTDbits.RD7
#define LCD_rs   PORTBbits.RB0
#define LCD_rw   PORTBbits.RB1
#define LCD_en   PORTBbits.RB2

// direction of pins (TRIS)
#define LCD_data_dir TRISD
#define LCD_busy_dir TRISDbits.RD7
#define LCD_rs_dir   TRISBbits.RB0
#define LCD_rw_dir   TRISBbits.RB1
#define LCD_en_dir   TRISBbits.RB2

// set default values for variables
#define TRUE  1
#define FALSE 0                       // [default value] description
int LCD_posX             = 1,         // [1]     starting position in row (ex. 1,2,3,...)
    LCD_posY             = 1,         // [1]     starting row number (1,2,3,4)
    LCD_isIncrement      = TRUE,      // [TRUE]  TRUE - increment, FALSE - decrement
    LCD_isShift          = FALSE,     // [FALSE] TRUE - shift ON, FLASE - shift OFF
    LCD_isDisplayOn      = TRUE,      // [TRUE]  TRUE - display ON, FALSE - display OFF
    LCD_isCursorOn       = TRUE,      // [TRUE]  TRUE - cursor displayed, FALSE - not showed
    LCD_isCursorBlinking = FALSE;     // [FALSE] TRUE - cursor blinks, FALSE - cursor doesn't blink

// waits given number of instruction cycles
void LCD_delay(int);
// waits given number of microseconds (10^-6 s)
void LCD_delay_us(int);
// waits given number of milliseconds (10^-3 s)
void LCD_delay_ms(int);
// waits given number of seconds
void LCD_delay_s(int);
// used after command execution to wait for busy flag to become High-->Low, or, if set, waits LCD_command delay microseconds
void LCD_wait();
// executes a code in the form [RS][RW][DB7][DB6][DB5][DB4][DB3][DB2][DB1][DB0] and DOESN'T call LCD_wait() afterwards
void LCD_codeNoWait(int);
// executes a code in the form [RS][RW][DB7][DB6][DB5][DB4][DB3][DB2][DB1][DB0] and calls LCD_wait() afterwards
void LCD_code(int);
// initializes LCD based on settings LCD_rows, LCD_data_length, LCD_font; LCD_increment, LCD_shift; LCD_displayOn, LCD_cursorOn, LCD_cursorBlinking
void LCD_init();
// displays a given character on position of cursor
void LCD_displayChar(char);
// displays a given string starting on position of cursor
void LCD_displayString(const char *);
// clears LCD and sets cursor at (1,1)
void LCD_clear();
// turns LCD off
void LCD_off();
// turns LCD on with previous settings
void LCD_on();
// set cursor at position (row, pos), where Y=row and X=pos
void LCD_setCursor(int, int);
// sets cursor at (1,1) but doesn't clear display
void LCD_home();
// displays a given string using typewriter effect -- it delays given number of milliseconds after displaying each letter
void LCD_typewriteString(const char *, int);
// displays cursor
void LCD_cursorOn();
// hides cursor
void LCD_cursorOff();
// sets cursor to blinking
void LCD_blinkCursor();
// stops cursor from blinking
void LCD_stopCursorBlinking();
// displays an integer (type: *int*; range -32767, 32767)
void LCD_displayNumber(long int);


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_LIBRARY_H */

