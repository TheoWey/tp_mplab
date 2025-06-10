#include "7seg.h"

void init7Seg(void) {
    TRISD = 0x00; // Set PORTB as output for segments
    TRISC = 0x00; // Set PORTC as output for digit select
    PORTD = 0x00; // Clear PORTB
    PORTC = 0x00; // Clear PORTC
}

void displayDigit(unsigned char digit) {
    // Define the segment patterns for digits 0-9
    const unsigned char segmentPatterns[11] = {
        0b11000000, // 0
        0b11111001, // 1
        0b10100100, // 2
        0b10110000, // 3
        0b10011001, // 4
        0b10010010, // 5
        0b10000010, // 6
        0b11111000, // 7
        0b10000000, // 8
        0b10010000, // 9
        0b11111111, // Blank (not used)
    };

    if (digit < 11) {
        PORTC = segmentPatterns[digit]; // Set segments for the digit
    }
}

void selectChannel(unsigned char channel) {
    // Define the channel selection for 4x7-segment display
    const unsigned char channelSelect[4] = {
        0b11110111, // Channel 4 (SV3 signal 4)
        0b11111011, // Channel 3 (SV3 signal 3)
        0b11111101, // Channel 2 (SV3 signal 2)
        0b11111110, // Channel 1 (SV3 signal 1)
    };

    if (channel < 4) {
        PORTD = channelSelect[channel]; // Activate the selected channel
    }
}

void clear7Seg(void) {
    for (unsigned char i = 0; i < 4; i++) {
        selectChannel(i); // Select each channel
        displayDigit(10); // Display blank
        __delay_us(500);  // Delay for a short time
    }
}

void displayTime(time current_time) {
    // Display hours
    uint8_t tens_minutes = current_time.minutes / 10;
    uint8_t tens_seconde = current_time.seconds / 10;
    uint8_t units_minutes = current_time.minutes % 10;
    uint8_t units_seconds = current_time.seconds % 10;

    if (tens_minutes != 0) {
        selectChannel(3);
        displayDigit(tens_minutes); // Tens place
        __delay_us(500);
    }
    selectChannel(2);
    displayDigit(units_minutes); // Units place
    __delay_us(500);
    // Display minutes
    if (tens_seconde != 0) {
        selectChannel(1);
        displayDigit(tens_seconde); // Tens place
        __delay_us(500);
    }
    selectChannel(0);
    displayDigit(units_seconds); // Units place
    __delay_us(500);

    // Display seconds (optional, if needed)
}