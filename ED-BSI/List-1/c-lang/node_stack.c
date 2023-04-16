#include <stdio.h>
#include <stdlib.h>
#include "node_stack.h"

struct node {
    void *data;
    Node *next;
};

struct stack{
    Node *top;
};

Stack *create_stack(void)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack) return NULL;

    stack->top = NULL;
    return stack;
}

int is_empty(Stack *s)
{
    return !s->top;
}

void push(Stack *stack, void *data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = stack->top;
    stack->top = node;
}

void *peek(Stack *stack)
{
    if (is_empty(stack)) {
        printf("Stack is empty.");
        return NULL;
    }

    return stack->top->data;
}

void *pop(Stack *stack)
{
    if (is_empty(stack)) {
        printf("Stack is empty.");
        return NULL;
    }
    Node *temp = stack->top;
    void *data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

void destroy_stack(Stack *stack)
{
    while (!is_empty(stack)) {
        pop(stack);
    }
    free(stack);
}

