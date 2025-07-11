#include "ramdisk.h"
#include "kernel.h"
#include "util.h"

#define DISK_TAG "[RAMDISK] "

RamFile ramdisk[RAMDISK_MAXFILES];
extern char _KERNEL_RAMDISK_START[]; // linker script
 
void initDisk(void)
{
    Kernel_printF(DISK_TAG "Setting up Ramdisk!\n");

    for (size_t i = 0; i < RAMDISK_MAXFILES; ++i) 
    {
        RamFile* entry = ramdisk + i; 
        entry->data = (Byte*)_KERNEL_RAMDISK_START + i * MAX_FILESIZE;
        entry->name.buffer = NULL;
        entry->permissions = READ;  
        entry->size = 0; 
    }
}

bool createFile(const char* name)
{

    for (size_t i = 0; i < RAMDISK_MAXFILES; ++i) 
    {
        if (ramdisk[i].size > 0)
        {
            continue;
        }
        
        RamFile* entry = ramdisk + i; 
        entry->size = 1;  // pad byte for used status
        entry->permissions = READ;
        TString_initFrom(&entry->name, name);
        Kernel_printF("Teehee.\n");
        return true;
    }

    return false;
}

void deleteFile(const char* name)
{
    for (size_t i = 0; i < RAMDISK_MAXFILES; ++i)
    {
        if (strcmp(ramdisk[i].name.buffer, name) == 0) 
        {
            Kernel_printF("Foundem.\n");
            ramdisk[i].permissions = 0x0; 
            ramdisk[i].size = 0; 
            TString_destroy(&ramdisk[i].name); 
            ramdisk[i].name.buffer = NULL; 
            return;
        }
    }
}

RamFile* getFile(const char *name)
{
    for (size_t i = 0; i < RAMDISK_MAXFILES; ++i) 
    {
        if (strcmp(ramdisk[i].name.buffer, name) == 0) 
        {
            return &ramdisk[i]; 
        }
    }

    return NULL;
}

