#if defined(__linux__)
#error("Cannot build using linux compiler")
#endif

#if !defined(__i386__)
#error("Cannot build without i686 compiler")
#endif

#define main entryPoint

#include "kernel.h"
#include "util.h"

void main(void)
{
    initKernel();
    Kernel* kernel = getKernel();
    volatile int x =  (1/0);
    __asm__ volatile("int $0x4");
    __asm__ volatile("int $0x3");
    // hang forever
    halt();
}
