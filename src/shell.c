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
    else if (strcmp(s, "cat") == 0) 
    {
        cat();
    }
    else if (strcmp(s, "write") == 0) 
    {
        write();
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

    if (!createFile(filename)) 
    {
        Kernel_printF("touch: Couldn't create file. no space.\n");
    }

    Kernel_printF("Created file %s\n.", filename);
}

void write(void)
{
    char* filename = strtok(NULL, " "); 
    char* data = strtok(NULL, "");
    if (filename == NULL || data == NULL) 
    {
        Kernel_printF("write: not enough args.\n");
    }

    if (!writeToFile(filename, data)) 
    {
        Kernel_printF("write: unable to write\n");
    }
}

void cat(void)
{
    char* filename = strtok(NULL, ""); 
    if (filename == NULL) 
    {
        Kernel_printF("cat: not enough args.\n"); 
        return;
    }

    RamFile* file = getFile(filename);
    if (file == NULL) 
    {
        Kernel_printF("cat: file doesn't exist\n");
        return;
    }

    // skip pad byte
    for (size_t i = 1; i < file->size; ++i) 
    {
        Kernel_printF("%c", file->data[i]);
    }

    Kernel_printF("\n");
}

void rm(void)
{
    char* filename = strtok(NULL, ""); 
    if (filename == NULL) 
    {
        Kernel_printF("rm: could not remove file.\n");
        return;
    }

    if (!deleteFile(filename)) 
    {
        Kernel_printF("rm: could not remove file.\n");
    }

    Kernel_printF("Deleted file: %s\n", filename);
}