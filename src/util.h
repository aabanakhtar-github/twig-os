#ifndef UTIL_H
#define UTIL_H

#include "types.h"
#include "stdbool.h"

void halt(void);

// C standard reimplementations
size_t strlen(const char* str);
int strcmp(const char* a, const char* b);
void* memset(void* ptr, int x, size_t n_bytes);
char* strtok(char* str, const char* delimeter);
char* getOlds(void);
// USEFUL TOOLS
// expects a buffer of 12 characters at max
void integerToString(int value, char* str);
// expects a buffer of size 9
void integerToStringHex(int hex_value, char* str);
// expects a buffer of size 32
void doubleToString(double value, char* str); 

bool isNumeric(char c);
bool isAlpha(char c);
char toUpper(char c);

#endif 
