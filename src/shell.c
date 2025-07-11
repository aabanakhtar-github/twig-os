#include "shell.h"
#include "kernel.h"
#include "util.h"
#include "ramdisk.h"

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
    else if (strcmp(s, "touch") == 0)
    {
        touch();
    }
    else if (strcmp(s, "ls") == 0) 
    {
        ls();
    }
    else if (strcmp(s, "rm") == 0) 
    {
        rm();
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

void ls(void)
{
    for (size_t i = 0; i < MAX_FILES; ++i) 
    {
        if (ramdisk[i].size > 0) 
        {
            Kernel_printF("%T, size: %d, permissions: %x\n", ramdisk[i].name, ramdisk[i].size, ramdisk[i].permissions);
        }
    }
}

void touch(void)
{
    char* filename = strtok(NULL, ""); 
    if (filename == NULL) 
    {
        Kernel_printF("touch: no filename proivded.\n");
        return;
    }

    createFile(filename);
    Kernel_printF("Created file %s\n.", filename);
}

void rm(void)
{
    char* filename = strtok(NULL, ""); 
    if (filename == NULL) 
    {
        Kernel_printF("rm: could not remove file.\n");
        return;
    }

    deleteFile(filename);
    Kernel_printF("Deleted file: %s\n", filename);
}