#include "util.h"

void halt(void)
{
    // hang forever
    while (1) 
    {
    }

    __asm__ volatile("hlt");
}

size_t strlen(const char* str)
{
    size_t length = 0;
    while(str[length] != 0) 
    {
        ++length;
    }

    return length;
}

void* memset(void* ptr, int x, size_t n_bytes)
{
    Byte val = (Byte)x; 
    Byte* target = ptr; 
    
    for (size_t i = 0; i < n_bytes; ++i) 
    {
        i[target] = val;
    }

    return (void*)target;
}

void integerToString(int value, char* str)
{
    char* ptr = str;
    int is_negative = 0;

    if (value == 0)
    {
        *ptr++ = '0';
        *ptr = '\0';
        return;
    }

    if (value < 0)
    {
        is_negative = 1;
        value = -value;
    }

    char* start = ptr;
    while (value != 0)
    {
        int digit = value % 10;
        *ptr++ = '0' + digit;
        value /= 10;
    }

    if (is_negative)
    {
        *ptr++ = '-';
    }

    *ptr = '\0';

    for (char* end = ptr - 1; start < end; ++start, --end)
    {
        char temp = *start;
        *start = *end;
        *end = temp;
    }
}

void integerToStringHex(int hex_value, char* str)
{
    static const char hex_chars[] = "0123456789ABCDEF";
    
    int i;
    for (i = 7; i >= 0; --i)
    {
        str[7 - i] = hex_chars[(hex_value >> (i * 4)) & 0xF];
    }
    str[8] = '\0';
}