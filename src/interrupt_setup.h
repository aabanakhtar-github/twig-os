#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "types.h"

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define PIC_EOI 0x20

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */


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

extern void loadIDT(IDTRegister* address);
void initInterrupts(void);
void setIDTEntry(size_t index, void(*callback)(), Byte attrib);

// remap so we can access hardware interrupts through the programmable interrupt controller
void PIC_remap(Byte pic1, Byte pic2);
void PIC_sendEndOfInterrupt(Byte irq_id);

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

#endif // INTERRUPTS_H