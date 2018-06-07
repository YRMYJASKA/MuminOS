/* GDT.h
 * Global Descriptor Table functions and other utilities
 */
#pragma once

#include "int_types.h"

struct gdt_entry {
    uint32_t base;
    uint32_t limit;
    uint8_t type;
} __attribute__((packed));

static struct gdt_entry GDT[8];

/* load_gdt:
 * Load the GDT. Definition in 'gdt.asm'
 *
 * @param table  Pointer to the head of the GDT
 */
extern void load_gdt(uint8_t* table);

/* init_gdt:
 * Initialize the GDT with proper values
 */
static void init_gdt()
{
    GDT[0].base = 0;
    GDT[0].limit = 0;
    GDT[0].type = 0; // First entry to the GDT is null

    GDT[1].base = 0x04000000;
    GDT[1].limit = 0x03FFFFFF;
    GDT[1].type = 0x9A; // The code

    GDT[2].base = 0x08000000;
    GDT[2].limit = 0x03FFFFFF;
    GDT[2].type = 0x92; // Data
}
