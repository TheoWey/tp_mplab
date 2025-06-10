/*
 * File:   main.h
 * Author: weyth
 *
 * Created on 4 avril 2025, 14:53
 */

#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "types.h" // Include types first

// REMOVE these includes to break circular dependencies
#include "7seg.h" 
#include "tim.h"

#define _XTAL_FREQ 20e6 // 20MHz

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

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */