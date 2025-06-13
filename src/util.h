#ifndef UTIL_H
#define UTIL_H

#include "types.h"

inline void halt(void)
{
    // hang forever
    while (1) 
    {
        asm volatile("hlt");
    }
}

inline size_t strlen(const char* str)
{
    size_t length = 0;
    while(str[length] != 0) 
    {
        ++length;
    }

    return length;
}

inline void* memset(void* ptr, int x, size_t n_bytes)
{
    Byte val = (Byte)x; 
    Byte* target = ptr; 
    
    for (size_t i = 0; i < n_bytes; ++i) 
    {
        i[target] = val;
    }

    return (void*)target;
}

#endif
