#include "util.h"

typedef struct {
    DWord int_err;      // pushed first (or dummy 0)
    DWord int_id;       // interrupt number
    DWord edi, esi, ebp, esp, ebx, edx, ecx, eax;  // pusha
    DWord ds;           // manually pushed
} __attribute__((packed)) InterruptFrame;