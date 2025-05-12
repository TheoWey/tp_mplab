#include "lcd.h"
#include <xc.h>

// LCD pin definitions - adjust as needed for your hardware
#define LCD_DATA_PORT PORTD // Port for data lines D4-D7
#define LCD_DATA_TRIS TRISD // Tris register for data port
#define LCD_DATA_MASK 0xF0  // Bits 4-7 for data (D4-D7)

#define LCD_RS_PORT PORTD // Port for Register Select
#define LCD_RS_TRIS TRISD // Tris register for RS
#define LCD_RS_PIN 0      // RC0 pin for RS

#define LCD_E_PORT PORTD // Port for Enable
#define LCD_E_TRIS TRISD // Tris register for Enable
#define LCD_E_PIN 1      // RC1 pin for Enable

#define _XTAL_FREQ 20e6

// Helper functions for LCD control
void lcd_pulse_enable(void);
void lcd_send_nibble(unsigned char nibble);
void lcd_send_byte(unsigned char byte, unsigned char rs);

char lcd_init(void) {
    // Initialize the LCD pins as outputs
    LCD_DATA_TRIS &= ~LCD_DATA_MASK;   // Data pins as output
    LCD_RS_TRIS &= ~(1 << LCD_RS_PIN); // RS pin as output
    LCD_E_TRIS &= ~(1 << LCD_E_PIN);   // E pin as output

    // Reset all pins to low
    LCD_DATA_PORT &= ~LCD_DATA_MASK;
    LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
    LCD_E_PORT &= ~(1 << LCD_E_PIN);

    // Wait for LCD to power up
    __delay_ms(50);

    // Initialize with 8-bit mode first (standard procedure)
    lcd_send_nibble(0x03);
    __delay_ms(5);
    lcd_send_nibble(0x03);
    __delay_us(200);
    lcd_send_nibble(0x03);
    __delay_us(200);

    // Switch to 4-bit mode
    lcd_send_nibble(0x02);
    __delay_us(100);

    // 4-bit mode, 2 lines, 5x8 font
    lcd_command(LCD_FUNCTION_SET | LCD_4BIT_MODE | LCD_2LINE | LCD_5x8DOTS);

    // Display on, cursor off, blink off
    lcd_command(LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON | LCD_CURSOR_OFF |
                LCD_BLINK_OFF);

    // Clear display
    lcd_command(LCD_CLEAR_DISPLAY);
    __delay_ms(2); // Clear command needs longer delay

    // Display on, cursor off, blink off
    lcd_command(LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON | LCD_CURSOR_OFF |
                LCD_BLINK_OFF);

    // Entry mode: increment cursor, no display shift
    lcd_command(LCD_ENTRY_MODE_SET | LCD_ENTRY_LEFT |
                LCD_ENTRY_SHIFT_DECREMENT);

    // And add a return statement at the end of lcd_init()
    return 0;
}

char lcd_command(unsigned char command) {
    lcd_send_byte(command, 0); // RS=0 for command

    // Short delay for most commands
    if (command == LCD_CLEAR_DISPLAY || command == LCD_RETURN_HOME) {
        __delay_ms(2); // These commands need longer delays
    } else {
        __delay_us(50);
    }

    return 0; // Success
}

char lcd_write_char(char c) {
    lcd_send_byte(c, 1); // RS=1 for data
    __delay_us(50);
    return 0; // Success
}

char lcd_goto(unsigned char row, unsigned char col) {
    unsigned char address;

    // Calculate DDRAM address based on row and column
    if (row == 0) {
        address = LCD_LINE1_ADDR + col;
    } else if (row == 1) {
        address = LCD_LINE2_ADDR + col;
    } else {
        return 1; // Error: Invalid row
    }

    // Set DDRAM address command
    lcd_command(LCD_SET_DDRAM_ADDR | address);
    return 0; // Success
}

char lcd_clear(void) {
    lcd_command(LCD_CLEAR_DISPLAY);
    __delay_ms(2); // Clear command needs longer delay
    return 0;      // Success
}

char lcd_write_string(const char *str) {
    while (*str) {
        if (lcd_write_char(*str++) != 0) {
            return 1; // Error
        }
    }
    return 0; // Success
}

// Helper function to pulse the Enable pin
void lcd_pulse_enable(void) {
    LCD_E_PORT |= (1 << LCD_E_PIN);  // Set E high
    __delay_us(1);                   // Enable pulse width >= 450ns
    LCD_E_PORT &= ~(1 << LCD_E_PIN); // Set E low
    __delay_us(1);                   // Command execution time
}

// Send 4 bits to LCD
void lcd_send_nibble(unsigned char nibble) {
    // Put nibble on upper 4 bits of port
    LCD_DATA_PORT &= ~LCD_DATA_MASK; // Clear data bits
    LCD_DATA_PORT |=
        ((nibble & 0x0F) << 4); // Set data bits (shifted to upper nibble)

    lcd_pulse_enable();
}

// Send a byte to LCD (in 4-bit mode, sends high nibble then low nibble)
void lcd_send_byte(unsigned char byte, unsigned char rs) {
    // Set RS pin (0 = command, 1 = data)
    if (rs)
        LCD_RS_PORT |= (1 << LCD_RS_PIN);
    else
        LCD_RS_PORT &= ~(1 << LCD_RS_PIN);

    // Send high nibble
    lcd_send_nibble(byte >> 4);

    // Send low nibble
    lcd_send_nibble(byte & 0x0F);
}
