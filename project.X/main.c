/*
 * File:   main.c
 * Author: weyth
 *
 * Created on 4 avril 2025, 14:53
 */

#include "main.h"
/*
 *
 */
int main(int argc, char **argv) {
    static bool right = 0;
    static uint8_t speed = 1; // Start with speed 1 instead of 0
    bool up = 0, menu = 0;    // Properly initialize both variables
    chenillard(right);
    __delay_ms(100 * speed); // Base delay of 100ms × speed
    return (EXIT_SUCCESS);
}

void chenillard(bool right) {
    const uint8_t MAX_CHENILLARD = 0x80;
    const uint8_t MIN_CHENILLARD = 0x01;

    static uint8_t chenillard = 0;
    static bool max = 0;

    TRISD = 0x00;
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
