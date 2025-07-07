#include "memory.h"

void* kMalloc(size_t size)
{
    static int bump = 0; 
    bump += size;
    return (void*)(_KERNEL_HEAP_START + bump - size); 
}
