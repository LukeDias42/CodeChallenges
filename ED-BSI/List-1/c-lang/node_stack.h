#ifndef NODE_STACK_H
#define NODE_STACK_H

typedef struct node Node;
typedef struct stack Stack;

Stack *create_stack(void);
int is_empty(Stack *s);
void push(Stack *stack, void *data);
void *peek(Stack *stack);
void *pop(Stack *stack);
void destroy_stack(Stack *stack);

#endif
