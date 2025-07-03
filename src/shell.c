#include "shell.h"
#include "kernel.h"
#include "util.h"


bool shellRun(const char* sanitized) 
{
    if (strcmp(sanitized, "about") == 0)
    {
        about();
    }
    else if (strcmp(sanitized, "clear") == 0) 
    {
        clear();
    }
    else if (strcmp(sanitized, "reboot") == 0) 
    {
        reboot(); 
    }
    else if (strcmp(sanitized, "help") == 0) 
    {
        help();
    }
    else if (strcmp(sanitized, "") == 0)
    {
    }
    else 
    {
        Kernel_printF("Twig: unknown command.\n");
        return false;
    }

    return true;
}

void about(void)
{
    Kernel_printF("\n      //\n");
    Kernel_printF("     //\n");
    Kernel_printF("  \\\\//\n");
    Kernel_printF("   ||\n");
    Kernel_printF("   ||\n");
    Kernel_printF("\n\n");
    Kernel_printF("  Twig OS, v0.0.1\n\n\n");     
}

void clear(void)
{
    Terminal_clear(&getKernel()->terminal);
}

void help(void) 
{
    static const char* commands[] = {
        "reboot - reboot the system", 
        "clear - clear the terminal", 
        "help - get help on commands", 
        "about - about TwigOS"
    };

    Kernel_printF("help:\n"); 

    for (size_t i = 0; i < (sizeof(commands) / sizeof(commands[0])); ++i) 
    {
        Kernel_printF("[%d] %s\n", i, commands[i]);
    }
}


void reboot(void)
{
    // triple fault the system
    __asm__ volatile (
        "lidt (%0)\n"
        "int $0x03\n"  // Trigger interrupt with invalid IDT
        :
        : "r" (0)      // Invalid IDT pointer
    );   
}
