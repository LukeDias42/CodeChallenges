#include <stdio.h>
#include "stack.h"

#define STACK_CAPACITY 1024
#define MAX_STRING_SIZE 1024

void revert_words(char str[], Stack *stack);
int get_line(char str[], int limit);

int main()
{
    Stack *stack = make_stack(STACK_CAPACITY);
    if (!stack) {
        printf("Couldn't allocate memory for the stack.\n");
        return 0;
    }

    char str[MAX_STRING_SIZE];

    if (get_line(str, MAX_STRING_SIZE) <= 0) {
        printf("Empty string.\n");
        destroy_stack(stack);
        return 0;
    }

    revert_words(str, stack);
    printf("%s\n", str);

    destroy_stack(stack);
    return 0;
}

// Function that gets a string until a new line is found.
int get_line(char str[], int limit)
{
    int c, i = 0;
    while (i < limit && (c = getchar()) != '\n' && c != EOF) {
        str[i++] = c;
    }

    str[i] = '\0';
    return i;
}

// The revert word implementation
// This implementation changes the string sent as parameter,
// thus this is not a pure function. To make it so, create a new string with the 
// same size as the original one and use the same method, but when popping, pop it
// into the new string.
// Or simply pass a copy as param.
void revert_words(char str[], Stack *stack)
{
    int next_word_start = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        // if not space, add character to stack
        if (str[i] != ' '){  
            push(stack, str[i]);
        }
        // if space, put characters from stack back into the string (reversed) 
        // and then the space itself
        else {
            while (!is_empty(stack)) {
                str[next_word_start++] = pop(stack);
            }
            str[next_word_start++] = ' ';
        }
    }

    // At last, add whatever was at the end of the string (after all spaces) back into the string
    while (!is_empty(stack)) {
        str[next_word_start++] = pop(stack);
    }
}
