#include "isr.h"
#include "kernel.h"

void isr_handler(InterruptFrame* stack)
{
    __asm__ volatile("hlt");
}