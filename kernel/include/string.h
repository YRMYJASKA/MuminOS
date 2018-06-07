#pragma once

int strlen(char* text)
{
    int c = 0;
    while (*(text + c) != '\0') {
        c++;
    }
    return c;
}

