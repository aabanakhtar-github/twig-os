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
