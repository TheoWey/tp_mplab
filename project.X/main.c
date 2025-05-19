/*
 * File:   main.c
 * Author: weyth
 *
 * Created on 4 avril 2025, 14:53
 */

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#include "tim.h"
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

/*
 *
 */
int main(int argc, char **argv) {
    // Initialize the device
    TRISD = 0x00; // Initialize PORTD to 0
    init_interrupt();
    // __delay_ms(1000);
    bool up = 0, menu = 0;
    while (1) {
        read_button(&up, &menu);
        if (menu) {
            way = !way; // Toggle direction
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
