/* This is another implementation of the third exercise. However in this iteration there is an array
 * of tops, each containing the current position of the substack. This is way easier to implement
 * and think about than the 2 substacks.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 5
#define STACKS 3

typedef struct stack {
    int stacks;
    int size;
    int *tops;
    long int *items;
} Stack;


Stack *make_stack(int capacity, int stacks);
void destroy_stack(Stack *s);
bool is_empty(const Stack *s, int stack_index);
bool is_full(const Stack *s, int stack_index);
void make_empty(Stack *s, int stack_index);
bool push(Stack *s, long int value, int stack_index);
long int peek(Stack *s, int stack_index);
long int pop(Stack *s, int stack_index);

int main()
{
    Stack *s = make_stack(STACK_SIZE, STACKS);
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
    push(s, 1, 2);
    push(s, 4, 2);
    push(s, 8, 2);
    push(s, 16, 2);
    push(s, 32, 2);

    for (int i = 0; i < s->stacks; i++){
        printf("Stack: %d\n", i);
        for (int j = 0; !is_empty(s, i); j++) {
            printf("   %d - Value: %d\n", j, pop(s, i));
        }
    }

    destroy_stack(s);
    return 0;
}

// This create a stack with "stacks" substacks, 
// each with a maximum of "capacity" elements
Stack *make_stack(int capacity, int stacks)
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s == NULL) {
        return NULL;
    }

    s->size = capacity;
    s->stacks = stacks;
    s->tops = (int *)malloc(sizeof(int)*stacks);
    for (int i = 0; i < stacks; i++) {
        s->tops[i] = -1;
    }
    s->items = (long int *)malloc(sizeof(long int)*capacity*stacks);

    return s;
}

// This frees the memory allocated for tops, items and the stack itself.
void destroy_stack(Stack *s)
{
    free(s->tops);
    free(s->items);
    free(s);
}

// This verifies if a substack exists and is empty.
bool is_empty(const Stack *s, int stack_index)
{
    if (stack_index >= s->stacks) {
        printf("The substack with index %d does not exist.", stack_index);
        exit(EXIT_FAILURE);
    }
    return s->tops[stack_index] < 0;
}

// This verifies if a substack exists and is full.
bool is_full(const Stack *s, int stack_index)
{
    if (stack_index >= s->stacks) {
        printf("The substack with index %d does not exist.", stack_index);
        exit(EXIT_FAILURE);
    }
    return s->tops[stack_index] >= s->size;
}

// If the substack exists, restarts its top.
void make_empty(Stack *s, int stack_index)
{
    if (stack_index >= s->stacks) {
        printf("The substack with index %d does not exist.", stack_index);
        exit(EXIT_FAILURE);
    }
    s->tops[stack_index] = -1;
}

// If the substack is not full, adds item to it.
// The positionn of the item inside the array is
// the top value of that substack + 1, plus the size of a substack * which position is the substack in.
// For instance, the substack 0 starts at 0, so it is just the top + 1;
// While the substack 1 of a list of substacks with size 5, starts at the index 5 * 1, so it is top + 1 + 5;
bool push(Stack *s, long int value, int stack_index)
{
    if (is_full(s, stack_index)) {
        return false;
    }

    s->items[++s->tops[stack_index] + (s-> size * stack_index)] = value;

    return true;
}

// If the substack is not empty, shows the value of its top.
// Follows the same idea of push, but does not change the value of top.
long int peek(Stack *s, int stack_index)
{
    if (is_empty(s, stack_index)) {
        printf("The stack %d is empty.\n", stack_index);
        exit(EXIT_FAILURE);
    }

    return s->items[s->tops[stack_index] + (s-> size * stack_index)];
}

// If the substack is not empty, shows the value of its top and removes it from the substack.
long int pop(Stack *s, int stack_index)
{
    if (is_empty(s, stack_index)) {
        printf("The stack %d is empty.\n", stack_index);
        exit(EXIT_FAILURE);
    }

    return s->items[s->tops[stack_index]-- + (s-> size * stack_index)];
}


