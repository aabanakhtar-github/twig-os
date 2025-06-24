#ifndef KERNEL_H
#define KERNEL_H

#include "terminal.h"
#include "ring_buffer.h"
#include "keyboard_driver.h"

typedef struct Kernel 
{
   Terminal terminal;
   RingBuffer input_buffer;
} Kernel;

void initKernel(void);
void loopKernel(void);
Kernel* getKernel(void);

// formatting and stuff
void Kernel_printF(const char* fmt, ...);
size_t Kernel_readLine(char *buffer, size_t buffer_size);
#endif // KERNEL_H