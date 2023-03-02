#include "stdio.h"
#include "stdlib.h"
#include "time.h"


typedef struct Stack1
{
    int *data;
    int Top;
    int Bottom;
    int Size;
} St;


St *CreateStack(int length)
{
    St *p = (St *) malloc(sizeof(St));
    if (!p) return NULL;
    p->data = (int *) malloc(sizeof(int));
    //p->Top = -1;
    p->Top = 0;
    p->Bottom = 0;
    p->Size = length;
    return p;
}

int Push(St *stack, int value)
{
    if (((stack->Top) - (stack->Bottom)) == (stack->Size) - 1)
        return 0;
    //stack -> data[++stack->Top] = value;
    stack->data[stack->Top++] = value;
    return 1;
}

int Pop(St *stack, int *value)
{
    if (stack->Top == stack->Bottom) return 0;
    (*value) = stack->data[--stack->Top];
    return 1;
}

int GetTop(St *stack, int *value)
{
    if (stack->Top == stack->Bottom) return 0;
    int index = stack->Top - 1;
    (*value) = stack->data[index];
    return 1;
}

void OutPut(St *stack)
{
    int length = (stack->Top - stack->Bottom);
    for (int i = 0; i < length; i++)
    {                 // 0 1 2 3 4 5
        int value = stack->data[length - i - 1];
        printf("\tPosition:%d Value:%d\n", length - i - 1, value);
    }
}

int main()
{
    srand(time(0));
#define LENGTH 10
    St *stack = CreateStack(LENGTH);
    for (auto i = 0; i < LENGTH; i++)
    {
        int op = rand() % 4;
        int value = 1 + rand() % 10;
        int *getvalue = NULL;
        switch (op)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            {
                int code = Push(stack, value);
                if (code == 0) printf("ERROR\n");
                else printf("SUCCESS PUSH\n");
                break;
            }

//            case 3: {
//                int code = Pop(stack, getvalue);
//                if (code == 0) printf("ERROR\n");
//                else printf("SUCCESS POP\n");
//            }

        }
        OutPut(stack);
    }
    free(stack);
    return 0;
}
