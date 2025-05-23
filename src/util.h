#ifndef UTIL_H
#define UTIL_H

#include "types.h"

inline void halt(void)
{
    // hang forever
    for (;;)
    {
        asm volatile("hlt");
    }
}

inline size_t stringLength(const char* str)
{
    size_t length = 0;
    while(str[length] != 0) 
    {
        ++length;
    }

    return length;
}

#endif
