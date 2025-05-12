/*
 * File:   main.h
 * Author: weyth
 *
 * Created on 4 avril 2025, 14:53
 */

#ifndef KEY_H
#define KEY_H
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

char kp_init(void);
char kp_read(void);

/**
 * Enum representing keypad values
 * Arranged in a 4x4 matrix:
 * BIT   4 5 6 7
 * 0     1 2 3 4
 * 1     5 6 7 8
 * 2     9 0 A B
 * 3     C D E F
 */
enum KeypadValue {
    KP_1 = 0x11,
    KP_2 = 0x21,
    KP_3 = 0x31,
    KP_4 = 0x41,
    KP_5 = 0x12,
    KP_6 = 0x22,
    KP_7 = 0x32,
    KP_8 = 0x42,
    KP_9 = 0x13,
    KP_0 = 0x23,
    KP_A = 0x33,
    KP_B = 0x43,
    KP_C = 0x14,
    KP_D = 0x24,
    KP_E = 0x34,
    KP_F = 0x44
};

#endif /* KEY_H */
