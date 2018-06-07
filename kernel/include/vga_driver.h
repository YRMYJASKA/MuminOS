// vga_driver.h
#pragma once

#include "colors.h"
#include "int_types.h"
#include "io.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

/* framebuffer:
 * The location of the framebuffer in memory
 */
static uint16_t* framebuffer = (uint16_t*)0xB8000;

/* fb_cell:
 * A struct for each cell in the framebuffer
 */
struct fb_cell {
	uint8_t value;
	uint8_t colour;

} __attribute__((packed));

/* cursor_x and cursor_y
 * Store the current position of the cursor on the screen
 */
static uint32_t cursor_x = 0;
static uint32_t cursor_y = 0;

/* move_cursor:
 * Move the cursor to a location
 * 
 * @param pos 	location to move the cursor to 
 */
static void move_cursor(uint16_t pos)
{
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, pos & 0x00FF);
}

/* write_char:
 * Write a character to the framebuffer with given colours
 *
 * @param location 	Location of the to print
 * @param c 		Character to print
 * @param fg 		Foreground colour
 * @param bg 		Background colour
 */
static void write_char(uint32_t location, char c, uint8_t fg, uint8_t bg)
{
	struct fb_cell* cell = &framebuffer[location];

	cell->value = c;
	cell->colour = (bg) << 4 | (fg);
}

/* scroll_lines:
 * Move all the lines on the screen up by one
 */
static void scroll_lines(void)
{
	// Shift the lines
	for (int i = 0; i < VGA_HEIGHT; i++) {
		for (int x = 0; x < VGA_WIDTH - 1; x++) {
			framebuffer[i * VGA_WIDTH + x] = framebuffer[(i + 1) * VGA_WIDTH + x];
		}
	}

	// Clear the final row
	for (int i = 0; i < VGA_WIDTH; i++) {
		write_char((VGA_HEIGHT * VGA_WIDTH + i), ' ', BLACK, BLACK);
	}
}

/* init_fb:
 * Initialize the terminal (framebuffer) for use.
 */
static void init_fb(void)
{
	for (int i = 0; i < VGA_HEIGHT; i++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			write_char((i * VGA_WIDTH + x), ' ', BLACK, BLACK);
		}
	}
}

static void print_char(char c)
{
	if (c == '\n') {
		cursor_y++;
	}
	if (cursor_y >= VGA_HEIGHT) {
		scroll_lines();
		cursor_y--;
	}
	write_char((cursor_y * VGA_WIDTH + cursor_x), c, WHITE, BLACK);
	cursor_x++;
}

/* print_string:
 * Write a string to the terminal and update values accordingly
 *
 * @param str 	String to to write to terminal
 */
static void print_string(const char* str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (cursor_y >= VGA_HEIGHT) {
			scroll_lines();
			cursor_y--;
		}
		if (str[i] == '\n') {
			cursor_y++;
			cursor_x = 0;
			continue;
		}
		write_char((cursor_y * VGA_WIDTH + cursor_x), str[i], WHITE, BLACK);
		cursor_x++;
	}
}

/* write_string:
 * Write a string to a specific position on the terminal and update values accordingly 
 *
 * @param str 	String to to write to terminal
 */
static void write_string(const char* str, int x, int y)
{
	cursor_y = y;
	cursor_x = x;
	for (int i = 0; str[i] != '\0'; i++) {
		if (cursor_y >= VGA_HEIGHT) {
			scroll_lines();
			cursor_y--;
		}
		if (str[i] == '\n') {
			cursor_y++;
			cursor_x = 0;
			continue;
		}
		write_char((y * VGA_WIDTH + cursor_x), str[i], WHITE, BLACK);
		cursor_x++;
	}
}
