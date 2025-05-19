#include "tim.h"

void init_interrupt(void) {
    // Configure Timer0 for 1-second interrupt
    // Setup Timer0
    OPTION_REGbits.T0CS = 0;   // Use internal instruction clock (Fosc/4)
    OPTION_REGbits.T0SE = 0;   // Increment on low-to-high
    OPTION_REGbits.PSA = 0;    // Assign prescaler to Timer0
    OPTION_REGbits.PS = 0b111; // 1:256 prescaler

    TMR0 = 60; // Preload value

    // Enable interrupts
    INTCONbits.T0IF = 0; // Clear Timer0 interrupt flag
    INTCONbits.T0IE = 1; // Enable Timer0 interrupt
    INTCONbits.GIE = 1;  // Enable global interrupts
    PORTD = 0x00;        // Initialize PORTD to 0
}

bool way = 1; // 1 for right, 0 for left

void __interrupt() interrupt_handler(void) {
    static uint8_t overflow_count = 0;
    if (INTCONbits.TMR0IF) {   // Check if Timer0 interrupt flag is set
        INTCONbits.TMR0IF = 0; // Clear Timer0 interrupt flag
        overflow_count++;
        if (overflow_count >= 100) { // ~1s reached
            overflow_count = 0;
            chenillard(way); // Call chenillard function
        }
    }
}

void chenillard(bool right) {
    const uint8_t MAX_CHENILLARD = 0x80;
    const uint8_t MIN_CHENILLARD = 0x01;

    static uint8_t chenillard = 1;
    static bool max = 0;

    if (right == 1) {
        if (chenillard == MAX_CHENILLARD) {
            max = 1;
        }
        if (max) {
            chenillard = MIN_CHENILLARD;
            max = 0;
        } else {
            chenillard = chenillard << 1;
        }
    } else {
        if (chenillard == MIN_CHENILLARD) {
            max = 1;
        }
        if (max) {
            chenillard = MAX_CHENILLARD;
            max = 0;
        } else {
            chenillard = chenillard >> 1;
        }
    }
    PORTD = chenillard;
}