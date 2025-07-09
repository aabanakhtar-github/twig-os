#ifndef RAMDISK_H
#define RAMDISK_H

#include "types.h"

#define MAX_FILES 32
#define MAX_FILESIZE 4096 // 4 kb 

typedef struct RamFile 
{
    const char* name; 
    Byte* data; 
    size_t size;
} RamFile; 

void createFile(const char* name); 
void deleteFile(const char* name); 
const char* tree(void);

#endif // RAMDISK_H