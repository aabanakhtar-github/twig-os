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
    Terminal_putStr(&getKernel()->terminal, "Welcome to Twig-OS!");

    // hang forever
    halt();
}
