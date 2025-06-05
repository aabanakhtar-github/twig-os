#include "kernel.h"
#include "gdt.h"
#include "stdbool.h"

static Kernel kernel; 
static bool kernel_ready = false; 

static void initKernel() 
{
    /* load Descriptors */
    initGDT();

    Terminal_init(&kernel.terminal); 
    Terminal_clear(&kernel.terminal);
}

Kernel *getKernel()
{
    if (!kernel_ready) 
    {
        initKernel(); 
        kernel_ready = true;
    }

    return &kernel; 
}