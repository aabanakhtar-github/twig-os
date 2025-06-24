#ifndef TERMINAL_IO_H
#define TERMINAL_IO_H

#include "types.h"

typedef enum TerminalColors 
{
    TC_BLACK = 0, 
    TC_BLUE = 1, 
    TC_GREEN = 2, 
    TC_CYAN = 3, 
    TC_RED = 4, 
    TC_PURPLE = 5, 
    TC_BROWN = 6, 
    TC_GRAY = 7, 
    TC_DARK_GRAY = 8, 
    TC_LIGHT_BLUE = 9, 
    TC_LIGHT_GREEN = 10, 
    TC_LIGHT_CYAN = 11, 
    TC_LIGHT_RED = 12, 
    TC_LIGHT_PURPLE = 13, 
    TC_YELLOW = 14, 
    TC_WHITE = 15 
} TerminalColor;

#define TERMINAL_WIDTH 80
#define TERMINAL_HEIGHT 25

// to protect form brakcpasce
typedef enum TerminalMode 
{
    TM_PROTECTED, 
    TM_UNPROTECTED
} TerminalMode;

typedef struct Terminal
{
    // pointer to video mem
    volatile Word* video_memory;
    TerminalMode mode; 
    size_t cursor_x;
    size_t cursor_y;
    // to protect the characters from backspace
    size_t last_protected_region_x;
    size_t last_protected_region_y;
} Terminal;

// handy tool (thanks Chat GPT)
#define TERM_CHAR_COLOR_WORD(ch, fg, bg) ((Word)(ch) | ((Word)(fg | (bg << 4)) << 8))

void Terminal_init(Terminal* term);
void Terminal_backspace(Terminal* term);


void Terminal_putChar(Terminal* term, char c, TerminalColor fg_color, TerminalColor bg_color); 
void Terminal_putStr(Terminal* term, const char* s);
void Terminal_putInt(Terminal* term, const int i); 
void Terminal_putHex(Terminal* term, const int i); 
void Terminal_putDouble(Terminal* term, const double d); 
void Terminal_clear(Terminal* term);

// remove backspaaces
void sanitizeInput(const char* original, char* target);

#endif // TERMINAL_IO_H

