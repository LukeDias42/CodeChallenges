/* This is an awful solution, it has a lot of type transformation (from int to string, to long and back to int),
 * Other than that, it is hard to understand and very slow.
 * There are way more straightfoward and faster solutions, such as manipulating the integer directly.
 * The challenge URL: https://leetcode.com/problems/reverse-integer 
 * */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

void revert_string(char buffer[]);

int reverse(int x)
{
    int sign = 1;
    if (x < 0) {
        sign = -1;
    }

    char *buffer;
    buffer = (char *)malloc(sizeof(char) * MAX_SIZE);
    sprintf(buffer, "%d", x);
    revert_string(buffer);

    char *remaining;
    long result = sign * strtol(buffer, &remaining, 10);

    if (result > 2147483647 || result < -2147483648)
        return 0;

    free(buffer);
    return result;
}


int string_len(char buffer[])
{
    int i;
    for (i = 0; buffer[i] != '\0'; i++)
        ;
    return i;
}

void revert_string(char *buffer)
{
    int len = string_len(buffer);
    for (int i = 0; i < len>>1; i++)
    {
        char temp =  buffer[i];
        buffer[i] = buffer[len-i-1];
        buffer[len-i-1] = temp;
    }
}

