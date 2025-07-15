#include "scheduler.h"
#include "memory.h"
#include "kernel.h"

#define TASK_STACK_SIZE 1024

static Task* current_task; 
static Task bing; 
static Task bom; 

void bingr(void)
{
    while (1) {
        Kernel_printF("shwim!\n");
        join();
    }
}


void bomr(void)
{
    while (1) {
        join();
    }
}

void initScheduler()
{
    current_task = &bing; 
    createTask(&bing, bingr,  0x202);
    createTask(&bom, bomr, 0x202); 

    bing.next_task = &bom; 
    bom.next_task = &bing;
}

void createTask(Task* task, void(*task_function)(void), DWord flags)
{
    task->registers.eax = 0; 
    task->registers.ebx = 0; 
    task->registers.ecx = 0; 
    task->registers.edx = 0; 
    task->registers.esi = 0; 
    task->registers.edi = 0; 
    task->registers.eflags = flags; // like the P registers on the 6502
    task->registers.eip = (DWord)task_function;
    task->registers.esp = (DWord)(alloc(TASK_STACK_SIZE) + TASK_STACK_SIZE - 4); // 16 bit aligned so we cooking here ig. also must grow downwards and is off by one
    task->next_task = NULL;
}

void join(void)
{
    Task* last = current_task;
    // point to the next task
    current_task = last->next_task; 
    switchTask(&last->registers, &current_task->registers); // let asm handle the rest
}