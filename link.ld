ENTRY(loader) /* Name of the entry point */

SECTIONS {
	. = 0x00100000;	/* Code location at 1 MB*/
	.text ALIGN (0x1000) : /* Align at 4 KB */
	{
		*(.multiboot)
		*(.text)	/* All text sections from all files */
	}
	.rodata ALIGN (0x1000) :
	{
		*(.rodata*)	/* All read-only data sections */
	}
	.data ALIGN (0x1000) :
	{
		*(.data)	/* All data sections */
	}
	.bss ALIGN (0x1000) :
	{
		*(COMMON)	/* All common sections */
		*(.bss)		/* All bss sections  */
	}
}
