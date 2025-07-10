#ifndef KERNEL_H
#define KERNEL_H

#include "terminal.h"
#include "ring_buffer.h"
#include "keyboard_driver.h"
#include "tcontainers.h"

typedef struct Kernel 
{
   Terminal terminal;
   RingBuffer input_buffer;
} Kernel;

void runBackground(bool *should_print_prompt);
void initKernel(void);
void loopKernel(void);
Kernel* getKernel(void);

// formatting and stuff
void splashScreen(void);
void Kernel_printF(const char* fmt, ...);
size_t tryRead(char* buffer, size_t size);
TString Kernel_readLine(void);

#endif // KERNEL_H