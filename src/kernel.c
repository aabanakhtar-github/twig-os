#include "kernel.h"
#include "gdt.h"
#include "interrupt_setup.h"
#include "stdbool.h"
#include "stdarg.h"
#include "util.h"
#include "shell.h"
#include "memory.h"
#include "ramdisk.h"

#define KERNEL_TAG

static Kernel kernel; 
static char input_buffer[KEYBOARD_BUFFER_SIZE];

void runBackground(bool* should_print_prompt)
{
    if (*should_print_prompt) 
    {
        Kernel_printF("twig-os $ ");
        *should_print_prompt = false;
    }

    // print out the inputs ig
    RingBuffer* buf = getKeyboardBuffer();
    RingBuffer* input_buffer = &getKernel()->input_buffer;

    PopResult pop = RingBuffer_pop(buf);
    if (pop.success) 
    {
        getKernel()->terminal.mode = TM_UNPROTECTED;

        // make it available for readline
        RingBuffer_push(input_buffer, pop.data); 

        Terminal_putChar(&getKernel()->terminal, pop.data, TC_WHITE, TC_BLUE);
    }
}

void initKernel(void)
{
    Terminal_init(&kernel.terminal); 
    Terminal_clear(&kernel.terminal); 

    /* load Descriptors */
    initGDT();
    /* load interrupts */
    initInterrupts();
    /* load devices! */
    initKeyboard();
    
    /* create the universal input buffer*/
    kernel.input_buffer.buffer = (Byte*)input_buffer; 
    kernel.input_buffer.buffer_size = sizeof(input_buffer); 
    kernel.input_buffer.head = 0; 
    kernel.input_buffer.tail = 0; 

    initMemory(); /*setup mem blocks*/
    initDisk(); /* setup disk */

    splashScreen();
}

void loopKernel(void)
{
    bool should_print_prompt = true;

    while (true) 
    {
        runBackground(&should_print_prompt);
        TString input = Kernel_readLine(); 
        shellRun(&input);
        TString_destroy(&input);

        should_print_prompt = true;
    }
}

void splashScreen(void) 
{
    Kernel_printF("                                 Twig-OS  v0.1.0                               ");
    Kernel_printF("               Repository: https://github.com/aabanakhtar/twig-os              ");
    Kernel_printF("===============================================================================\n\n");
}

Kernel *getKernel(void)
{
    return &kernel; 
}

void Kernel_printF(const char* fmt, ...)
{
    Terminal* term = &getKernel()->terminal;
    term->mode = TM_PROTECTED;
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
                // custom for TString
                case 'T': {
                    TString str = va_arg(args, TString);
                    Terminal_putStr(term, str.buffer);
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

size_t tryRead(char *buffer, size_t buffer_size)
{
    RingBuffer* in_buf = &getKernel()->input_buffer;

    if (RingBuffer_isEmpty(in_buf))
        return 0;

    size_t length = RingBuffer_length(in_buf);
    size_t i = 0;

    for (; i < length && i < (buffer_size - 1); ++i) 
    {
        // read the chracter
        char c = in_buf->buffer[(in_buf->tail + i) % in_buf->buffer_size];
        
        if (c == '\n') 
        {
            // Copy full line including newline
            for (size_t j = 0; j <= i && j < (buffer_size - 1); ++j) 
            {
                buffer[j] = in_buf->buffer[(in_buf->tail + j) % in_buf->buffer_size];
            }
            buffer[i + 1] = '\0'; 

            // Advance tail past the line
            in_buf->tail = (in_buf->tail + i + 1) % in_buf->buffer_size;

            return i + 1;
        }
    }

    return 0; 
}

TString Kernel_readLine(void)
{
    char input[KEYBOARD_BUFFER_SIZE] = {0};
    while (tryRead(input, KEYBOARD_BUFFER_SIZE) <= 0) 
    {
        bool temp = false; 
        runBackground(&temp); // still collect inputs;
    } 

    // remove weird characters and bakcspace 
    char sanitized[KEYBOARD_BUFFER_SIZE] = {0}; 
    sanitizeInput(input, sanitized);
    // convert to heap string
    TString as_string;
    TString_initFrom(&as_string, sanitized);
    return as_string; 
}
