// vga_driver.h
// The driver for the VGA screen

#pragma once

#include "int_types.h"
#include "string.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

uint8_t* VRAM = (uint8_t*)0xB8000;
int CURSOR_X = 0, CURSOR_Y = 0;

uint8_t VGA_BUFFER[2*VGA_HEIGHT][2*VGA_WIDTH];

// Initialize the screen buffer and other initial settings
extern void init_vga()
{
    for (int i = 0; i < 2*VGA_HEIGHT; i++) {
        for (int x = 0; x < 2*VGA_WIDTH; x++) {
            VGA_BUFFER[i][x] = 0x00;
        }
    }
}

// Print the buffer into the VRAM
extern void vga_refresh()
{
    uint8_t* offset = VRAM;
    for (int i = 0; i < 2*VGA_HEIGHT; i++) {
        for (int x = 0; x < 2*VGA_WIDTH; x += 2) {
            *offset++ = VGA_BUFFER[i][x];
            *offset++ = VGA_BUFFER[i][x + 1];
        }
    }
}

// print_string:
// print a string to a specifc position on the screen
extern void vga_print(char* text, int x, int y, uint8_t colour)
{
    for (int i = 0; i < strlen(text); i++) {
        if (*(text+i) == '\n') {
			y++;
			x = 0;
            continue;
        }
        VGA_BUFFER[y][x] = *(text+i);
        VGA_BUFFER[y][x + 1] = colour;
        x += 2;
    }
}

// Move the cursor
extern void vga_move_cursor(int x, int y)
{
    CURSOR_X = x;
    CURSOR_Y = y;
}
/*
extern init_screen()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3E0) & 0xE0) | cursor_end);
}*/
