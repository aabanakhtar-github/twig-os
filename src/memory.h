#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"
#include "stdbool.h"
#include "stdalign.h"

typedef struct MemBlock 
{
    bool used; 
    size_t size; 
    struct MemBlock* next; 
} MemBlock __attribute__((aligned(4)));

// useful func i guess
inline uintptr_t align_up(uintptr_t address, size_t alignment) 
{
    return (address + alignment - 1) & ~(alignment - 1);
}

void initMemory(void);
void printMemoryBlocks(void);
void* alloc(size_t n);
void free(void* ptr);

#endif // MEMORY_H