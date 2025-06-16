#ifndef IO_H
#define IO_H

#include "types.h"

inline void outB(Word port, Byte val) 
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

inline Byte inB(Word port) 
{
    Byte ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

// small delay
inline void ioWait(void)
{
    outB(0x80, 0); // unused port 
}

#endif // IO_H