#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

struct stack {
    int capacity;
    int top;
    long int *items;
};

Stack *make_stack(int capacity)
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s == NULL) {
        return NULL;
    }

    s->capacity = capacity;
    s->top = -1;
    s->items = (long int *)malloc(sizeof(long int) * capacity);

    return s;
}

void destroy_stack(Stack *s)
{
    free(s->items);
    free(s);
}

long int size(const Stack *s)
{
    return s->top+1;
}

bool is_empty(const Stack *s)
{
    return size(s)==0;
}

bool is_full(const Stack *s)
{
    return size(s)>=s->capacity;
}

bool push(Stack *s, long int value)
{
    if (is_full(s))
    {
        printf("The stack is full\n");
        return false;
    }

    s->items[++s->top] = value;
    return true;
}

long int peek(Stack *s)
{
    if (is_empty(s)) {
        printf("The stack is empty\n");
        exit(EXIT_FAILURE);
    }

    return s->items[s->top];
}

long int pop(Stack *s)
{
    if (is_empty(s)) {
        printf("The stack is empty\n");
        exit(EXIT_FAILURE);
    }

    return s->items[s->top--];
}

void make_empty(Stack *s)
{
    if (is_empty(s)) return;
    s->top = -1;
}
