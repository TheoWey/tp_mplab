/*
 * File:   tim.h
 * Author: weyth
 *
 * Created on 4 avril 2025, 14:53
 */

#ifndef TIM_H
#define TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h" 
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "7seg.h"
// #include "main.h"

#define _XTAL_FREQ 20e6 // 20MHz

void init_interrupt(void);
void init_timer(void);
void start_timer(void);
void stop_timer(void);

void __interrupt() timer0_isr(void);

#ifdef __cplusplus
}
#endif

#endif /* TIM_H */