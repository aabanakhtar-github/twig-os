#ifndef STR_H
#define STR_H

#include "types.h"

/* twig strings!*/
typedef struct TString 
{
    char* buffer; 
    size_t size; 
} TString ;

void TString_initFrom(TString* str, const char* value);
void TString_append(const char c); 
void TString_destroy(TString* str); 

#endif