#include "memory.h"
#include "kernel.h"

#define HEAP_SIZE 0x100000 // 1mb
#define MEMBLOCK_SIZE sizeof(MemBlock)

extern char _KERNEL_HEAP_START[]; 
static void* heap_start;
static MemBlock* blocks; 
static size_t bump = 0; 

#define MEMBLOCK_LOOP(block_identifier) \
    MemBlock* block_identifier = blocks; \
    while (block_identifier != NULL) \

#define MEMBLOCK_UPDATE(block_identifier) block_identifier = block_identifier->next

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

void printMemoryBlocks(void)
{
    Kernel_printF("---------------\n");
    int i = 0; 
    MEMBLOCK_LOOP(block)
    {
        Kernel_printF("id: %d, used: %s, location: %d, payload size: %x\n", i++, block->used ? "true" : "false", (DWord)block, block->size);
        MEMBLOCK_UPDATE(block);
    }
}

void* alloc(size_t n)
{
    MEMBLOCK_LOOP(existing_block) 
    {
        if (!existing_block->used && existing_block->size >= n)
        {
            existing_block->used = true;
            return (void*)((Byte*)existing_block + MEMBLOCK_SIZE); 
        }

        MEMBLOCK_UPDATE(existing_block);
    }

    MemBlock* block = (MemBlock*)((Byte*)heap_start + bump);
    block->used = true; 
    block->size = n; 
    
    bump += MEMBLOCK_SIZE;
    void* return_addr = (Byte*)heap_start + bump;
    bump += n; // take up space

    block->next = blocks; 
    blocks = block; 
    return return_addr;
}

void free(void* ptr)
{
    MemBlock* block = (MemBlock*)((Byte*)ptr - MEMBLOCK_SIZE);
    block->used = false; 
}
