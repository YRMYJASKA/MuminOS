; Constants
MAGIC_NUM 	equ 0x1BADB002	; Magic number
FLAGS		equ 0x0			
CHECKSUM	equ -MAGIC_NUM

section .multiboot			; Create the multiboot header in order to boot
align 4
	dd MAGIC_NUM
	dd FLAGS
	dd CHECKSUM

section .bss	; Set up the stack
align 16
stack_bottom:
resb 16384
stack_top:

section .text
global _start:function (_start.end - _start)
_start: 
	mov esp, stack_top

	extern kmain
	call kmain

	cli
.hang: hlt
	jmp .hang
.end:
