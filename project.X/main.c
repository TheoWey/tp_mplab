/*
 * File:   main.c
 * Author: weyth
 *
 * Created on 4 avril 2025, 14:53
 */

#include "main.h"

time current_time = {10, 20, 0}; // Initialize current_time to 10:20:00

int main(int argc, char **argv) {

    // Initialize the microcontroller
    init7Seg(); // Initialize 7-segment display

    init_interrupt(); // Initialize interrupts
    init_timer();     // Initialize timer
    clear7Seg();      // Clear the 7-segment display

    while (1) {
        /* code */
        displayTime(
            current_time); // Display the current time on the 7-segment display
    }

    return (EXIT_SUCCESS);
}
