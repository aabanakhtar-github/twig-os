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

void kmain(void)
{
    initKernel(); 
    TString string; 
    TString_initFrom(&string, "\nHello World!"); 
    printMemoryBlocks(); 
    int* a = alloc(4);

    printMemoryBlocks();
    TString_destroy(&string);
    free(a);
    printMemoryBlocks();
    loopKernel();

    // hang forever
    halt();
}
