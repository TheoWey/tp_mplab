#include "tim.h"

void init_interrupt(void) {
    // Configure Timer0
    INTCONbits.T0IF = 0; // Clear Timer0 interrupt flag
    INTCONbits.T0IE = 1; // Enable Timer0 interrupt
    INTCONbits.GIE = 1;  // Enable global interrupts
}

void init_timer(void) {
    // Configure Timer0
    OPTION_REGbits.T0CS = 0;   // Use internal instruction clock (Fosc/4)
    OPTION_REGbits.T0SE = 0;   // Increment on low-to-high
    OPTION_REGbits.PSA = 0;    // Assign prescaler to Timer0
    OPTION_REGbits.PS = 0b111; // 1:256 prescaler
}

void __interrupt() timer0_isr(void) {
    static uint8_t overflow_count = 0;
    if (INTCONbits.TMR0IF) {   // Check if Timer0 interrupt flag is set
        INTCONbits.TMR0IF = 0; // Clear Timer0 interrupt flag
        // Add your code here to handle the Timer0 interrupt
        overflow_count++;
        if (overflow_count >= 76) { // ~1s reached
            overflow_count = 0;
            current_time.seconds++;
            if (current_time.seconds >= 60) {
                current_time.seconds = 0;
                current_time.minutes++;
                if (current_time.minutes >= 60) {
                    current_time.minutes = 0;
                    current_time.hours++;
                    if (current_time.hours >= 24) {
                        current_time.hours = 0;
                    }
                }
            }
        }
        // Update the 7-segment display with the current time
    }
}