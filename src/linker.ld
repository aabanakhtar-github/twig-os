/* The bootloader will look at this image and start execution at the symbol
   designated as the entry point. */
ENTRY(_start)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* Recommended start offset for modern systems */
	. = 2M;

	/* First put the multiboot header, and the .text section */
	/* Align and block are just the recommendend settings for efficiency purposes, and general compatiblity */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
	
	/* Reserve 16 MB heap */
	.heap (NOLOAD) : ALIGN(8)
	{
		. = ALIGN(8);
		_KERNEL_HEAP_START = .;
		. = . + 0x01000000; /* 16 MB */
	}

	/* Reserve 128 KB RAM disk */
	.ramdisk (NOLOAD) : ALIGN(8)
	{
		. = ALIGN(8);
		_KERNEL_RAMDISK_START = .;
		. = . + 0x20000; /* 128 KB */
	}
}
