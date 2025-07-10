#include "shell.h"
#include "kernel.h"
#include "util.h"


bool shellRun(TString* string) 
{
    const char* s = strtok(string->buffer, " ");

    if (strcmp(s, "about") == 0)
    {
        about();
    }
    else if (strcmp(s, "clear") == 0) 
    {
        clear();
    }
    else if (strcmp(s, "reboot") == 0) 
    {
        reboot(); 
    }
    else if (strcmp(s, "echo") == 0)
    {
        echo();
    }
    else if (strcmp(s, "echo") == 0)
    {
        echo();
    }
    else if (strcmp(s, "") == 0) 
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

void echo(void)
{
    char* arg = strtok(NULL, "");
    
    if (arg == NULL)
    {
        Kernel_printF("echo: not enough arguments\n");
        return; 
    }

    Kernel_printF("%s\n", arg);
}
