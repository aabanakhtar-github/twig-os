#include "util.h"
#include "terminal.h"
#include "stdarg.h"

void Terminal_init(Terminal* term)
{
    term->video_memory = (Word*)0xB8000; 
    term->cursor_x = 0; 
    term->cursor_y = 0;
}

void Terminal_putChar(Terminal* term, char c, TerminalColor fg_color, TerminalColor bg_color)
{
    if (c == '\n' || term->cursor_x >= TERMINAL_WIDTH)
    {
        term->cursor_x = 0;
        term->cursor_y++;

        if (term->cursor_y >= TERMINAL_HEIGHT)
        {
            // scroll up
            for (size_t y = 1; y < TERMINAL_HEIGHT; ++y)
            {
                for (size_t x = 0; x < TERMINAL_WIDTH; ++x)
                {
                    term->video_memory[(y - 1) * TERMINAL_WIDTH + x] = 
                        term->video_memory[y * TERMINAL_WIDTH + x];
                }
            }

            // clear the last line
            for (size_t x = 0; x < TERMINAL_WIDTH; ++x)
            {
                term->video_memory[(TERMINAL_HEIGHT - 1) * TERMINAL_WIDTH + x] =
                    TERM_CHAR_COLOR_WORD(' ', fg_color, bg_color);
            }

            term->cursor_y = TERMINAL_HEIGHT - 1;
        }

        if (c == '\n')
            return;
    }

    int location = term->cursor_y * TERMINAL_WIDTH + term->cursor_x;
    term->video_memory[location] = TERM_CHAR_COLOR_WORD(c, fg_color, bg_color);
    term->cursor_x++;
}


void Terminal_putStr(Terminal *term, const char *s)
{
    for (size_t i = 0; i < strlen(s); ++i)
    {
        Terminal_putChar(term, s[i], TC_WHITE, TC_BLUE);
    }
}

void Terminal_putInt(Terminal *term, const int i)
{
    char buffer[12];
    integerToString(i, buffer); 
    Terminal_putStr(term, buffer);
}

void Terminal_putHex(Terminal *term, const int i)
{
    char buffer[9];
    integerToStringHex(i, buffer);
    Terminal_putStr(term, "0x");
    Terminal_putStr(term, buffer);
}

void Terminal_putDouble(Terminal *term, const double d)
{
    char buffer[32];
    doubleToString(d, buffer); 
    Terminal_putStr(term, buffer); 
}

void Terminal_clear(Terminal* term) 
{
    for (size_t y = 0; y < TERMINAL_HEIGHT; ++y) 
    {
        for (size_t x = 0; x < TERMINAL_WIDTH; ++x) 
        {
            int location = y * TERMINAL_WIDTH + x;
            term->video_memory[location] = TERM_CHAR_COLOR_WORD(' ', TC_WHITE, TC_BLUE);
        }
    }
}
