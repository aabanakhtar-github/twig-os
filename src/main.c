#if defined(__linux__)
#error("Cannot build using linux compiler")
#endif

#if !defined(__i386__)
#error("Cannot build without i686 compiler")
#endif

#define kmain entryPoint

#include "kernel.h"
#include "util.h"
#include "memory.h"

void kmain(void)
{
    initKernel(); 
    alloc(4);
    int* a =  alloc(8);
    printMemoryBlocks(); 

    free(a); 
    printMemoryBlocks(); 

    alloc(4);
    printMemoryBlocks();

    loopKernel();

    // hang forever
    halt();
}
