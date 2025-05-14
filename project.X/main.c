/*
 * File:   main.c
 * Author: weyth
 *
 * Created on 4 avril 2025, 14:53
 */

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

#include "adc.h"
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define _XTAL_FREQ 20e6

/*
 *
 */
int main(int argc, char **argv) {

    // Initialize the ADC
    ADC_Init();
    lcd_init();
    uint16_t adcValue[4] = {0}; // Array to hold ADC values
    float temperature = 0.0;
    // Read the ADC value
    // Print the ADC value
    char buffer[16];
    lcd_goto(0, 0); // Move to the first line
    lcd_write_string("Hello, World!");
    lcd_goto(1, 0); // Move to the second line
    while (1) {
        __delay_ms(500);         // Delay for 1 second
        lcd_goto(1, 0);          // Move to the second line
        ADC1_read(&adcValue[0]); // Read ADC value
        ADC2_read(&adcValue[1]); // Read ADC value
        ADC3_read(&adcValue[2]); // Read ADC value
        ADC4_read(&adcValue[3]); // Read ADC value

        ADC_convert(&adcValue[3], &temperature);

        __delay_ms(2000); // Delay for 1 second
        lcd_clear();      // Clear the LCD
        lcd_goto(0, 0);   // Move to the first line
        sprintf(buffer, "ADC1: %d", adcValue[0]);
        lcd_write_string(buffer); // Display ADC1 value
        lcd_goto(1, 0);           // Move to the second line
        sprintf(buffer, "ADC2: %d", adcValue[1]);
        lcd_write_string(buffer); // Display ADC2 value

        __delay_ms(2000); // Delay for 1 second
        lcd_clear();      // Clear the LCD
        lcd_goto(0, 0);   // Move to the third line
        sprintf(buffer, "ADC3: %d", adcValue[2]);
        lcd_write_string(buffer); // Display ADC3 value
        lcd_goto(1, 0);           // Move to the second line
        sprintf(buffer, "ADC4: %f", temperature);
        lcd_write_string(buffer); // Display ADC3 value
    }

    return (EXIT_SUCCESS);
}
