#if defined(__linux__)
#error("Cannot build using linux compiler")
#endif

#if !defined(__i386__)
#error("Cannot build without i686 compiler")
#endif

void putChar(char c) 
{
    static int i = 0;
    volatile char* vidmem = (char*)0xB8000;
    vidmem[i * 2]     = c;     // character
    vidmem[i * 2 + 1] = 0x07;  // attribute: light gray on black
    ++i;
}

void print(const char* str)
{
    while (*str)
    {
        putChar(*str++);
    }
}

void halt()
{
    print("SOCES ROBOTICS FELL OFF OS");

    // hang forever
    for (;;)
    {
        asm volatile("hlt");
    }
}

extern "C" void entryPoint()
{
    halt();
}
