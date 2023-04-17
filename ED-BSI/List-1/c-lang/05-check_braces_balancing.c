/* This exercise's purpose is to verify if a string has balanced braces.
 * It is a pretty straightforward exercise. 
 * */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"

#define MAX_STACK_SIZE 1024
#define MAX_STRING_SIZE 1024
#define CORRECT_BALANCE "The string is correctly balanced.\n"
#define INCORRECT_BALANCE "The string is NOT correctly balanced.\n"

bool verify_string(char str[], Stack *stack);

int main()
{
    Stack *s = make_stack(MAX_STACK_SIZE);
    if (!s) {
        printf("Could not allocate memory to the stack.");
        return 0;
    }

    char str[MAX_STRING_SIZE];
    scanf("%s", str);

    printf("%s", verify_string(str, s) ? CORRECT_BALANCE : INCORRECT_BALANCE);

    destroy_stack(s);
    return 0;
}

// Returns the correct closing for a given character.
char matching_opening(char c)
{
    if (c == ')') return '(';
    if (c == ']') return '[';
    if (c == '}') return '{';
    return '\0';
}

// Uses the previously created stack to verify if a string has balanced braces.
// If a closing brace appears and the previous opening brace is missing or is not a match, the braces are not balanced.
bool verify_string(char str[], Stack *stack)
{
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (c == '(' || c == '[' || c == '{') {
            push(stack, c);
        }
        if (c == ')' || c == ']' || c == '}') {
            if (is_empty(stack) || pop(stack) != matching_opening(c)) {
                return false;
            }
        }
    }
    return is_empty(stack);
}
