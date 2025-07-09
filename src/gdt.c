#include "gdt.h"
#include "util.h"
#include "kernel.h"

static GDTEntry GDT_entries[6]; 
static TSSEntry TSS;

static void setGDTEntry(size_t index, int base, int access, int flags, int limit)
{
    GDTEntry* target = GDT_entries + index; 
    target->base_low = (Word)(base & 0xFFFF); // lower 16 bits 
    target->base_middle = (Byte)((base & 0xFF0000) >> 16); // upper 8 bits
    target->base_high = (Byte)((base & 0xFF000000) >> 24);

    target->limit_low = limit & 0xFFFF; 
    target->access = access; 

    // should look like | flags (4) | limit upper nibble (4) |
    target->flags = (flags << 4) | ((limit & 0xF0000) >> 16);
}

void initGDT(void)
{
    Kernel_printF("[GDT] Setting up GDT!\n");

    GDTPointer gdt_pointer = 
    { 
        .base =  (DWord)&GDT_entries, 
        .limit = sizeof(GDT_entries) - 1 // because zero index
    };

    setGDTEntry(0, 0, 0, 0, 0); // null descriptor
    setGDTEntry(1, 0, 0x9A, 0xC, 0xFFFFFFFF); // Kernel mode code segment
    setGDTEntry(2, 0, 0x92, 0xC, 0xFFFFFFFF); // Kernel mode data segment 
    setGDTEntry(3, 0, 0xFA, 0xC, 0xFFFFFFFF); // Userspace code segment ring 3
    setGDTEntry(4, 0, 0xF2, 0xC, 0xFFFFFFFF); // Userspace Data segment ring 3

    TSS.esp0 = 0x90000;  // Example top of kernel stack
    TSS.ss0 = 0x10;      // Kernel data segment selector
    setGDTEntry(5, (DWord)&TSS, 0x89, 0x0, sizeof(TSS) - 1); // task state segment for task switching

    loadGDT((DWord)&gdt_pointer);
}

