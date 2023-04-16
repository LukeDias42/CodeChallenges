/* In this exercise you have to create an stack that works as two stacks.
 * I don't see the point of this exercise, in practice you can simply create another instance of the
 * stack without this complexity. My solution is to use the same array, but each half of it is a stack. 
 * A good thing about this solution is that it is easily scalable to many instances of a stack inside one stack.
 * Instead of having top 1 and top 2, you would have an array tops, each containing the current top.
 * Each would have the same capacity, so it would be easy to verify if it is empty or full.
 * For a more generic implementation, see the file 3-01-multi_stack.c.
 * PS. It is not a good practice to have the typedef as a pointer, since it can become confusing.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STACK 5

struct Stack {
    int max_size;
    int top1;
    int top2;
    int *items;
};

typedef struct Stack *stack;

stack make_stack(int capacity);
void destroy_stack(stack s);
bool is_empty(const stack s, int stack_index);
bool is_full(const stack s, int stack_index);
void make_empty(stack s, int stack_index);
bool push(stack s, int value, int stack_index);
int peek(stack s, int stack_index);
int pop(stack s, int stack_index);

int main()
{
    stack s = make_stack(MAX_STACK);
    if (s == NULL) {
        printf("Couldn't allocate stack.\n");
        return 0;
    }
    push(s, 10, 0);
    push(s, 200, 0);
    push(s, 3000, 0);
    push(s, 40000, 0);
    push(s, 50000, 0);
    push(s, 60, 1);
    push(s, 700, 1);
    push(s, 8000, 1);
    push(s, 90000, 1);
    push(s, 100000, 1);

    for (int i = 0; i < MAX_STACK; i++){
        printf("INDEX: %d\n", i);
        printf("stack: 0, value: %d\n", pop(s, 0));
        printf("stack: 1, value: %d\n", pop(s, 1));
    }

    destroy_stack(s);
    return 0;
}

stack make_stack(int capacity)
{
    capacity <<= 1;

    stack s = (stack)malloc(sizeof(struct Stack));
    if (s == NULL) {
        return NULL;
    }
    s->max_size = capacity;
    s->top1 = -1;
    s->top2 = -1;
    s->items = (int *)malloc(sizeof(int)*capacity);

    return s;
}

void destroy_stack(stack s)
{
    free(s->items);
    free(s);
}

bool is_empty(const stack s, int stack_index)
{
    int current_top = stack_index == 0 ? s->top1 : s->top2;
    return (current_top + 1) <= 0;
}

bool is_full(const stack s, int stack_index)
{
    int current_top = stack_index == 0 ? s->top1 + 1 : s->top2 + 1;
    return current_top >= (s->max_size >> 1);
}

void make_empty(stack s, int stack_index)
{
    if (stack_index == 0) {
        s->top1 = -1;
    }
    else {
        s->top2 = - 1;
    }
}

bool push(stack s, int value, int stack_index)
{
    if (is_full(s, stack_index)) {
        return false;
    }

    if (stack_index == 0) {
        s->items[++s->top1] = value;
    }
    else {
        s->items[(++s->top2) + (s->max_size>>1)] = value;
    }

    return true;
}

int peek(stack s, int stack_index)
{
    if (is_empty(s, stack_index)) {
        printf("The stack %d is empty.\n", stack_index);
        exit(EXIT_FAILURE);
    }

    if (stack_index == 0) {
        return s->items[s->top1];
    }
    else {
        return s->items[(s->top2) + (s->max_size>>1)];
    }
}

int pop(stack s, int stack_index)
{
    if (is_empty(s, stack_index)) {
        printf("The stack %d is empty.\n", stack_index);
        exit(EXIT_FAILURE);
    }

    if (stack_index == 0) {
        return s->items[s->top1--];
    }
    else {
        return s->items[(s->top2--) + (s->max_size>>1)];
    }
}


