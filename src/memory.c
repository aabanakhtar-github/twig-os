#include "memory.h"
#include "kernel.h"

#define HEAP_SIZE 0x100000 // 1mb
#define MEMBLOCK_SIZE sizeof(MemBlock)

extern char _KERNEL_HEAP_START[]; 
static void* heap_start;
static MemBlock* blocks; 
static size_t bump = 0; 

void initMemory(void)
{
    heap_start = (void*)(_KERNEL_HEAP_START);
    blocks = (MemBlock*)heap_start;
    bump += MEMBLOCK_SIZE; 
    blocks->size = 0; 
    blocks->used = true; 
    blocks->next = NULL; 

    Kernel_printF("Memory loaded %d\n", _KERNEL_HEAP_START);
    Kernel_printF("Initial bump: %d\n", bump);
    Kernel_printF("Memblock size: %d\n ", MEMBLOCK_SIZE);
}

void* alloc(size_t n)
{
    Kernel_printF("ALLOCATION================================\n");
    
    int bump_og = bump; 
    MemBlock* block = (MemBlock*)((Byte*)heap_start + bump);
    block->used = true; 
    block->size = n; 
    
    bump += MEMBLOCK_SIZE;
    void* return_addr = (Byte*)heap_start + bump;
    bump += n; // take up space

    block->next = blocks; 
    blocks = block; 

    MemBlock* node = blocks; 
    while (node != NULL) 
    {
        Kernel_printF("Address: %d\n", (DWord)node);
        node = node->next;
    }

    Kernel_printF("Bump size change:%d\n", bump - bump_og); 
    return return_addr;
}