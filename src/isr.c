#include "isr.h"
#include "kernel.h"

void isr_handler(InterruptFrame* stack)
{
    Terminal_putStr(&getKernel()->terminal, "Hi, an interrupt occured!, id #");
    Terminal_putInt(&getKernel()->terminal, stack->int_id);
    Terminal_putStr(&getKernel()->terminal, "\n");
}