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
        entry->permissions = READ | WRITE;
        TString_initFrom(&entry->name, name);
        Kernel_printF("Teehee.\n");
        return true;
    }

    return false;
}

bool deleteFile(const char* name)
{
    RamFile* file = getFile(name); 
    if (name == NULL) 
    {
        return false; 
    }

    file->permissions = 0x0; 
    file->size = 0; 
    TString_destroy(&file->name); 
    file->name.buffer = NULL; 
    return true;
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

bool writeToFile(const char *name, const char *data)
{
    RamFile* file = getFile(name);
    size_t data_len = strlen(data);

    if (data_len + 2 > MAX_FILESIZE || !(file->permissions & WRITE))
    {
        return false;
    } 

    for (size_t i = 0; i < data_len; ++i)
    {
        file->data[i + 1] = data[i];
    }

    file->data[data_len + 1] = '\0';  // ensure null-terminated
    file->size = data_len + 2;        // pad + data + null

    return true;
}
