#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"


#define STACK_SIZE 1024
#define STRING_SIZE 1024

long int evaluate_expression(char expression[], Stack *operators, Stack *operands);
int get_line(char str[], int limit);

int main()
{
    Stack *operators = make_stack(STACK_SIZE);
    Stack *operands = make_stack(STACK_SIZE);
    if (!operators || !operands) {
        printf("Couldn't allocate memory to the stacks.\n");
        return 0;
    }

    char str[STRING_SIZE];
    if (get_line(str, STRING_SIZE) <= 0) {
        printf("Empty expression.\n");
        destroy_stack(operators);
        destroy_stack(operands);
        return 0;
    }

    long int result = evaluate_expression(str, operators, operands);
    printf("The total value of the expression is: %ld\n", result);

    destroy_stack(operators);
    destroy_stack(operands);
    return 0;
}

int get_line(char str[], int limit)
{
    int c, i = 0;
    while (i < limit && (c = getchar()) != '\n' && c != EOF) {
        str[i++] = c;
    }

    str[i] = '\0';
    return i;
}

int to_int(char c)
{
    return c - '0';
}

bool is_operator(char c)
{
    return c == '+' || c == '-' || c == '/' || c == '*';
}

long int operate(char operator, int a, int b) {
    switch (operator) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

long int evaluate_expression(char expression[], Stack *operators, Stack *operands)
{
    long int num = 0;
    for (int i = 0; expression[i] != '\0'; i++) {
        char c = expression[i];
        if (isdigit(c)) {
            num = to_int(c);
            while (isdigit(c = expression[++i])) {
                num = num * 10 + to_int(c);
            }
            push(operands, num);
            i--;
        }
        else if (is_operator(c) || c == '(') {
            push(operators, c);
        }
        else if (c == ')') {
            char op = pop(operators);
            while (op != '(') {
                long b = pop(operands);
                long a = pop(operands);
                long result = operate(op, a, b);
                push(operands, result);
                op = pop(operators);
            }
        }
        else if (c != ' '){
            printf("ERROR: Unkown operator \"%c\"\n", c);
            exit(EXIT_FAILURE);
        }
    }

    return pop(operands);
}
