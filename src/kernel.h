
#include "terminal.h"

typedef struct Kernel 
{
   Terminal terminal; 
} Kernel;

void initKernel(void);
Kernel* getKernel(void);

// formatting and stuff
void kprintf(const char* fmt, int);