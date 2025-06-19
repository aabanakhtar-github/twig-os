#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include "stdbool.h"

typedef struct KeyboardState
{
    char input_buffer[4096];
    size_t buffer_last_charcter; 
    bool shift_pressed;
} KeyboardState;

void keyboardHandler(void);
char numberRowShift(char c);
// handle shift
void shift(void);
// buffer management

#endif // KEYBOARD_DRIVER_H