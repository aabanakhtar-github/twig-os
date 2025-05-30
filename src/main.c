#if defined(__linux__)
#error("Cannot build using linux compiler")
#endif

#if !defined(__i386__)
#error("Cannot build without i686 compiler")
#endif

#define main entryPoint

#include "util.h"
#include "terminal_io.h"


void main(void)
{
    Terminal term;
    Terminal_init(&term);
    Terminal_clear(&term);
    Terminal_putStr(&term, "hello world! This is twig-os                         \n                   BIG WRAPPER TEST!!!!!"
    "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n you shall feel my wrath\n\n hi");
    halt();
}
