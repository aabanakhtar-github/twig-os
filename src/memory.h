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

/*Byte* memAlloc(size_t n); 
Byte* memFree(); */


extern void writeCR0(DWord); 
__attribute__((unused)) extern DWord readCR0(void);
extern void writeCR3(DWord); 
extern DWord readCR3(DWord); 

#endif // ALLOCATOR_H