#include "kernel.h"
#include "descriptors.h"
#include "stdbool.h"

static void splashScreen(void);

static Kernel kernel; 
static bool kernel_ready = false; 

void initKernel(void) 
{
    /* load Descriptors */
    initGDT();
    /* load interrupts */
    initInterrupts();
    
    Terminal_init(&kernel.terminal); 
    Terminal_clear(&kernel.terminal);
    splashScreen();
}

static void splashScreen(void) 
{
    Kernel* kernel = getKernel();
    Terminal_putStr(&kernel->terminal, "================================================================================");
    Terminal_putStr(&kernel->terminal, "                                Twig-OS  v0.1.0                                 ");
    Terminal_putStr(&kernel->terminal, "================================================================================");
    Terminal_putStr(&kernel->terminal, "             Repository: https://github.com/aabanakhtar/twig-os                 ");
    Terminal_putStr(&kernel->terminal, "================================================================================");
}

Kernel *getKernel(void)
{
    return &kernel; 
}