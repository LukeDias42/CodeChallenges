/* This exercise uses the principle of the last exercise and then expand on it.
 * In this one, the string must be on the format a D b D c D ... D z, where a, b, c, ..., z are representing
 * substrings that are on the format xCy, where y is the mirror of x. Each substring is separated by a D character.
 * Example of string that would work with that description: "AADABAABADABABBAABBABA",
 * This would be equivalent to the array ["AA", "ABAABA", "ABABBAABBABA"], each of these elements
 * must be on the xCy format. Since they are, the string is on the correct format.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

#define MAX_STACK 1024
#define MAX_STRING 1024
#define ULONG long unsigned int
#define INCORRECT_FORMAT " is not in the correct format.\n"
#define CORRECT_FORMAT " is in the correct format.\n"
#define IS_AB(c) (c == 'A' || c == 'B')

ULONG str_len(char string[]);
bool verify_string(char string[], Stack *s, int start, int end);

int main()
{
    Stack *s = make_stack(MAX_STACK);
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
                // If any of the substrings are incorrect, then the whole string is incorrect.
                printf("%s%s",str, INCORRECT_FORMAT);
                destroy_stack(s);
                return 0;
            }
            // The next start index starts after the 'D' character;
            start = i+1;
        }
    }

    // The final substring is not followed by a 'D' character on the specified format, 
    // therefore a last check must be made.
    bool finalResult = verify_string(str, s, start, i-1);
    printf("%s%s",str, finalResult ? CORRECT_FORMAT : INCORRECT_FORMAT);

    destroy_stack(s);
    return 0;
}

// Updated verify string to receive the start and end of the substring that is being verified.
// This version would also work on the previous exercise, where start = 0 and end = len - 1;
bool verify_string(char string[], Stack *s, int start, int end)
{
    // The length of the substring is the distance from the start character to the end character
    // of that substring.
    int len = end - start + 1;
    if (len % 2 != 0){
        return false;
    }

    // The middle of the substring is the start plus half of the distance to the end character.
    int mid = start+(len>>1);
    if (!is_empty(s)) {
        make_empty(s);
    }

    for (int i = mid; i <= end; i++) {
        push(s, string[i]);
    }

    for (int i = start; i < mid; i++) {
        char popped = pop(s);
        if (string[i] != popped || !IS_AB(string[i])) {
            return false;
        }
    }

    return true;
}

