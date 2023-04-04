#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "stack.h"
#include "expression.h"

void PrintoptrStack(struct OPTRstack *optrstack)
{
    if (optrstack->top == optrstack->bottom)
    {
        printf("当前运算符栈为空!\n");
        return;
    }

    printf("当前运算符栈:");
    for (int i = 0; i < optrstack->top - optrstack->bottom; i++)
    {
        printf(" %c |", optrstack->stack[i]);
    }
    printf("\b \n");

}

void PrintopndStack(struct OPNDstack *opndstack)
{
    //当opndstack->top == opndstack->bottom时,栈为空
    if (opndstack->top == opndstack->bottom)
    {
        printf("当前数字栈为空!\n");
        return;
    }
    printf("当前数字栈:");
    for (int i = 0; i < opndstack->top - opndstack->bottom; i++)
    {
        printf(" %d |", opndstack->stack[i]);
    }
    printf("\b \n");
}

int ComputeExpression(char *expression)     //计算表达式
{
    int length = strlen(expression);
    //创建两个栈opnd和optr
    OPNDstack *opndStack = CreateOPNDStack(length);
    OPTRstack *optrStack = CreateOPTRStack(length);
    //数据的记录
    int index = 0; //记录number的下标
    char *number = (char *) malloc(length * sizeof(char));    //记录数字
    if (!number) return 0;  //内存分配失败,返回0
    //运算符优先级
    int prori = 0;
    for (int i = 0; i < length; i++)
    {
        if (expression[i] >= '0' && expression[i] <= '9')
        {
            number[index++] = expression[i];    //记录数字
            continue;
        }
        //不是数据
        if (index != 0) //number中有数据
        {
            number[index] = '\0';   //添加结束符
            int temp = CharToNumber(number);    //将字符串转换为数字
            Push(opndStack, temp);  //将数字压入栈中
            PrintopndStack(opndStack);
        }
        //optr栈是空的
        if (optrStack->top == optrStack->bottom)
        {
            Push(optrStack, expression[i]); //将运算符压入栈中
            PrintoptrStack(optrStack);
            continue;   //原代码中没有continue,会多执行一次
        }
        do
        {
            char charinStack = GetTop(optrStack);   //获取栈顶运算符
            prori = Priori(charinStack, expression[i]); //获取优先级
            //左括号和右括号抵消
            if (prori == 0)
            {
                Pop(optrStack);
                PrintoptrStack(optrStack);
            }//弹出栈顶运算符
            else if (prori == 2)
            {//栈外的运算符优先级高于栈顶运算符优先级
                Push(optrStack, expression[i]); //将运算符压入栈中
                PrintoptrStack(optrStack);
            } else    //prori == 1,栈外的运算符优先级低于栈顶运算符优先级
            {//prori == 1
                char operater = Pop(optrStack); //弹出栈顶运算符
                int rightData = Pop(opndStack); //弹出栈顶数据
                int leftData = Pop(opndStack);  //弹出栈顶数据
                int result = Calculate2Number(leftData, operater, rightData);   //计算结果
                printf("计算:%d %c %d = %d\n", leftData, operater, rightData, result);
                Push(opndStack, result);    //将结果压入数字栈中
                PrintopndStack(opndStack);
                PrintoptrStack(optrStack);
            }
        } while (prori == 1);
        index = 0;
    }//end of for (int i = 0; i < length; i++)
    int result = Pop(opndStack);
    free(opndStack->stack); //释放内存
    free(optrStack->stack);
    free(opndStack);
    free(optrStack);
    free(number);
    return result;
}

int main()
{
    char express[256];
    express[0] = '(';
    printf("请输入一个表达式:");
    scanf_s("%s", &express[1], 254);
    size_t len = strlen(express);
    express[len] = ')'; //添加右括号
    express[len + 1] = '\0'; //添加结束符
    int result = ComputeExpression(express);
    printf("\n计算结果为:%d\n", result);
    return 0;
}


//3+3*(9-2*3)/3*(8-2*4)-9的计算过程

