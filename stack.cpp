#include<cstdio>
#include<cstdlib>
#include "stack.h"

using namespace std;

struct OPNDstack *CreateOPNDStack(int length)
{
    struct OPNDstack *opndstack = (OPNDstack *)malloc(sizeof(OPNDstack));
    if (!opndstack) return NULL;
    opndstack->stack = (int *)malloc(length * sizeof(int));
    opndstack->bottom = opndstack->top = 0;
    opndstack->length = length;
    return opndstack;
}

struct OPTRstack *CreateOPTRStack(int length)
{
    struct OPTRstack *optrstack = (OPTRstack *)malloc(sizeof(OPTRstack));
    if (!optrstack) return NULL;
    optrstack->stack = (char *)malloc(length * sizeof(char));
    optrstack->bottom = optrstack->top = 0;
    optrstack->length = length;
    return optrstack;
}

void Push(struct OPNDstack *opndstack, int item) //压入数据
{
    if((opndstack->top - opndstack->bottom) >= (opndstack->length - 1))
    {
        printf("ERROR! The stack is full!\n");
        return;
    }
    printf("将 %d 压入到数字栈!\n", item);
    opndstack->stack[opndstack->top++] = item;
}

void Push(struct OPTRstack *optrstack, char item)
{
    if((optrstack->top - optrstack->bottom) >= (optrstack->length - 1))
    {
        printf("ERROR! The stack is full!\n");
        return;
    }
    printf("将 %c 压入到操作符栈!\n", item);
    optrstack->stack[optrstack->top++] = item;
}

int GetTop(struct OPNDstack *opndstack)
{
    if(opndstack->top == opndstack->bottom)
    {
        printf("ERROR! The stack is empty!\n");
        return -1;
    }
    int temp = opndstack->top - 1;
    return opndstack->stack[temp];
}

char GetTop(struct OPTRstack *optrstack)
{
    if(optrstack->top == optrstack->bottom)
    {
        printf("ERROR! The stack is empty!\n");
        return '#';
    }
    int temp = optrstack->top - 1;
    return optrstack->stack[temp];
}

int Pop(struct OPNDstack *opndstack)
{
    if(opndstack->top == opndstack->bottom)
    {
        printf("ERROR! The stack is empty!\n");
        return -1;
    }
    int topData = opndstack->stack[--opndstack->top];
    printf("将 %d 从数字栈中弹出!\n", topData);
    return topData;
}

char Pop(struct OPTRstack *optrstack)
{
    if(optrstack->top == optrstack->bottom)
    {
        printf("ERROR! The stack is empty!\n");
        return '#';
    }
    char c = optrstack->stack[--optrstack->top];
    printf("将 %c 从操作符栈中弹出!\n", c);
    return c;
}