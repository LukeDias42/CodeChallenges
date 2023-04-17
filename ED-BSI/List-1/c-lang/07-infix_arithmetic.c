/* This is a more complex exercise where you have to use stakcs in order to create a interpreter for a simple infix calculator.
 * The calculator only accepts the basic operators +, -, /, *, and it is completely paranthesized, which means that you
 * do not have to worry about precedences when dealing with the operators.
 * To do this, two stacks where created (this could be a great place to apply the substack of previous exercises),
 * the operands stack and operators stack. When a digit is found inside the array, a number is created and addded to the operands,
 * when a closing parenthesis is found it processes the last two numbers with the last operator, and it keeps doing that until
 * a closing parenthesis is found. 
 * More operations could easily be added, like ^ for pow, l for log, etc. 
 * Or by allowing for string operators instead of characters, which could be achieved by using the generic stack.
 * */

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
                long int b = pop(operands);
                long int a = pop(operands);
                long int result = operate(op, a, b);
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
