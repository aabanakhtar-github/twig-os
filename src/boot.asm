; Declare the multiboot header to be compliant with GRUB
MBALIGN  equ 1 << 0 ; align the memory on page bounds
MEMINFO  equ 1 << 1 ; load the mmap_* stuff; allows you to query about the memory
MBFLAGS  equ MBALIGN | MEMINFO ; declare flags for the multiboot
MAGIC    equ 0x1BADB002 ; lets the bootloader find us
CHECKSUM equ -(MAGIC + MBFLAGS) ; proves we are multiboot

; declare multiboot header according to spec
section .multiboot
    align 4 ; make sure that everything is 4 bytes apart
    dd MAGIC
    dd MBFLAGS
    dd CHECKSUM

; section where statically allocated variables that aren't init-ted are kept
section .bss
    align 16 ;x86 likes to align at 16 byte intervals
    stack_bottom:
    resb 16384 ; create a 16KiB stack
    stack_top:

section .text
    global _start:function (_start.end - _start)

; the program
_start:
  mov esp, stack_top ; setup the stack
  extern entryPoint ; load the function
  call entryPoint

  ; hang the system by clearing interrupts, and waiting for one to happen even though they never will
  cli
.hang:
    hlt
    jmp .hang
.end:
