/* PIC.h
 * Functions to handle the Programmable Interrupt Controller(PIC)
 *
 */
#pragma once

#include "int_types.h"
#include "io.h"

#define PIC1_PORT_A 0x20
#define PIC2_PORT_A 0xA0

#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT PIC2_START_INTERRUPT + 7

#define PIC_ACK 0x20

/* pic_ack:
 * Acknowledges an interrupt from either PIC 1 or 2
 *
 * @param num 	The number of the interrupt
 */
static void pic_ack(uint32_t num)
{
    if (num < PIC1_START_INTERRUPT || num > PIC2_END_INTERRUPT) {
        return;
    }

    if (num < PIC2_START_INTERRUPT) {
        outb(PIC1_PORT_A, PIC_ACK);
    } else {
        outb(PIC2_PORT_A, PIC_ACK);
    }
}
