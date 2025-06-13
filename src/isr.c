#include "isr.h"
#include "kernel.h"

void isr_handler(InterruptFrame* stack)
{
    Terminal_putStr(&getKernel()->terminal, "Hi");
}