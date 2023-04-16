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
bool verify_string(char string[], stack s, int start, int end);

int main()
{
    stack s = make_stack(MAX_STACK);
    if (s == NULL) {
        printf("Couldn't allocate stack.");
        return 1;
    }

    char str[MAX_STRING];
    scanf("%s", str);

    int start = 0, i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'D') {
            bool result = verify_string(str, s, start, i-1);
            if (!result) { 
                printf("%s%s",str, INCORRECT_FORMAT);
                return 0;
            }
            start = i+1;
        }
    }
    bool finalResult = verify_string(str, s, start, i-1);
    printf("%s%s",str, finalResult ? CORRECT_FORMAT : INCORRECT_FORMAT);

    return 0;
}

bool verify_string(char string[], stack s, int start, int end)
{
    int len = end - start + 1;
    if (len % 2 != 0){
        return false;
    }
    int halfway = start+(len>>1);

    for (int i = start; i < end; i++) {
        if (string[i] != 'A' && string[i] != 'B') {
            return false;
        }
    }

    for (int i = halfway; i <= end; i++) {
        push(s, string[i]);
    }

    for (int i = start; i < halfway; i++) {
        if (string[i] != pop(s)) {
            return false;
        }
    }

    return true;
}
