/*
 * File:   main.h
 * Author: weyth
 *
 * Created on 4 avril 2025, 14:53
 */

#ifndef tim_H
#define tim_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#define _XTAL_FREQ 20e6

#ifdef __cplusplus
}
#endif

void init_interrupt(void);
void __interrupt() interrupt_handler(void);
void chenillard(bool right);

#endif /* tim_H */