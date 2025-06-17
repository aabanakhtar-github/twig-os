#include "isr.h"
#include "io.h"
#include "kernel.h"
#include "interrupt_setup.h"

static const char* interrupt_messages[32] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved (15)",
    "x87 Floating Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating Point Exception",
    "Virtualization Exception",
    "Reserved (21)",
    "Reserved (22)",
    "Reserved (23)",
    "Reserved (24)",
    "Reserved (25)",
    "Reserved (26)",
    "Reserved (27)",
    "Reserved (28)",
    "Reserved (29)",
    "Security Exception",
    "Reserved (31)"
};

void isrHandler(InterruptFrame* stack)
{
    Terminal* t = &getKernel()->terminal;
    if (stack->int_id < 32) 
    {
        Kernel_printF("An exception occured of id: %d and caused by: %s\n", stack->int_id, interrupt_messages[stack->int_id]);
        halt();
    }

    Kernel_printF("An interrupt occured.\n");
}

void irqHandler(InterruptFrame* stack)
{
    inB(0x60); 
    Kernel_printF("An IRQ has occured! %d \n", stack->int_id);
    PIC_sendEndOfInterrupt(stack->int_id - 32); // -32 because the eoi function expects offest based on PIC relative mapping
}

void exceptionHandler(void)
{
    Terminal_putStr(&getKernel()->terminal, "An unrecoverable exception occured"); 
    // halt the system
    __asm__ volatile("cli; hlt"); 
}
