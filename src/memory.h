#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"
#include "stdbool.h"

typedef struct MemBlock 
{
    bool used; 
    size_t size; 
    struct MemBlock* next; 
} MemBlock;

void initMemory(void);
void printMemoryBlocks(void);
void* alloc(size_t n);
void free(void* ptr);

#endif // MEMORY_H