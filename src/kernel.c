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

static void splashScreen() 
{
    Kernel* kernel = getKernel();
    Terminal_putStr(&kernel->terminal, "================================================================================");
    Terminal_putStr(&kernel->terminal, "                                Twig-OS  v0.1.0                                 ");
    Terminal_putStr(&kernel->terminal, "================================================================================");
    Terminal_putStr(&kernel->terminal, "             Repository: https://github.com/aabanakhtar/twig-os                 ");
    Terminal_putStr(&kernel->terminal, "================================================================================");
}

Kernel *getKernel()
{
    if (!kernel_ready) 
    {
        initKernel(); 
        kernel_ready = true;
        splashScreen();
    }

    return &kernel; 
}