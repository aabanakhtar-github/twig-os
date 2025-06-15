#ifndef UTIL_H
#define UTIL_H

#include "types.h"

void halt(void);

// C standard reimplementations
size_t strlen(const char* str);
void* memset(void* ptr, int x, size_t n_bytes);

// USEFUL TOOLS
// expects a buffer of 12 characters at max
void integerToString(int value, char* str);
// expects a buffer of size 9
void integerToStringHex(int hex_value, char* str);
// expects a buffer of size 
void doubleToString(double value, char* str); 

#endif 
