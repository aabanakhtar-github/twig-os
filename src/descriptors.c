#include "descriptors.h"
#include "util.h"

static GDTEntry GDT_entries[6]; 
static TSSEntry TSS;

__attribute__((aligned(16)))
static IDTEntry IDT[256]; // 256 total interrupts
static IDTRegister IDT_register;

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

void setIDTEntry(size_t index, void(*callback)(), Byte attrib) 
{
    IDTEntry* target = &IDT[index];
    target->attrib = attrib;
    target->reserved = 0; 
    target->kernel_cs = 0x08; // selectors use byte offset
    target->isr_low = (Word)callback & 0xFFFF;
    target->isr_high = ((DWord)callback >> 16) & 0xFFFF; 
}

void initInterrupts(void)
{
    static void (*isr_table[32])() = 
    {
        isr0, isr1, isr2,  isr3,  isr4,  isr5,  isr6,  isr7,
        isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15,
        isr16,isr17,isr18, isr19, isr20, isr21, isr22, isr23,
        isr24,isr25,isr26, isr27, isr28, isr29, isr30, isr31
    };

    IDT_register.base = (DWord)&IDT[0]; 
    IDT_register.limit = sizeof(IDT) - 1;

    // zero out the whole IDT 
    memset(IDT, NULL, sizeof(IDT)); 

    // bind the first 32 isr handlers (these are for CPU tweak outs)
    for (size_t i = 0; i < 32; ++i) 
    {
        setIDTEntry(i, isr_table[i], 0x8E); // ring 0, 32 bit interrupt, with presence
    }

    loadIDT(&IDT_register);
}
