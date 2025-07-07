#if defined(__linux__)
#error("Cannot build using linux compiler")
#endif

#if !defined(__i386__)
#error("Cannot build without i686 compiler")
#endif

#define main entryPoint

#include "kernel.h"
#include "util.h"
#include "memory.h"

void setup(void)
{
    initKernel();
}

void main(void)
{
    setup();

    int* a = kMalloc(sizeof(int)); 
    *a = 799999;
    Kernel_printF("\n%d %x", *a, a); 
    loopKernel();

    // hang forever
    halt();
}
