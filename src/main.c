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
    alloc(4);
    alloc(4);
    loopKernel();

    // hang forever
    halt();
}
