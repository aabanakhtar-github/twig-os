#include "memory.h"
#include "types.h"

DWord page_directory[1024] __attribute__((aligned(4096)));

void setupPaging(void)
{

}

Byte *memAlloc(size_t n)
{
    return NULL;
}
