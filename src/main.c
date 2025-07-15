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
#include "scheduler.h"

extern void bingr();

void kmain(void)
{
    initKernel(); 
    initScheduler(); 

    join(); 
    
    // hang forever
    halt();
}
