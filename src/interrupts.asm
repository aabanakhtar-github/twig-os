[BITS 32]

; define a macro to create our cpu related isr handlers
%macro ISR_NO_ERROR_CODE 1 ; 1 PARAM MACRO 
    [GLOBAL isr%1]
    isr%1:
        cli ; clear the interrupt
        push dword 0 ; put in a random byte, because some interrupts have error codes
        push dword %1 ; push the interrupt 
        jmp isr_dispatch ; jump to the common isr handler 
%endmacro

%macro ISR_ERROR_CODE 1 
    [GLOBAL isr%1]
    isr%1: 
        cli
        push dword %1 
        jmp isr_dispatch
%endmacro

ISR_NO_ERROR_CODE 0
ISR_NO_ERROR_CODE 1
ISR_NO_ERROR_CODE 2
ISR_NO_ERROR_CODE 3
ISR_NO_ERROR_CODE 4
ISR_NO_ERROR_CODE 5
ISR_NO_ERROR_CODE 6
ISR_NO_ERROR_CODE 7
ISR_ERROR_CODE    8
ISR_NO_ERROR_CODE 9
ISR_ERROR_CODE    10
ISR_ERROR_CODE    11
ISR_ERROR_CODE    12
ISR_ERROR_CODE    13
ISR_ERROR_CODE    14
ISR_NO_ERROR_CODE 15
ISR_NO_ERROR_CODE 16
ISR_ERROR_CODE    17
ISR_NO_ERROR_CODE 18
ISR_NO_ERROR_CODE 19
ISR_NO_ERROR_CODE 20
ISR_NO_ERROR_CODE 21
ISR_NO_ERROR_CODE 22
ISR_NO_ERROR_CODE 23
ISR_NO_ERROR_CODE 24
ISR_NO_ERROR_CODE 25
ISR_NO_ERROR_CODE 26
ISR_NO_ERROR_CODE 27
ISR_NO_ERROR_CODE 28
ISR_ERROR_CODE    29
ISR_NO_ERROR_CODE 30
ISR_NO_ERROR_CODE    31


[EXTERN isr_handler]

isr_dispatch:
    pusha ; store the state

    mov ax, ds 
    push eax ; save the data segment descriptor 

    mov ax, 0x10 ; go back to kernel mode just in case
    mov ds, ax
    mov es, ax
    mov fs, ax 
    mov gs, ax 
    
    push esp
    call isr_handler
    add esp, 4

    pop eax ; go back to user mode or whatever 
    mov ds, ax 
    mov es, ax 
    mov fs, ax 
    mov gs, ax

    popa ; restore the state

    add esp, 8 ; pop the args (error and interrupt) off the stack
               ; stack grows downwards

    sti ; re enable interrupts
    iret ; return to normal execution

[GLOBAL loadIDT]

loadIDT:
    mov eax, [esp + 4] ; first arg (second is return addr)
    lidt [eax]
    sti
    ret 