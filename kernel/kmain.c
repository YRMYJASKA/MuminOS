// kmain.c

#include "include/GDT.h"
#include "include/IDT.h"
#include "include/colors.h"
#include "include/commands.h"
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
    char buffer[74];
    int i = 0;
    // Enter the loop
    while (1) {
        write_string("BISh> ", 0, cursor_y);
        char keypress = get_char();
        if (keypress == '\n' && lastkey != '\n') { // Enter was pressed
            print_string("\n");
            buffer[i] = ' ';
            execute_command(buffer);
            for (int x = 0; x < 74; x++) {
                buffer[x] = ' ';
            }
            i = 0;
            lastkey = keypress;
        } else if (keypress < 32 || keypress > 126 || keypress == lastkey) {
            if ((keypress == 0x0E || keypress == 0x08) && i > 0) {
                buffer[i] = ' ';
                i--;
				cursor_x--;
                write_string(buffer, 7, cursor_y);
                move_cursor(cursor_y * VGA_WIDTH + cursor_x);
            }
        } else {
            if (i < 74) {
                buffer[i] = keypress;
                i++;
            }
            write_string(buffer, 7, cursor_y);
            move_cursor(cursor_y * VGA_WIDTH + cursor_x);
        }
        lastkey = keypress;
    }
}
