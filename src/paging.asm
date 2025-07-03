[GLOBAL writeCR0]
writeCR0:
    mov eax, [esp + 4] ; first arg after return addr 
    mov cr0, eax
    ret

[GLOBAL readCR0]
readCR0:
    mov eax, cr0 ; standard return register
    ret

[GLOBAL writeCR3] 
writeCR3: 
    mov eax, [esp + 4]
    mov cr3, eax 
    ret 

[GLOBAL readCR3]
readCR3: 
    mov eax, cr3 
    ret