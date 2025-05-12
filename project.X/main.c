#include "key.h"
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS   // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP =                                                           \
    OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
        // (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM
                         // code protection off)
#pragma config WRT =                                                           \
    OFF // Flash Program Memory Write Enable bits (Write protection off; all
        // program memory may be written to by EECON control)
#pragma config CP =                                                            \
    OFF // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20e6

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

int main(void) {
    char key;
    // Initialize LCD and Keypad
    lcd_init();
    kp_init();

    // Display welcome message
    lcd_goto(0, 0);
    lcd_write_string("Welcome to");
    lcd_goto(1, 0);
    lcd_write_string("Keypad LCD");

    // Main loop
    while (1) {
        key = kp_read(); // Read the keypad

        if (key == 0) {           // If no key is pressed
            continue;             // Skip to the next iteration
        } else if (key == 0xFF) { // If an error occurs
            lcd_goto(1, 0);
            lcd_clear();
            lcd_write_string("Error");
            continue;             // Skip to the next iteration
        } else if (key == 0xFE) { // If a special key is pressed
            lcd_goto(1, 0);
            lcd_clear();
            lcd_write_string("Special Key");
            continue; // Skip to the next iteration
        } else {
            // Display the pressed key on the LCD
            lcd_goto(1, 0);
            lcd_clear();
            lcd_write_string(&key); // Display the key value
        }
        // Optionally, you can add a delay here to avoid rapid key detection
        __delay_ms(100); // Adjust the delay as needed
    }

    return 0;
}