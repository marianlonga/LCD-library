/* Copyright (c) 2014 Marian Longa. All rights reserved.
 * http://marianlonga.com, http://github.com/marianlonga/LCD-display */

#include "LCD-library.h"

void LCD_delay(int time)  {for(int i = 0; i < time; i++);}
void LCD_delay_us(int us) {for(int i = 0; i < us; i++) __delay_us(1);}
void LCD_delay_ms(int ms) {for(int i = 0; i < ms; i++) __delay_ms(1);}
void LCD_delay_s(int s)   {for(int i = 0; i < s; i++) for(int j = 0; j < 1000; j++) __delay_ms(1);}

void LCD_wait() { // I must read the busy flag between en=HIGH and en=LOW
    if(LCD_USE_BUSY_FLAG) {
        LCD_data_dir = 0xFF; // set RD to input pins
        LCD_rs       = 0; // command register
        LCD_rw       = 1; // read

        LCD_en = 1;
        while(LCD_busy) { LCD_en=0; LCD_en=1;}

        LCD_data_dir = 0x00; // set RD back to outputs
    }
    else LCD_delay_us(LCD_command_delay);
}

void LCD_codeNoWait(int code) {
    LCD_rs   = (code & 0b1000000000) >> 9;
    LCD_rw   = (code & 0b0100000000) >> 8;
    LCD_data =  code & 0b0011111111;
    LCD_en   = 1; // enable pin HIGH-->LOW
    LCD_en   = 0;
}

void LCD_code(int code) {
    LCD_codeNoWait(code);
    LCD_wait();
}

void LCD_init() {
    LCD_data_dir = LCD_rs_dir = LCD_rw_dir = LCD_en_dir = 0; // all LCD pins to output
    LCD_en       = LCD_rs     = LCD_rw     = LCD_data   = 0;// default values for LCD pins are 0

    // convert human-readable config to machine-readable
    int LCD_dl, LCD_n, LCD_f;
    if(LCD_data_length ==  8) LCD_dl = 1; else if(LCD_data_length == 4) LCD_dl = 0;
    if(LCD_rows        ==  2) LCD_n  = 1; else if(LCD_rows        == 1) LCD_n  = 0;
    if(LCD_font        == 10) LCD_f  = 1; else if(LCD_font        == 8) LCD_f  = 0;

    if(LCD_data_length == 8) {

        // Official init starts here
        LCD_delay_ms(50);
        LCD_codeNoWait(0b0000100000 + (LCD_dl<<4) + (LCD_n<<3) + (LCD_f<<2)); // set function set
        LCD_delay_ms(10);
        LCD_codeNoWait(0b0000100000 + (LCD_dl<<4) + (LCD_n<<3) + (LCD_f<<2)); // set function set
        LCD_delay_us(200);
        LCD_codeNoWait(0b0000100000 + (LCD_dl<<4) + (LCD_n<<3) + (LCD_f<<2)); // set function set

        LCD_code(0b0000100000 + (LCD_dl<<4) + (LCD_n<<3) + (LCD_f<<2)); // set function set // 8 bits, 2 lines, 5x8 dots
        LCD_code(0b0000001000); // display OFF
        LCD_code(0b0000000001); // clear display
        LCD_code(0b0000000100 + (LCD_isIncrement<<1) + LCD_isShift); // set entry mode // cursor increment, no display shift
        // Official init ends here

        LCD_code(0b0000001000 + (LCD_isDisplayOn<<2) + (LCD_isCursorOn<<1) + LCD_isCursorBlinking); // display ON, cursor ON, cursor not blinking
        LCD_setCursor(LCD_posX, LCD_posY); // set initial position of cursor
    }
    else if(LCD_data_length == 4) {
        // TODO: make init for 4bit interface
    }
}

//display char on LCD
void LCD_displayChar(char inputChar) {
    LCD_code(0b1000000000 + inputChar); // char is an 8bit binary ASCII code, compatible with character codes which can be displayed on HD44780
    // move cursor based on the increment/decrement setting
    if(LCD_isIncrement) LCD_posX++; else LCD_posX--;
}

// displays string
void LCD_displayString(const char *str) {
    for(int i = 0; i < strlen(str); i++) LCD_displayChar(str[i]);
}

