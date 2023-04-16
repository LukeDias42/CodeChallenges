#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

struct Stack {
    int maxSize;
    int top;
    int *items;
};

stack make_stack(int capacity)
{
    stack s = (stack)malloc(sizeof(struct Stack));
    if (s == NULL) {
        return NULL;
    }

    s->maxSize = capacity;
    s->top = -1;
    s->items = (int *)malloc(sizeof(int) * capacity);

    return s;
}

void destroy_stack(stack s)
{
    free(s);
}

int size(const stack s)
{
    return s->top+1;
}

bool is_empty(const stack s)
{
    return size(s)==0;
}

bool is_full(const stack s)
{
    return size(s)>=s->maxSize;
}

bool push(stack s, int value)
{
    if (is_full(s))
    {
        printf("The stack is full\n");
        return false;
    }

    s->items[++s->top] = value;
    return true;
}

int peek(stack s)
{
    if (is_empty(s)) {
        printf("The stack is empty\n");
        exit(EXIT_FAILURE);
    }

    return s->items[s->top];
}

int pop(stack s)
{
    if (is_empty(s)) {
        printf("The stack is empty\n");
        exit(EXIT_FAILURE);
    }

    return s->items[s->top--];
}

