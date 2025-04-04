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
    uint8_t switchs = 0;      // Initialize switchs variable

    // Configure inputs for buttons
    TRISB = 0x01;
    TRISC = 0x01;
    while (1) {
        read_button(&up, &menu);
        if (up == menu) {
            if (up != menu) {
                right = !right;
            }
            if (menu) {
                speed += 1;
                if (speed > 10) { // Changed to > instead of >=
                    speed = 1;    // Reset to 1 instead of 0
                }
            }
            chenillard(right);

            __delay_ms(100); // Base delay of 100ms * speed
        } else {
            read_switch(&switchs); // Read switchs state
            PORTD = switchs; // If not in chenillard mode, display switchs state
        }
    }

    return (EXIT_SUCCESS);
}

void read_button(bool *up, bool *menu) {
    static bool up_mem, menu_mem = 0;
    uint8_t up_read = PORTBbits.RB0;
    uint8_t menu_read = PORTBbits.RB1;

    *up = (up_mem != up_read && PORTBbits.RB0 == 0);
    *menu = (menu_mem != menu_read && PORTBbits.RB1 == 0);

    up_mem = up_read;
    menu_mem = menu_read;
}

void read_switch(uint8_t *switchs) {
    *switchs = PORTC;
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
