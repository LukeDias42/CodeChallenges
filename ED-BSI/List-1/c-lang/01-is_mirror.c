#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

#define MAX_STACK 1024
#define MAX_STRING 1024
#define ULONG long unsigned int
#define INCORRECT_FORMAT " is not on the correct format.\n"
#define CORRECT_FORMAT " is on the correct format.\n"

ULONG str_len(char string[]);
bool verify_string(char string[], stack s);

int main()
{
    stack s = make_stack(MAX_STACK);
    if (s == NULL) {
        printf("Couldn't allocate stack.");
        return 1;
    }

    char str[MAX_STRING];
    scanf("%s", str);

    bool result = verify_string(str, s);
    printf("%s%s",str, result ? CORRECT_FORMAT : INCORRECT_FORMAT);

    return 0;
}

bool verify_string(char string[], stack s)
{
    ULONG len = str_len(string);
    if (len % 2 != 0){
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (string[i] != 'A' && string[i] != 'B') {
            return false;
        }
    }

    for (int i = len>>1; i < len; i++) {
        push(s, string[i]);
    }

    for (int i = 0; i < len>>1; i++) {
        if (string[i] != pop(s)) {
            return false;
        }
    }

    return true;
}

ULONG str_len(char string[])
{
    ULONG size = 0;
    while (string[size++] != '\0');
    return size-1;
}
