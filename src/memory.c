#include "memory.h"
#include "types.h"

#define PRESENT  0x1
#define RW 0x2


DWord page_directory[1024] __attribute__((aligned(4096)));
DWord first_page_table[1024] __attribute__((aligned(4096)));

void setupPaging(void)
{
    for (int i = 0; i < 1024; ++i) {
        first_page_table[i] = (i * 4096) | PRESENT | RW; 
    }

    page_directory[0] = (DWord)&first_page_table | PRESENT | RW;
    writeCR3((DWord)&page_directory); 
    DWord cr0 = readCR0(); 
    // set the paging and protection bits
    cr0 |= 0x80000001;
    writeCR0(cr0);
}

