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

void initMemory(void);
void printMemoryBlocks(void);
void* alloc(size_t n);
void free(void* ptr);

#endif // MEMORY_H