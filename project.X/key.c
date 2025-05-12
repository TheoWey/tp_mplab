#include "key.h"
#include <stdint.h> // For proper integer types
#include <xc.h>

// Define pins for matrix keypad (adjust based on your hardware)
#define ROW_PORT PORTB // Port for rows
#define ROW_TRIS TRISB // TRIS register for rows
#define COL_PORT PORTB // Port for columns (changed from PORTB to PORTC)
#define COL_TRIS                                                               \
    TRISB // TRIS register for columns (changed from TRISB to TRISC)

// Row and column masks (assuming rows on RA0-RA3 and columns on RB4-RB7)
#define ROW_MASK 0x0F // Lower 4 bits (0-3)
#define COL_MASK 0xF0 // Upper 4 bits (4-7)

#define _XTAL_FREQ 20e6
/**
 * Initialize keypad - configure I/O ports
 * Returns 0 on success, non-zero on error
 */
char kp_init(void) {
    // Configure rows as inputs with pull-ups
    ROW_TRIS |= ROW_MASK; // Set row pins as inputs

    // Enable weak pull-ups on PORTB
    OPTION_REG &= ~0x80; // Clear RBPU bit (bit 7) to enable pull-ups

    // Configure columns as outputs
    COL_TRIS &= ~COL_MASK; // Set column pins as outputs
    COL_PORT &= ~COL_MASK; // Initialize columns to low

    return 0; // Success
}

/**
 * Read the keypad and return the pressed key value
 * Returns 0 if no key is pressed, otherwise returns the key code
 */
char kp_read(void) {
    char key = 0;
    uint8_t row, col;

    // Scan each column by setting one column low at a time
    for (col = 0; col < 4; col++) {
        // Set all columns high
        COL_PORT |= COL_MASK;

        // Set current column low
        COL_PORT &= ~(0x10 << col); // 0x10, 0x20, 0x40, 0x80

        // Small delay for signal stabilization
        __delay_us(50);

        // Read rows - with pull-ups, pressed keys read as 0
        row = (~ROW_PORT) & ROW_MASK; // Invert to make pressed keys = 1

        if (row) { // If any row is active (key pressed)
            if (row & 0x01)
                key = col + 1; // First row
            else if (row & 0x02)
                key = col + 5; // Second row
            else if (row & 0x04)
                key = col + 9; // Third row
            else if (row & 0x08)
                key = col + 13; // Fourth row

            // Wait for key release to avoid multiple detections
            while ((~ROW_PORT) & ROW_MASK) {
                __delay_ms(10); // Debounce delay
            }

            break; // Exit column loop when key found
        }
    }

    // Map key codes to actual characters
    if (key) {
        switch (key) {
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return '0';
        case 11:
            return 'A';
        case 12:
            return 'B';
        case 13:
            return 'C';
        case 14:
            return 'D';
        case 15:
            return 'E';
        case 16:
            return 'F';
        }
    }

    return 0; // No key pressed
}
