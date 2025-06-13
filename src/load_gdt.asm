[GLOBAL loadGDT]
[BITS 32]

loadGDT:
    mov eax, [esp + 4] ; load the first argument (ptr to gdt)
    lgdt [eax]

    ; setup the selectors (they're all the same because they operate on the same memory?) 
    mov ax, 0x10 
    mov ds, ax 
    mov es, ax 
    mov fs, ax 
    mov gs, ax 
    mov ss, ax 

    ; setup the cs register
    ; 0x08 is for the code segment specifically 
    jmp 0x08:.flush_and_load_tss 

.flush_and_load_tss:
    ; setup the tss 
    mov ax, 0x28 ; gdt is 6th 
    ltr ax ; load based on selector

    ret ; used by the cs selector for setting (idk what this is bruh)