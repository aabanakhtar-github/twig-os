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
}

void main(void)
{
    setup();

    loopKernel();

    // hang forever
    halt();
}
