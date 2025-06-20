#include "interrupt_setup.h"
#include "io.h"
#include "util.h"

__attribute__((aligned(16)))
static IDTEntry IDT[256]; // 256 total interrupts
static IDTRegister IDT_register;

void setIDTEntry(size_t index, void(*callback)(), Byte attrib) 
{
    IDTEntry* target = &IDT[index];
    target->attrib = attrib;
    target->reserved = 0; 
    target->kernel_cs = 0x08; // selectors use byte offset
    target->isr_low = (DWord)callback & 0xFFFF;
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

    static void (*irq_table[16])() = 
    {
        NULL,     // IRQ0 (timer)
        irq33,    // IRQ1 (keyboard) 
        NULL,     // IRQ2 (reserved)
        NULL, NULL, NULL, NULL, NULL,  // IRQ3–7
        NULL, NULL, NULL, NULL, NULL, NULL, NULL  // IRQ8–15
    };


    IDT_register.base = (DWord)&IDT[0]; 
    IDT_register.limit = sizeof(IDT) - 1;

    // zero out the whole IDT 
    memset(IDT, 0, sizeof(IDT)); 

    // bind the first 32 isr handlers (these are for CPU tweak outs)
    for (size_t i = 0; i < 32; ++i) 
    {
        setIDTEntry(i, isr_table[i], 0x8E); // ring 0, 32 bit interrupt, with presence
    }

    // 32 + 15 max irqs
    for (size_t i = 0; i < (sizeof(irq_table) / 8); ++i)
    {
        size_t offset = 32; 
        setIDTEntry(offset + i, irq_table[i], 0x8E);
    }

    PIC_remap(32, 40); // map the pic to interrupts 32-47

    loadIDT(&IDT_register);
}

// sequence goes like this 
// enable reinit
// new offsets
// configure daisy chaining
// operation flags
void PIC_remap(Byte pic1, Byte pic2) 
{
    outB(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); // expect 4 command words to follow and begin reinitializing
    ioWait();
    outB(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    ioWait(); 

    outB(PIC1_DATA, pic1); // the offset of the irqs first pic 
    ioWait();
    outB(PIC2_DATA, pic2); // offset of the irqs for the second pic 
    ioWait(); 

    outB(PIC1_DATA, 4); // irq2 = slave pic 
    ioWait(); 
    outB(PIC2_DATA, 2); // slave pic should know which irq its on
    ioWait();

    outB(PIC1_DATA, ICW4_8086); // use modern configuration 
    ioWait(); 
    outB(PIC2_DATA, ICW4_8086); // same here 
    ioWait();

    // enable all hardware interrupts 
    outB(PIC1_DATA, 0xFD); 
    outB(PIC2_DATA, 0xFF);
}

void PIC_sendEndOfInterrupt(Byte irq_id)
{
    if (irq_id >= 8) 
    {
        outB(PIC2_COMMAND, PIC_EOI); // send to the second pic instead
        return;
    }

    outB(PIC1_COMMAND, PIC_EOI);
}
