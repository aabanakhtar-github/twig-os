#ifndef RAMDISK_H
#define RAMDISK_H

#include "types.h"
#include "tcontainers.h"
#include "stdbool.h"

#define MAX_FILES 32
#define MAX_FILESIZE 4096 // 4 kb 
#define RAMDISK_MAXFILES 32

#define READ 0x1 
#define WRITE 0x2

typedef struct RamFile 
{
    TString name; 
    Byte* data;
    Byte permissions; 
    size_t size;
} RamFile; 

extern RamFile ramdisk[]; 

void initDisk(void);

bool createFile(const char* name); 
void deleteFile(const char* name);
RamFile* getFile(const char* name); 

#endif // RAMDISK_H