#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H

#include "types.h"

// who designed ts
typedef struct GDTEntry
{
    Word limit_low; 
    Word base_low; 
    Byte base_middle; 
    Byte access;
    Byte flags;
    Byte base_high; 
} __attribute__((packed)) GDTEntry;


typedef struct GDTPointer
{
    Word limit;
    DWord base;
} __attribute__((packed)) GDTPointer;

typedef struct TSSEntry {
    DWord prev_tss;   // Previous TSS (if hardware task switching is used)
    DWord esp0;       // Stack pointer for ring 0
    DWord ss0;        // Stack segment for ring 0
    DWord esp1;       // Stack pointer for ring 1
    DWord ss1;        // Stack segment for ring 1
    DWord esp2;       // Stack pointer for ring 2
    DWord ss2;        // Stack segment for ring 2
    DWord cr3;        // Page directory base register
    DWord eip;        // Instruction pointer
    DWord eflags;     // Flags register
    DWord eax;        // General purpose registers
    DWord ecx;
    DWord edx;
    DWord ebx;
    DWord esp;        // Stack pointer
    DWord ebp;        // Base pointer
    DWord esi;        // Source index
    DWord edi;        // Destination index
    DWord es;         // Segment selectors
    DWord cs;
    DWord ss;
    DWord ds;
    DWord fs;
    DWord gs;
    DWord ldt;        // Local descriptor table selector
    Word trap;       // Trap on task switch
    Word iomap_base; // I/O map base address
} __attribute__((packed)) TSSEntry;

typedef struct IDTEntry 
{
    Word isr_low; 
    Word kernel_cs; // where the cs will be set to (in case we're in user mode)
    Byte reserved; 
    Byte attrib; 
    Word isr_high; 
} __attribute__((packed)) IDTEntry;

typedef struct IDTRegister 
{
    Word limit; 
    DWord base; 
} __attribute__((packed)) IDTRegister; 

// in asm 
extern void loadGDT(DWord address); 
extern void loadIDT(IDTRegister* address);

// global descriptor stuff
void initGDT(void);

// interrupts related 
void initInterrupts(void);
void setIDTEntry(size_t index, void(*callback)(), Byte attrib);

void exceptionHandler(void);

// isrs (0 - 31) represent CPU Exceptions and BAD things
// must be handled to avoid crashing 
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif