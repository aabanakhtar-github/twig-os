#include "tcontainers.h"
#include "memory.h"
#include "util.h"
#include "kernel.h"

void TString_initFrom(TString* str, const char* value)
{
    str->size = strlen(value); // include null term
    str->buffer = alloc(str->size + 1); 
    
    for (size_t i = 0; i < str->size; ++i) 
    {
        str->buffer[i] = value[i];
    }

    str->buffer[str->size] = 0; // null term lol 
}

void TString_destroy(TString *str)
{
    str->size = 0; 
    free(str->buffer); 
}
