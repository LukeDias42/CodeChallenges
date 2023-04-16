#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct stack Stack;

Stack *make_stack(int capacity);
void destroy_stack(Stack *s);
bool is_empty(const Stack *s);
bool is_full(const Stack *s);
void make_empty(Stack *s);
bool push(Stack *s, int value);
int peek(Stack *s);
int pop(Stack *s);

#endif
