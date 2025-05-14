
/*
 * File:   main.h
 * Author: weyth
 *
 * Created on 4 avril 2025, 14:53
 */

#ifndef LCD_H
#define LCD_H
#include <stdio.h>
#include <stdlib.h>

char lcd_init(void);
char lcd_command(
    unsigned char command); // Fix the name from cldcommand to lcd_command
char lcd_write_char(char c);
char lcd_write_string(const char *str);
char lcd_goto(unsigned char row, unsigned char col);
char lcd_clear(void);

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

// LCD JHD 162A addresses and commands
enum LCD_COMMANDS {
    // LCD Commands
    LCD_CLEAR_DISPLAY = 0x01,
    LCD_RETURN_HOME = 0x02,
    LCD_ENTRY_MODE_SET = 0x04,
    LCD_DISPLAY_CONTROL = 0x08,
    LCD_CURSOR_SHIFT = 0x10,
    LCD_FUNCTION_SET = 0x20,
    LCD_SET_CGRAM_ADDR = 0x40,
    LCD_SET_DDRAM_ADDR = 0x80,

    // Entry mode flags
    LCD_ENTRY_RIGHT = 0x00,
    LCD_ENTRY_LEFT = 0x02,
    LCD_ENTRY_SHIFT_INCREMENT = 0x01,
    LCD_ENTRY_SHIFT_DECREMENT = 0x00,

    // Display control flags
    LCD_DISPLAY_ON = 0x04,
    LCD_DISPLAY_OFF = 0x00,
    LCD_CURSOR_ON = 0x02,
    LCD_CURSOR_OFF = 0x00,
    LCD_BLINK_ON = 0x01,
    LCD_BLINK_OFF = 0x00,

    // Function set flags
    LCD_8BIT_MODE = 0x10,
    LCD_4BIT_MODE = 0x00,
    LCD_2LINE = 0x08,
    LCD_1LINE = 0x00,
    LCD_5x10DOTS = 0x04,
    LCD_5x8DOTS = 0x00,

    // DDRAM addresses for line starts
    LCD_LINE1_ADDR = 0x00,
    LCD_LINE2_ADDR = 0x40
};

#endif /* LCD_H */
