#ifndef KERNEL_H
#define KERNEL_H

#include "terminal.h"

typedef struct Kernel 
{
   Terminal terminal; 
} Kernel;

void initKernel(void);
Kernel* getKernel(void);

// formatting and stuff
void Kernel_printF(const char* fmt, ...);

#endif // KERNEL_H