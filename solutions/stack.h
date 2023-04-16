#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct Stack *stack;

stack make_stack(int capacity);
void destroy_stack(stack s);
bool is_empty(const stack s);
bool is_full(const stack s);
void make_emtpy(stack s);
bool push(stack s, int value);
int peek(stack s);
int pop(stack s);

#endif
