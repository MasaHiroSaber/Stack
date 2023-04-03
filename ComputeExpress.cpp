#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "expression.h"

void PrintoptrStack(struct OPTRstack *optrstack)
{
    //��optrstack->top == optrstack->bottomʱ,ջΪ��
    if (optrstack->top == optrstack->bottom)
    {
        printf("��ǰ�����ջΪ��!\n");
        return;
    }

    printf("��ǰ�����ջ:");
    for (int i = 0; i < optrstack->top - optrstack->bottom; i++)
    {
        printf(" %c |", optrstack->stack[i]);
    }
    printf("\b \n");

}

void PrintopndStack(struct OPNDstack *opndstack)
{
    //��opndstack->top == opndstack->bottomʱ,ջΪ��
    if (opndstack->top == opndstack->bottom)
    {
        printf("��ǰ����ջΪ��!\n");
        return;
    }
    printf("��ǰ����ջ:");
    for (int i = 0; i < opndstack->top - opndstack->bottom; i++)
    {
        printf(" %d |", opndstack->stack[i]);
    }
    printf("\b \n");
}

int ComputeExpression(char *expression)     //������ʽ
{
    int length = strlen(expression);
    //��������ջopnd��optr
    OPNDstack *opndStack = CreateOPNDStack(length);
    OPTRstack *optrStack = CreateOPTRStack(length);
    //���ݵļ�¼
    int index = 0; //��¼number���±�
    char *number = (char *) malloc(length * sizeof(char));    //��¼����
    if (!number) return 0;  //�ڴ����ʧ��,����0
    //��������ȼ�
    int prori = 0;
    for (int i = 0; i < length; i++)
    {
        if (expression[i] >= '0' && expression[i] <= '9')
        {
            number[index++] = expression[i];    //��¼����
            continue;
        }
        //��������
        if (index != 0) //number��������
        {
            number[index] = '\0';   //��ӽ�����
            int temp = CharToNumber(number);    //���ַ���ת��Ϊ����
            Push(opndStack, temp);  //������ѹ��ջ��
            PrintopndStack(opndStack);
        }
        //optrջ�ǿյ�
        if (optrStack->top == optrStack->bottom)
        {
            Push(optrStack, expression[i]); //�������ѹ��ջ��
            PrintoptrStack(optrStack);
            continue;
        }
        do
        {
            char charinStack = GetTop(optrStack);   //��ȡջ�������
            prori = Priori(charinStack, expression[i]); //��ȡ���ȼ�
            //�����ź������ŵ���
            if (prori == 0)
            {
                Pop(optrStack);
                PrintoptrStack(optrStack);
            }//����ջ�������
            else if (prori == 2)
            {//ջ�����������ȼ�����ջ����������ȼ�
                Push(optrStack, expression[i]); //�������ѹ��ջ��
                PrintoptrStack(optrStack);
            } else    //prori == 1,ջ�����������ȼ�����ջ����������ȼ�
            {//prori == 1
                char operater = Pop(optrStack); //����ջ�������
                int rightData = Pop(opndStack); //����ջ������
                int leftData = Pop(opndStack);  //����ջ������
                int result = Calculate2Number(leftData, operater, rightData);   //������
                printf("����:%d %c %d = %d\n", rightData, operater, leftData, result);
                Push(opndStack, result);    //�����ѹ������ջ��
                PrintopndStack(opndStack);
                PrintoptrStack(optrStack);
            }
        } while (prori == 1);
        index = 0;
    }//end of for (int i = 0; i < length; i++)
    int result = Pop(opndStack);
    free(opndStack->stack); //�ͷ��ڴ�
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
    printf("������һ�����ʽ:");
    scanf_s("%s", &express[1], 254);
    size_t len = strlen(express);
    express[len] = ')'; //���������
    express[len + 1] = '\0'; //��ӽ�����
    int result = ComputeExpression(express);
    printf("\n������Ϊ:%d\n", result);
    return 0;
}