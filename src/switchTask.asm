[BITS 32]
global switchTask
; bro what is this :sob: 

switchTask:
    cli
    pusha                   ; push all general-purpose registers
    pushf                   ; push EFLAGS

    mov eax, [esp + 36]     ; first argument: pointer to where to save context
                            ; esp + 36 because pusha(32) + pushf(4) = 36 bytes pushed

    mov [eax + 4], ebx      ; save ebx
    mov [eax + 8], ecx      ; save ecx
    mov [eax + 12], edx     ; save edx
    mov [eax + 16], esi     ; save esi
    mov [eax + 20], edi     ; save edi

    mov ebx, [esp + 28]     ; eax (saved by pusha) at esp+28
    mov ecx, [esp + 32]     ; eip (return address) at esp+32
    mov edx, [esp + 12]     ; esp at esp+12
    add edx, 4              ; remove return address from esp
    mov esi, [esp + 8]      ; ebp at esp+8
    mov edi, [esp + 4]      ; eflags (pushed by pushf) at esp+4

    mov [eax], ebx          ; save eax
    mov [eax + 24], edx     ; save esp
    mov [eax + 28], esi     ; save ebp
    mov [eax + 32], ecx     ; save eip
    mov [eax + 36], edi     ; save eflags

    mov eax, [esp + 40]     ; new task pointer argument (passed as second arg, esp+40)
    
    mov ebx, [eax + 4]      ; restore ebx
    mov ecx, [eax + 8]      ; restore ecx
    mov edx, [eax + 12]     ; restore edx
    mov esi, [eax + 16]     ; restore esi
    mov edi, [eax + 20]     ; restore edi
    mov ebp, [eax + 28]     ; restore ebp

    push eax                ; save pointer for later

    mov eax, [eax + 36]     ; restore eflags
    push eax
    popf                    ; load eflags

    pop eax                 ; restore pointer

    mov esp, [eax + 24]     ; restore esp

    push eax                ; save pointer again

    mov eax, [eax + 32]     ; restore eip
    xchg [esp], eax         ; put eip on stack as return address

    sti ; for safety reasons
    ret                     ; jump to new task
