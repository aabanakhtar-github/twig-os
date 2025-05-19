; Declare the multiboot header to be compliant with GRUB
MBALIGN  equ 1 << 0 ; align the memory on page bounds
MEMINFO  equ 1 << 1 ; load the mmap_* stuff; allows you to query about the memory
MBFLAGS  equ MBALIGN | MEMINFO ; declare flags for the multiboot
MAGIC    equ 0x1BADBOO2 ; lets the bootloader find us
CHECKSUM equ -(MAGIC | FLAGS) ; proves we are multiboot

; declare multiboot header according to spec
section .multiboot
    align 4 ; make sure that everything is 4 bytes apart
    dd MAGIC
    dd FLAGS
    dd CHECKSUM


.start