; gdt.asm
; Functions for the Global Descriptor Table

; load_gdt - Load the GDT from the given paramater
; stack: [esp + 4] Pointer to the GDT struct
;		 [esp    ] The return address
global load_gdt
load_gdt:
	; Load the GDT 
	mov eax, [esp + 4]
	lgdt [eax]
	ret
