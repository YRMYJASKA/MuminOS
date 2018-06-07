/* IDT.h
 * The IDT functions and other IDT related stuff
 */
#pragma once

#include "int_types.h"

uint64_t IDT[256];

struct IDT_entry {
    uint32_t entry_high;
    uint32_t entry_low;
} __attribute__((packed));

struct cpu_state {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;

    uint32_t esp;
} __attribute__((packed));

struct stack_state {
    uint32_t err_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed));

/* interrupt_handler:
 *
 * @param cpu
 * @param _stack
 * @param interrupt
 */
void interrupt_handler(struct cpu_state cpu, struct stack_state _stack, uint32_t interrupt);

/* load_idt:
 * Definition in 'IDT.asm'
 *
 * @param idt_ptr 	Pointer to the first element of the IDT
 */
void load_idt(uint64_t* idt_ptr);
