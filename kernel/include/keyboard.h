/* keyboard.h
 * The driver for the keyboard.
 */
#pragma once

#include "PIC.h"
#include "colors.h"
#include "int_types.h"
#include "io.h"
#include "vga_driver.h"

#define KBD_DATA_PORT 0x60

short shift_key_down = 0;

int counter = 1;

/*keymap_ansi:
 * This array contains the relevant characters for each keyboard scan code.
 * The array has twice as many keys there are on an ANSI keyboard because of shift letters.
 */
char keymap_ansi[166] = {
	0x1B, 0x1B, // Escape

	'1', '!',
	'2', '@',
	'3', '#',
	'4', '$',
	'5', '%',
	'6', '^',
	'7', '&',
	'8', '*',
	'9', '(',
	'0', ')',
	'-', '_',
	'=', '+',

	0x0E, 0x08, // Backspace
	0x0F, 0x09, // Tab

	'q', 'Q',
	'w', 'W',
	'e', 'E',
	'r', 'R',
	't', 'T',
	'y', 'Y',
	'u', 'U',
	'i', 'I',
	'o', 'O',
	'p', 'P',
	'[', '{',
	']', '}',

	'\n', '\n', // Enter
	0x00, 0x00, // Control key (29, 0x1D)

	'a', 'A',
	's', 'S',
	'd', 'D',
	'f', 'F',
	'g', 'G',
	'h', 'H',
	'j', 'J',
	'k', 'K',
	'l', 'L',
	';', ':',
	'\'', '\"',
	'`', '~',

	0x00, 0x00, // Left Shift key (42, 0x2A)

	'\\', '|',
	'z', 'Z',
	'x', 'X',
	'c', 'C',
	'v', 'V',
	'b', 'B',
	'n', 'N',
	'm', 'M',
	',', '<',
	'.', '>',
	'/', '?',

	0x00, 0x00, // Right Shift key (54, 0x36)
	0x2A, 0x00, // PRISC
	0x00, 0x00, // Alt key (56, 38)
	' ', ' ', // Space key
	0x00, 0x00, // Caps key

	0x3B, 0x54, // F1
	0x3C, 0x55, // F2
	0x3D, 0x56, // F3
	0x3E, 0x57, // F4
	0x3F, 0x58, // F5
	0x40, 0x59, // F6
	0x41, 0x5A, // F7
	0x42, 0x5B, // F8
	0x43, 0x5C, // F9
	0x44, 0x5D, // F10

	0x00, 0x00, // Num Lock
	0x00, 0x00, // Scroll Lock

	0x47, 0x37, // Home key
	0x48, 0x38, // UP key
	0x49, 0x39, // PGUP key
	0x00, '-',
	0x4B, 0x34, // Left key
	0x00, 0x35, // Center key
	0x4D, 0x36, // Right key
	0x00, '+',
	0x4F, 0x31, // End key
	0x50, 0x32, // Down key
	0x51, 0x33, // PGDN key
	0x52, 0x30, // Ins key
	0x53, 0x2E, // Del key
};

/* read_scan_code:
 * Read the scan code sent by the keyboard
 *
 * @return 		The scan code (Should be translated to ASCII)
 */
uint8_t read_scan_code(void) { return inb(KBD_DATA_PORT); }

/* get_char:
 * 
 * @return 	The received character from the keyboard or NULL if invalid key
 */
char get_char(void)
{
	uint8_t code = read_scan_code();

	// Check if the key pressed/released is shift
	if (code == 0x2A || code == 0x36) {
		shift_key_down = 1;
	} else if (code == 0xAA || code == 0xB6) {
		shift_key_down = 0;
	}

	char received_char = keymap_ansi[(code - 1) * 2 + shift_key_down];

	pic_ack(KBD_DATA_PORT);
	return received_char;
}

void init_kb()
{
	outb(KBD_DATA_PORT, 0xF3);
	outb(KBD_DATA_PORT, 0x04);
}
