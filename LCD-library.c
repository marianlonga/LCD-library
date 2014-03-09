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
        LCD_delay_ms(20);
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

void LCD_displayChar(char inputChar) {
    char c; // binary representation of character to display
    switch(inputChar) { // translate human readable char (inputChar) to machine readable char (c)
        case 'a': c = 0b01100001; break;
        case 'b': c = 0b01100010; break;
        case 'c': c = 0b01100011; break;
        case 'd': c = 0b01100100; break;
        case 'e': c = 0b01100101; break;
        case 'f': c = 0b01100110; break;
        case 'g': c = 0b01100111; break;
        case 'h': c = 0b01101000; break;
        case 'i': c = 0b01101001; break;
        case 'j': c = 0b01101010; break;
        case 'k': c = 0b01101011; break;
        case 'l': c = 0b01101100; break;
        case 'm': c = 0b01101101; break;
        case 'n': c = 0b01101110; break;
        case 'o': c = 0b01101111; break;
        case 'p': c = 0b01110000; break;
        case 'q': c = 0b01110001; break;
        case 'r': c = 0b01110010; break;
        case 's': c = 0b01110011; break;
        case 't': c = 0b01110100; break;
        case 'u': c = 0b01110101; break;
        case 'v': c = 0b01110110; break;
        case 'w': c = 0b01110111; break;
        case 'x': c = 0b01111000; break;
        case 'y': c = 0b01111001; break;
        case 'z': c = 0b01111010; break;

        case 'A': c = 0b01000001; break;
        case 'B': c = 0b01000010; break;
        case 'C': c = 0b01000011; break;
        case 'D': c = 0b01000100; break;
        case 'E': c = 0b01000101; break;
        case 'F': c = 0b01000110; break;
        case 'G': c = 0b01000111; break;
        case 'H': c = 0b01001000; break;
        case 'I': c = 0b01001001; break;
        case 'J': c = 0b01001010; break;
        case 'K': c = 0b01001011; break;
        case 'L': c = 0b01001100; break;
        case 'M': c = 0b01001101; break;
        case 'N': c = 0b01001110; break;
        case 'O': c = 0b01001111; break;
        case 'P': c = 0b01010000; break;
        case 'Q': c = 0b01010001; break;
        case 'R': c = 0b01010010; break;
        case 'S': c = 0b01010011; break;
        case 'T': c = 0b01010100; break;
        case 'U': c = 0b01010101; break;
        case 'V': c = 0b01010110; break;
        case 'W': c = 0b01010111; break;
        case 'X': c = 0b01011000; break;
        case 'Y': c = 0b01011001; break;
        case 'Z': c = 0b01011010; break;

        case '0': c = 0b00110000; break;
        case '1': c = 0b00110001; break;
        case '2': c = 0b00110010; break;
        case '3': c = 0b00110011; break;
        case '4': c = 0b00110100; break;
        case '5': c = 0b00110101; break;
        case '6': c = 0b00110110; break;
        case '7': c = 0b00110111; break;
        case '8': c = 0b00111000; break;
        case '9': c = 0b00111001; break;

        case ' ': c = 0b00100000; break;
        case '!': c = 0b00100001; break;
        case '"': c = 0b00100010; break;
        case '#': c = 0b00100011; break;
        case '$': c = 0b00100100; break;
        case '%': c = 0b00100101; break;
        case '&': c = 0b00100110; break;
        case '\'': c = 0b00100111; break;
        case '(': c = 0b00101000; break;
        case ')': c = 0b00101001; break;
        case '*': c = 0b00101010; break;
        case '+': c = 0b00101011; break;
        case ',': c = 0b00101100; break;
        case '-': c = 0b00101101; break;
        case '.': c = 0b00101110; break;
        case '/': c = 0b00101111; break;

        case ':': c = 0b00111010; break;
        case ';': c = 0b00111011; break;
        case '<': c = 0b00111100; break;
        case '=': c = 0b00111101; break;
        case '>': c = 0b00111110; break;
        case '?': c = 0b00111111; break;

        case '@': c = 0b01000000; break;

        case '[': c = 0b01011011; break;
        case '¥': c = 0b01011100; break; // yen (/ cent)
        case ']': c = 0b01011101; break;
        case '^': c = 0b01011110; break;
        case '_': c = 0b01011111; break;

        case '`': c = 0b01100000; break;

        case '{': c = 0b01111011; break;
        case '|': c = 0b01111100; break;
        case '}': c = 0b01111101; break;
        //case '': c = 0b01111011; break; // right arrow
        //case '': c = 0b01111011; break; // left arrow

        //case '\n': break;

        default:  c = 0b00100011; break; // default is #
    }
    LCD_code(0b1000000000+c); //display char on LCD
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

void LCD_clear() {LCD_code(0b0000000001);}

// if display is turned on, turn it off
// display OFF, cursor OFF, blinking OFF
void LCD_off()   {
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
    switch(row) {
        case 1:  LCD_code(0b0010000000 + 0x00 + (pos-1)); break;
        case 2:  LCD_code(0b0010000000 + 0x40 + (pos-1)); break;
        //case  3: LCD_code(0b0010000000 + 0x14 + (pos-1)); break;
        //case  4: LCD_code(0b0010000000 + 0x54 + (pos-1)); break;
        default: LCD_code(0b0010000000 + 0x00 + (pos-1)); break; // default is 1st row
    }
}

void LCD_home() {LCD_code(0b0000000010);}

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