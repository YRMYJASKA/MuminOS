#pragma once

#include "string.h"
#include "vga_driver.h"

void execute_command(char* command)
{
    char args[16][64];
    int x = 0, z = 0;
    for (int i = 0; i < strlen(command); i++) {
        if (command[i] == ' ') {
            x++;
            z = 0;
        } else {
            args[x][z] = command[i];
            z++;
        }
    }
    if (strCmp(args[0], "help") == 0) {
        print_string("help      Displays this message\n");
        print_string("ping      Pong!\n");
        print_string("clear     Clears the terminal\n");
    } else if (strCmp(args[0], "ping") == 0) {
        print_string("Pong!\n");
    } else if (strCmp(args[0], "clear") == 0) {
        // TODO
    }
}
