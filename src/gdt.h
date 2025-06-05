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

// in asm 
extern void loadGDT(DWord address); 
void initGDT(void);