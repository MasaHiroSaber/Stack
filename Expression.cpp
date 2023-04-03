#include <cstdio>
#include <cstring>

using namespace std;

static char priority[5][6] = {
        {2, 2, 2, 2, 2, 0},
        {2, 1, 1, 2, 2, 1},
        {2, 1, 1, 2, 2, 1},
        {2, 1, 1, 1, 1, 1},
        {2, 1, 1, 1, 1, 1}
};

char Priori(char charInStack, char charOutOfStack)
{
    int indexInStack = 0, indexOutOfStack = 0;
    switch(charInStack)
    {
        case '(':
            indexInStack = 0;
            break;
        case '+':
            indexInStack = 1;
            break;
        case '-':
            indexInStack = 2;
            break;
        case '*':
            indexInStack = 3;
            break;
        case '/':
            indexInStack = 4;
            break;
    }
    switch(charOutOfStack)
    {
        case '(':
            indexOutOfStack = 0;
            break;
        case '+':
            indexOutOfStack = 1;
            break;
        case '-':
            indexOutOfStack = 2;
            break;
        case '*':
            indexOutOfStack = 3;
            break;
        case '/':
            indexOutOfStack = 4;
            break;
        case ')':
            indexOutOfStack = 5;
            break;
    }
    return priority[indexInStack][indexOutOfStack];
}

int Calculate2Number(int leftopnd, char optr, int rightopnd)
{
    switch(optr)
    {
        case '+':
            return leftopnd + rightopnd;
        case '-':
            return leftopnd - rightopnd;
        case '*':
            return leftopnd * rightopnd;
        case '/':
            return leftopnd / rightopnd;
        default:
            return -1;
    }
}

int CharToNumber(char *s)   //���ַ���ת��Ϊ����
{
    int length = strlen(s);
    int sum = 0;
    for(int i = 0; i < length; i++)
    {
        sum *= 10;  //ÿ�γ���10
        sum += (s[i] - 48); //���ַ�ת��Ϊ����, '0'��ASCII��Ϊ48, '1'��ASCII��Ϊ49, '2'��ASCII��Ϊ50, �Դ�����
    }
    return sum;
}