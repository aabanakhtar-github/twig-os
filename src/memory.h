#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

extern DWord _KERNEL_HEAP_START;


inline void *setupMemory(void) 
{
    return &_KERNEL_HEAP_START;
}

void* kMalloc(size_t size);

#endif // MEMORY_H