#ifndef ISR_H
#define ISR_H

#include "util.h"
#include "types.h"

typedef struct 
{
    DWord ds;
    DWord edi, esi, ebp, esp, ebx, edx, ecx, eax;
    DWord int_id;
    DWord int_err;
} __attribute__((packed)) InterruptFrame;

void exceptionHandler(void);

#endif