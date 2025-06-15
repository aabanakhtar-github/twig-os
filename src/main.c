#if defined(__linux__)
#error("Cannot build using linux compiler")
#endif

#if !defined(__i386__)
#error("Cannot build without i686 compiler")
#endif

#define main entryPoint

#include "kernel.h"
#include "util.h"

void setup(void)
{
    initKernel();
    Kernel* kernel = getKernel();
}

void main(void)
{
    setup();

    Kernel_printF("Hello World, this is printf %d \n", 34);

    __asm__ volatile("int $0x3");
    // hang forever
    halt();
}
