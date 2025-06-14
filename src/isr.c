#include "isr.h"
#include "kernel.h"

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

void isr_handler(InterruptFrame* stack)
{
    Terminal* t = &getKernel()->terminal;
    if (stack->int_id < 32) 
    {
        Terminal_putStr(t, "A cpu exception has occured; Interrupt ID: "); 
        Terminal_putInt(t, stack->int_id); 
        Terminal_putStr(t, ". Cause: ");
        Terminal_putStr(t, interrupt_messages[stack->int_id]);
        halt();
    }

    Terminal_putStr(t, "Interrupt occured.\n");
}

void exceptionHandler(void)
{
    Terminal_putStr(&getKernel()->terminal, "An unrecoverable exception occured"); 
    // halt the system
    __asm__ volatile("cli; hlt"); 
}
