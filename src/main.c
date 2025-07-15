#if defined(__linux__)
#error("Cannot build using linux compiler")
#endif

#if !defined(__i386__)
#error("Cannot build without i686 compiler")
#endif

#define kmain entryPoint

#include "kernel.h"
#include "util.h"
#include "tcontainers.h"
#include "memory.h"

extern void bingr();

/* kmain: program starts here*/
void kmain(void)
{
    initKernel(); 
    
    loopKernel();
    // hang forever
    halt();
}
