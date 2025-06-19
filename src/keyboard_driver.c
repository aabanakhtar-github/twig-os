#include "keyboard_driver.h"
#include "types.h"
#include "io.h"
#include "kernel.h"
#include "util.h"

#define KEYBOARD_PORT 0x60
// scancodes
#define LEFT_SHIFT_PRESSED 0x2A
#define RIGHT_SHIFT_PRESSED 0x36
#define LEFT_SHIFT_RELEASED 0xAA
#define RIGHT_SHIFT_RELEASED 0xB6

static KeyboardState state;

static SignedByte us_keyboard[128] = 
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
    '9', '0', '-', '=', '\b',	/* Backspace */
    '\t',			/* Tab */
    'q', 'w', 'e', 'r',	/* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
    '\'', '`',   0,		/* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
    'm', ',', '.', '/',   0,				/* Right shift */
    '*',
    0,	/* Alt */
    ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
    '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
    '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void keyboardHandler(void)
{
    Byte input = inB(KEYBOARD_PORT);

    // this key was released
    if (input >= 128) 
    {
       if (input == LEFT_SHIFT_RELEASED)
       {
            state.shift_pressed = false;
            return;
       } 
    } 
    // test dummy for now
    else
    {
        if (input == LEFT_SHIFT_PRESSED)
        {
            state.shift_pressed = true;
            return;
        }
        
        char key = us_keyboard[input];
        if (state.shift_pressed && key != 0 && !isNumeric(key)) 
        {
            // convert to upper case
            key = toUpper(key);
        } 
        else if (state.shift_pressed && key != 0 && isNumeric(key))
        {
           key = numberRowShift(key);
        }

        Kernel_printF("%c", key);
    }
}

char numberRowShift(char c)
{
    char characters[10] = {'!', '@', '#', '$', '%', '^', '&', '*', '(' , ')'};
    size_t offset = (size_t)(c - '0');

    // why did they put zero at the end bruh
    if (c != '0')
    {
        offset--;
    } else 
    {
        offset = 9;
    }

    return characters[offset]; 
}

