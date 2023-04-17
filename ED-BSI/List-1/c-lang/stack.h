#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct stack Stack;

Stack *make_stack(int capacity);
void destroy_stack(Stack *s);
bool is_empty(const Stack *s);
bool is_full(const Stack *s);
void make_empty(Stack *s);
bool push(Stack *s, long int value);
long int peek(Stack *s);
long int pop(Stack *s);

#endif
