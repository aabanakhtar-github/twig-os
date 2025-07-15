#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "types.h"
#include "isr.h"
typedef struct Registers 
{
    DWord eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags; 
} Registers;

typedef enum TaskState 
{
    READY, 
    WAIITNG, 
    RUNNING,
} TaskState;

typedef struct Task 
{
    Registers registers;
    struct Task* next_task;  
} Task;

void createTask(Task* task, void(*f)(void), DWord flags); 
void initScheduler(void); 
void join(void);
// save, new 
extern void switchTask(Registers* old_task, Registers* new_task);

#endif // SCHEDULER_H