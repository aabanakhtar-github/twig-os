#if defined(__linux__)
#error("Cannot build using linux compiler")
#endif

#if !defined(__i386__)
#error("Cannot build without i686 compiler")
#endif

#define kmain entryPoint

#include "kernel.h"
#include "util.h"
#include "string.h"
#include "memory.h"

void kmain(void)
{
    initKernel(); 
    TString string; 
    TString_initFrom(&string, "Hello World!"); 
    printMemoryBlocks(); 
    int* a = alloc(4);

    Kernel_printF("%T\n", string);

    printMemoryBlocks();
    TString_destroy(&string);
    free(a);
    printMemoryBlocks();
    loopKernel();

    // hang forever
    halt();
}
