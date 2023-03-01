#include "stdio.h"
#include "stdlib.h"

typedef struct Stack1 {
    int *data;
    int Top;
    int Bottom;
    int Size;
} St;


St *CreateStack(int length) {
    St *p = (St *) malloc(sizeof(St));
    if (!p) return NULL;
    p->data = (int *) malloc(sizeof(int));
    //p->Top = -1;
    p->Top = 0;
    p->Bottom = 0;
    p->Size = length;
    return p;
}

int Push(St *stack, int value) {
    if (((stack->Top) - (stack->Bottom)) == (stack->Size) - 1)
        return 0;
    //stack -> data[++stack->Top] = value;
    stack->data[stack->Top++] = value;
    return 1;
}

int Pop(St *stack, int *value) {
    if (stack->Top == stack->Bottom) return 0;
    (*value) = stack->data[--stack->Top];
    return 1;
}

int GetTop(St *stack, int *value) {
    if (stack->Top == stack->Bottom) return 0;
    int index = stack->Top - 1;
    (*value) = stack->data[index];
    return 1
}