// displays string waiting "delay" milliseconds after each letter
void LCD_typewriteString(const char *str, int delay) {
    for(int i = 0; i < strlen(str); i++) {
        LCD_displayChar(str[i]);
        LCD_delay_ms(delay);
    }
}

void LCD_displayNumber(long int number) {
    char strNumber[20];
    itoa(strNumber, number, 10); // convert int to string
    LCD_displayString(strNumber);
}

void LCD_displayNumberRight(long int number) {
    char strNumber[20];
    itoa(strNumber, number, 10); // convert int to string
    LCD_moveLeft(strlen(strNumber)-1);
    LCD_displayString(strNumber);
}

void LCD_clear() {
    LCD_code(0b0000000001); // clear display
    LCD_posX = LCD_posY = 1; // cursor is reset to (1,1)
}

// if display is turned on, turn it off
// display OFF, cursor OFF, blinking OFF
void LCD_off() {
    if(LCD_isDisplayOn) {
        LCD_code(0b0000001000);
        LCD_isDisplayOn = FALSE;
    }
}

//void LCD_on()    {LCD_code(0b0000001110);} // display ON, cursor ON, blinking OFF
void LCD_on() {
    if(!LCD_isDisplayOn) {
       LCD_code(0b0000001100 + (LCD_isCursorOn<<1) + LCD_isCursorBlinking); // turn display on with previous settings
       LCD_isDisplayOn = TRUE;
    }
}

void LCD_setCursor(int pos, int row) {
    if(pos >= 1 && pos <= LCD_columns && row >= 1 && row <= LCD_rows){ // is the chosen cursor position in range?
        LCD_posX = pos; // set the variables
        LCD_posY = row;
        switch(row) { // set the DDRAMA address in LCD
            case 1:  LCD_code(0b0010000000 + 0x00 + (pos-1)); break;
            case 2:  LCD_code(0b0010000000 + 0x40 + (pos-1)); break;
            //case  3: LCD_code(0b0010000000 + 0x14 + (pos-1)); break;
            //case  4: LCD_code(0b0010000000 + 0x54 + (pos-1)); break;
            default: LCD_code(0b0010000000 + 0x00 + (pos-1)); break; // default is 1st row
        }
    }
}

void LCD_home() {
    LCD_code(0b0000000010);
    LCD_posX = LCD_posY = 1; // cursor is reset to (1,1)
}

void LCD_cursorOff() {
    if(LCD_isCursorOn) {
        LCD_code(0b0000001000 + (LCD_isDisplayOn<<2) + LCD_isCursorBlinking);
        LCD_isCursorOn = FALSE;
    }
}

void LCD_cursorOn() {
    if(!LCD_isCursorOn) {
        LCD_code(0b0000001010 + (LCD_isDisplayOn<<2) + LCD_isCursorBlinking);
        LCD_isCursorOn = TRUE;
    }
}

void LCD_blinkCursor() {
    if(LCD_isCursorBlinking) {
        LCD_code(0b0000001000 + (LCD_isDisplayOn<<2) + (LCD_isCursorOn<<1));
        LCD_isCursorBlinking = FALSE;
    }
}

void LCD_stopCursorBlinking() {
    if(!LCD_isCursorBlinking) {
        LCD_code(0b0000001001 + (LCD_isDisplayOn<<2) + (LCD_isCursorOn<<1));
        LCD_isCursorBlinking = TRUE;
    }
}

void LCD_moveLeft(int howMuch) {
    if(LCD_posX -howMuch >= 1) {
        LCD_posX -= howMuch;
        LCD_setCursor(LCD_posX, LCD_posY);
    }
}

void LCD_moveRight(int howMuch) {
    if(LCD_posX +howMuch <= LCD_columns) {
        LCD_posX += howMuch;
        LCD_setCursor(LCD_posX, LCD_posY);
    }
}

void LCD_moveUp(int howMuch) {
    if(LCD_posY -howMuch >= 1) {
        LCD_posY -= howMuch;
        LCD_setCursor(LCD_posX, LCD_posY);
    }
}

void LCD_moveDown(int howMuch) {
    if(LCD_posY +howMuch <= LCD_rows) {
        LCD_posY += howMuch;
        LCD_setCursor(LCD_posX, LCD_posY);
    }
}