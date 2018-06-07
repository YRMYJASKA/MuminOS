// kmain.c

#include "include/colors.h"
#include "include/version.h"
#include "include/vga_driver.h"
#include "include/string.h"

int kmain(void)
{
    vga_print("       //\n      (oo\\ \n      / ._) \n     J _=\\= \n     |   / \n3._.\' |_|_", 0, 0, WHITE | BLACK);
	vga_print(VERSION_STRING, 10, 6, WHITE | BLACK);
    while (1) {
        vga_refresh();
    }
}