//将 ( 压入到操作符栈!
//当前运算符栈: (
//将 3 压入到数字栈!
//当前数字栈: 3
//将 + 压入到操作符栈!
//当前运算符栈: ( | +
//将 3 压入到数字栈!
//当前数字栈: 3 | 3
//将 * 压入到操作符栈!
//当前运算符栈: ( | + | *
//将 ( 压入到操作符栈!
//当前运算符栈: ( | + | * | (
//将 9 压入到数字栈!
//当前数字栈: 3 | 3 | 9
//将 - 压入到操作符栈!
//当前运算符栈: ( | + | * | ( | -
//将 2 压入到数字栈!
//当前数字栈: 3 | 3 | 9 | 2
//将 * 压入到操作符栈!
//当前运算符栈: ( | + | * | ( | - | *
//将 3 压入到数字栈!
//当前数字栈: 3 | 3 | 9 | 2 | 3
//将 * 从操作符栈中弹出!
//将 3 从数字栈中弹出!
//将 2 从数字栈中弹出!
//计算:2 * 3 = 6
//将 6 压入到数字栈!
//当前数字栈: 3 | 3 | 9 | 6
//当前运算符栈: ( | + | * | ( | -
//将 - 从操作符栈中弹出!
//将 6 从数字栈中弹出!
//将 9 从数字栈中弹出!
//计算:9 - 6 = 3
//将 3 压入到数字栈!
//当前数字栈: 3 | 3 | 3
//当前运算符栈: ( | + | * | (
//将 ( 从操作符栈中弹出!
//当前运算符栈: ( | + | *
//将 * 从操作符栈中弹出!
//将 3 从数字栈中弹出!
//将 3 从数字栈中弹出!
//计算:3 * 3 = 9
//将 9 压入到数字栈!
//当前数字栈: 3 | 9
//当前运算符栈: ( | +
//将 / 压入到操作符栈!
//当前运算符栈: ( | + | /
//将 3 压入到数字栈!
//当前数字栈: 3 | 9 | 3
//将 / 从操作符栈中弹出!
//将 3 从数字栈中弹出!
//将 9 从数字栈中弹出!
//计算:9 / 3 = 3
//将 3 压入到数字栈!
//当前数字栈: 3 | 3
//当前运算符栈: ( | +
//将 * 压入到操作符栈!
//当前运算符栈: ( | + | *
//将 ( 压入到操作符栈!
//当前运算符栈: ( | + | * | (
//将 8 压入到数字栈!
//当前数字栈: 3 | 3 | 8
//将 - 压入到操作符栈!
//当前运算符栈: ( | + | * | ( | -
//将 2 压入到数字栈!
//当前数字栈: 3 | 3 | 8 | 2
//将 * 压入到操作符栈!
//当前运算符栈: ( | + | * | ( | - | *
//将 4 压入到数字栈!
//当前数字栈: 3 | 3 | 8 | 2 | 4
//将 * 从操作符栈中弹出!
//将 4 从数字栈中弹出!
//将 2 从数字栈中弹出!
//计算:2 * 4 = 8
//将 8 压入到数字栈!
//当前数字栈: 3 | 3 | 8 | 8
//当前运算符栈: ( | + | * | ( | -
//将 - 从操作符栈中弹出!
//将 8 从数字栈中弹出!
//将 8 从数字栈中弹出!
//计算:8 - 8 = 0
//将 0 压入到数字栈!
//当前数字栈: 3 | 3 | 0
//当前运算符栈: ( | + | * | (
//将 ( 从操作符栈中弹出!
//当前运算符栈: ( | + | *
//将 * 从操作符栈中弹出!
//将 0 从数字栈中弹出!
//将 3 从数字栈中弹出!
//计算:3 * 0 = 0
//将 0 压入到数字栈!
//当前数字栈: 3 | 0
//当前运算符栈: ( | +
//将 + 从操作符栈中弹出!
//将 0 从数字栈中弹出!
//将 3 从数字栈中弹出!
//计算:3 + 0 = 3
//将 3 压入到数字栈!
//当前数字栈: 3
//当前运算符栈: (
//将 - 压入到操作符栈!
//当前运算符栈: ( | -
//将 9 压入到数字栈!
//当前数字栈: 3 | 9
//将 - 从操作符栈中弹出!
//将 9 从数字栈中弹出!
//将 3 从数字栈中弹出!
//计算:3 - 9 = -6
//将 -6 压入到数字栈!
//当前数字栈: -6
//当前运算符栈: (
//将 ( 从操作符栈中弹出!
//当前运算符栈为空!
//将 -6 从数字栈中弹出!
//
//计算结果为:-6

