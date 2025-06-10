#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

// Define this only ONCE in the whole project
typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} time;

// Declare the global variable (definition will be in main.c)
extern time current_time;

#endif /* TYPES_H */