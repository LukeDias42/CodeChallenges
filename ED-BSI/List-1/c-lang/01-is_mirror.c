/* The challenge for this solution is to check wheter a string is of the format xCy, where y is the mirror of x.
 * Also, the sring must only consist of the characters 'A' and 'B'.
 * You should also only access a character each time while checking the string.
 * For instance, the string: "ABABBAABBABA" has x = "ABABBA" and y = "ABBABA". Since y is the mirror of x
 * the string is in the correct format.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

#define MAX_STACK 1024
#define MAX_STRING 1024
#define ULONG long unsigned int
#define INCORRECT_FORMAT " is NOT in the correct format.\n"
#define CORRECT_FORMAT " is in the correct format.\n"
#define IS_AB(c) (c == 'A' || c == 'B')

bool verify_string(char string[], Stack *s);

int main()
{
    // Tries to allocate space in memory for this stack.
    Stack *s = make_stack(MAX_STACK);
    if (s == NULL) {
        printf("Couldn't allocate stack.");
        return 1;
    }

    char str[MAX_STRING];
    scanf("%s", str);

    bool result = verify_string(str, s);
    printf("%s%s",str, result ? CORRECT_FORMAT : INCORRECT_FORMAT);

    destroy_stack(s);
    return 0;
}

// In C, strings always end with a '\0' character, so the size is from the first character up to '\0'
ULONG str_len(char string[])
{
    ULONG size = 0;
    while (string[size++] != '\0');
    return size-1;

}

// Verify if the string is in the proposed format xCy, where y is the mirror of x.
bool verify_string(char string[], Stack *s)
{
    ULONG len = str_len(string);
    // If length of the string is not an even value, then it cannot be on the format xCy.
    if (len % 2 != 0){
        return false;
    }

    // Starting from the half of the string, add char to the stack.
    for (int i = len>>1; i < len; i++) {
        push(s, string[i]);
    }

    // Verify if the current char on the string is equal to the popped character from the stack.
    // If they are not equal, then the string is not on the correct format.
    // Also, if they are equal, check if the current char is 'A' or 'B'
    // You don't need to check for the popped value, because you already know that it is equal to
    // the current char.
    for (int i = 0; i < len>>1; i++) {
        if (string[i] != pop(s) || !IS_AB(string[i])) {
            return false;
        }
    }

    return true;
}

