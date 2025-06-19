#include "kernel.h"
#include "gdt.h"
#include "interrupt_setup.h"
#include "stdbool.h"
#include "stdarg.h"

static void splashScreen(void);

static Kernel kernel; 

void initKernel(void) 
{
    /* load Descriptors */
    initGDT();
    /* load interrupts */
    initInterrupts();
    
    Terminal_init(&kernel.terminal); 
    Terminal_clear(&kernel.terminal);
    splashScreen();
}

static void splashScreen(void) 
{
    Kernel_printF("================================================================================");
    Kernel_printF("                                Twig-OS  v0.1.0                                 ");
    Kernel_printF("================================================================================");
    Kernel_printF("             Repository: https://github.com/aabanakhtar/twig-os                 ");
    Kernel_printF("================================================================================");
}

Kernel *getKernel(void)
{
    return &kernel; 
}

void Kernel_printF(const char* fmt, ...)
{
    Terminal* term = &getKernel()->terminal;
    va_list args;
    va_start(args, fmt);

    for (size_t i = 0; fmt[i] != '\0'; ++i)
    {
        if (fmt[i] == '%' && fmt[i + 1] != '\0')
        {
            i++;
            char spec = fmt[i];

            switch (spec)
            {
                case 'd': {
                    int val = va_arg(args, int);
                    Terminal_putInt(term, val);
                    break;
                }
                case 'x': {
                    int val = va_arg(args, int);
                    Terminal_putHex(term, val);
                    break;
                }
                case 's': {
                    const char* str = va_arg(args, const char*);
                    Terminal_putStr(term, str);
                    break;
                }
                case 'c': {
                    char ch = (char)va_arg(args, int);
                    Terminal_putChar(term, ch, TC_WHITE, TC_BLUE);
                    break;
                }
                case 'f': {
                    double val = va_arg(args, double);
                    Terminal_putDouble(term, val);
                    break;
                }
                case '%': {
                    Terminal_putChar(term, '%', TC_WHITE, TC_BLUE);
                    break;
                }
                default:
                    // Unknown specifier; print it raw
                    Terminal_putChar(term, '%', TC_WHITE, TC_BLUE);
                    Terminal_putChar(term, spec, TC_WHITE, TC_BLUE);
                    break;
            }
        }
        else
        {
            Terminal_putChar(term, fmt[i], TC_WHITE, TC_BLUE);
        }
    }

    va_end(args);
}
