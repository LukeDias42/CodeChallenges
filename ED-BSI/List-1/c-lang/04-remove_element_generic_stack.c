/* This exercise simply asks you to remove an element of a generic stack.
 * In C, there is nothing (that I know of) that can achieve the same that new Stack<T>() achieves,
 * however the void pointer allows you to point to any type, so you just have to add the same type to
 * the node.
 * Another thing, if the void* points to a struct that has a pointer inside (for instance), there is no
 * generic way to verify if they are the same. Therefore we have to create our own isEqual method.
 * The difference from this to Java is that in Java a class would be able to "know" how to compare,
 * however in C you have to implement the remove_element funtion with this implementation inside.
 * The cons of this is that you can't apply DRY as much, but the up side is SPEED, BABY!
 * PS.: This solution assumes that there is only one element with a certain value,
 * the change to verify multiple values is trivial.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "node_stack.h"

void remove_element(Stack *stack, void *element);
bool compare(void *a, void* b);
int *create_int(int num);

int main()
{
    Stack *stack = create_stack();
    for (int i = 0; i < 20; i++) {
        push(stack, create_int(i));
    }

    for (int i = 1; i < 20; i+=2) {
        remove_element(stack, create_int(i));
    }

    printf("Result:\n");
    while (!is_empty(stack)) {
        int *n = pop(stack);
        printf("  %d\n", *n);
    }

    destroy_stack(stack);
    return 0;
}

int *create_int(int num)
{
    int *x = (int *)malloc(sizeof(int));
    *x = num;
    return x;
}

void remove_element(Stack *stack, void *element)
{
    Stack *temp = create_stack();

    while (!is_empty(stack)) {
        void *popped = pop(stack);
        if (compare(popped, element)) {
            break;
        }
        push(temp, popped);
    }

    while (!is_empty(temp)) {
        push(stack, pop(temp));
    }

    destroy_stack(temp);
}

bool compare(void *a, void* b) 
{
    return *(int *)a == *(int *)b;
}
