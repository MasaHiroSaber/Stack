#ifndef _STACK_H
#define _STACK_H

struct OPNDstack
{
    int *stack;
    int bottom, top, length;
};

struct OPTRstack
{
    char *stack;
    int bottom, top, length;
};

struct OPNDstack *CreateOPNDStack(int length);
struct OPTRstack *CreateOPTRStack(int length);
void Push(struct OPNDstack *opndstack, int item);
void Push(struct OPTRstack *optrstack, char item);
int GetTop(struct OPNDstack *opndstack);
char GetTop(struct OPTRstack *optrstack);
int Pop(struct OPNDstack *opndstack);
char Pop(struct OPTRstack *optrstack);

#endif