#pragma once

int strlen(char* text)
{
    int c = 0;
    while (*(text + c) != '\0') {
        c++;
    }
    return c;
}
int strCmp(char string1[], char string2[])
{
    for (int i = 0;; i++) {
        if (string1[i] != string2[i]) {
            return string1[i] < string2[i] ? -1 : 1;
        }

        if (string1[i] == '\0') {
            return 0;
        }
    }
}
