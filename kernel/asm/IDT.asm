%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push dword 0
	push dword %1
	jmp common_interrupt_handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push dword %1
	jmp common_interrupt_handler
%endmacro

common_interrupt_handler:
	; Save registers
	push eax
	push ebx
	push ecx
	push edx
	push ebp
	push esi
	push edi
	
	extern interrupt_handler

	; Pop registers
	pop edi
	pop esi
	pop ebp
	pop edx
	pop ecx
	pop ebx
	pop eax
	
	add esp, 8
	
	; Return
	iret 

; load_idt - Loads the interrupt descriptor table (IDT)
; stack: [esp + 4] The address of the first entry in the IDT
; 		 [esp    ] Return address
global load_idt
load_idt:
	mov eax, [esp+4]
	lidt [eax]
	ret

no_error_code_interrupt_handler 0
error_code_interrupt_handler 1
no_error_code_interrupt_handler 2
no_error_code_interrupt_handler 3
no_error_code_interrupt_handler 4
no_error_code_interrupt_handler 5
no_error_code_interrupt_handler 6
error_code_interrupt_handler 7
; TODO

