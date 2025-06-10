#ifndef SEVEN_SEG_H
#define SEVEN_SEG_H

#include "types.h"
#include <xc.h>

#define _XTAL_FREQ 20e6 // 20MHz

// Function prototypes
void init7Seg(void);                     // Initialize 7-segment display
void displayDigit(unsigned char digit);  // Display a single digit (0-9)
void selectChannel(unsigned char digit); // Select which channel to display
void clear7Seg(void);
void displayTime(time current_time); // Display time on 7-segment display

#endif // SEVEN_SEG_H