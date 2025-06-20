#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include "stdbool.h"
#include "ring_buffer.h"

typedef struct KeyboardState
{
    RingBuffer keyboard_buffer;
    bool shift_pressed;
} KeyboardState;

// init
void initKeyboard();

void keyboardHandler(void);
char numberRowShift(char c);
// buffer management
RingBuffer* getKeyboardBuffer(void);

#endif // KEYBOARD_DRIVER_H