#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "types.h"

struct FreeListEntry 
{

};

struct FreeList 
{

}; 

void setupPaging(void); 

Byte* memAlloc(size_t n); 
Byte* memFree(); 

#endif // ALLOCATOR_H