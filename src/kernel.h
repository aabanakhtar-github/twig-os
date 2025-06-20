#ifndef KERNEL_H
#define KERNEL_H

#include "terminal.h"

typedef struct Kernel 
{
   Terminal terminal; 
} Kernel;

void initKernel(void);
void loopKernel(void);
Kernel* getKernel(void);

// formatting and stuff
void Kernel_printF(const char* fmt, ...);
void Kernel_readLine(char *buffer, size_t buffer_size);
#endif // KERNEL_H