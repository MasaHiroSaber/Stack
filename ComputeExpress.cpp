#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "expression.h"

int ComputeExpression(char* expression)     //计算表达式
{
    int length = strlen(expression);
    //创建两个栈opnd和optr
    OPNDstack* opndStack = CreateOPNDStack(length);
    OPTRstack* optrStack = CreateOPTRStack(length);
    //数据的记录
    int index = 0; //记录number的下标
    char* number = (char*)malloc(length * sizeof(char));    //记录数字
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
        }
        //optr栈是空的
        if (optrStack->top == optrStack->bottom)
        {
            Push(optrStack, expression[i]); //将运算符压入栈中
        }
        do
        {
            char charinStack = GetTop(optrStack);   //获取栈顶运算符
            prori = Priori(charinStack, expression[i]); //获取优先级
            //左括号和右括号抵消
            if (prori == 0)
                Pop(optrStack); //弹出栈顶运算符
            else if (prori == 2)
            {//栈外的运算符优先级高于栈顶运算符优先级
                Push(optrStack, expression[i]); //将运算符压入栈中
            }
            else    //prori == 1,栈外的运算符优先级低于栈顶运算符优先级
            {//prori == 1
                char operater = Pop(optrStack); //弹出栈顶运算符
                int rightData = Pop(opndStack); //弹出栈顶数据
                int leftData = Pop(opndStack);  //弹出栈顶数据
                int result = Calculate2Number(leftData, operater, rightData);   //计算结果
                Push(opndStack, result);    //将结果压入数字栈中
            }
        }
        while (prori == 1);
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
    printf("Plz input an expression:");
    scanf_s("%s", &express[1], 254);
    size_t len = strlen(express);
    express[len] = ')'; //添加右括号
    express[len + 1] = '\0'; //添加结束符
    int result = ComputeExpression(express);
    printf("\nthe result is:%d\n", result);
    return 0;
}