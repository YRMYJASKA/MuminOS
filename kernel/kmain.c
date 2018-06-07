// kmain.c

#include "include/GDT.h"
#include "include/IDT.h"
#include "include/colors.h"
#include "include/int_types.h"
#include "include/io.h"
#include "include/keyboard.h"
#include "include/string.h"
#include "include/version.h"
#include "include/vga_driver.h"

int kmain(void)
{
	print_string("       //\n      (oo\\ \n      / ._) \n     J _=\\= \n     |   / \n3._.\' |_|_  MuminOS v");
	print_string(VERSION_STRING);
	print_string("\n\n");

	init_gdt();
	load_idt((uint64_t*)IDT);

	init_kb();

	char lastkey = 0;
	// Enter the loop
	while (1) {
		char keypress = get_char();
		if (keypress == '\n' && lastkey != '\n') { // Enter was pressed
			print_string("\n");
		}
		if (keypress < 32 || keypress > 126 || keypress == lastkey) {
			// Nothing for now
		} else {
			print_char(keypress);
		}
		lastkey = keypress;
		move_cursor(cursor_y * VGA_WIDTH + cursor_x);
	}
}
