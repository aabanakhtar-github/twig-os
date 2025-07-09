#include "memory.h"
#include "kernel.h"

#define MEMBLOCK_SIZE sizeof(MemBlock)
#define KERNEL_HEAP_SIZE 0x100000

extern char _KERNEL_HEAP_START[]; 
static void* heap_start;
static void* heap_end;
static MemBlock* blocks; 
static size_t bump = 0; 

#define MEMBLOCK_LOOP(block_identifier) \
    MemBlock* block_identifier = blocks; \
    while (block_identifier != NULL) \

#define MEMBLOCK_UPDATE(block_identifier) block_identifier = block_identifier->next
#define MEMORY_INIT_TAG "[Memory] "

void initMemory(void)
{
    heap_start = (void*)(_KERNEL_HEAP_START);
    heap_end = heap_start + KERNEL_HEAP_SIZE; 
    blocks = (MemBlock*)heap_start;
    bump += MEMBLOCK_SIZE; 
    blocks->size = 0; 
    blocks->used = true; 
    blocks->next = NULL; 

    Kernel_printF(MEMORY_INIT_TAG "Memory loaded %d; Heap Size: %d\n", _KERNEL_HEAP_START, KERNEL_HEAP_SIZE);
    Kernel_printF(MEMORY_INIT_TAG "Initial bump: %d\n", bump);
    Kernel_printF(MEMORY_INIT_TAG "Memblock size: %d\n ", MEMBLOCK_SIZE);
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

    if ((Byte*)heap_start + bump >= (Byte*)heap_end)
    {

    }

    MemBlock* block = (MemBlock*)((Byte*)heap_start + bump);
    block->used = true; 
    block->size = n; 
    bump += MEMBLOCK_SIZE; // allocate the header
    bump += n; // take up space

    void* return_addr = (Byte*)block + MEMBLOCK_SIZE;
    
    block->next = blocks; 
    blocks = block; 
    return return_addr;
}

void free(void* ptr)
{
    MemBlock* block = (MemBlock*)((Byte*)ptr - MEMBLOCK_SIZE);
    block->used = false; 
}
