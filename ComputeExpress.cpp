#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "stack.h"
#include "expression.h"

void PrintoptrStack(struct OPTRstack *optrstack)
{
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
            continue;   //ԭ������û��continue,���ִ��һ��
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
                printf("����:%d %c %d = %d\n", leftData, operater, rightData, result);
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


//3+3*(9-2*3)/3*(8-2*4)-9�ļ������

//�� ( ѹ�뵽������ջ!
//��ǰ�����ջ: (
//�� 3 ѹ�뵽����ջ!
//��ǰ����ջ: 3
//�� + ѹ�뵽������ջ!
//��ǰ�����ջ: ( | +
//�� 3 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 3
//�� * ѹ�뵽������ջ!
//��ǰ�����ջ: ( | + | *
//�� ( ѹ�뵽������ջ!
//��ǰ�����ջ: ( | + | * | (
//�� 9 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 3 | 9
//�� - ѹ�뵽������ջ!
//��ǰ�����ջ: ( | + | * | ( | -
//�� 2 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 3 | 9 | 2
//�� * ѹ�뵽������ջ!
//��ǰ�����ջ: ( | + | * | ( | - | *
//�� 3 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 3 | 9 | 2 | 3
//�� * �Ӳ�����ջ�е���!
//�� 3 ������ջ�е���!
//�� 2 ������ջ�е���!
//����:2 * 3 = 6
//�� 6 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 3 | 9 | 6
//��ǰ�����ջ: ( | + | * | ( | -
//�� - �Ӳ�����ջ�е���!
//�� 6 ������ջ�е���!
//�� 9 ������ջ�е���!
//����:9 - 6 = 3
//�� 3 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 3 | 3
//��ǰ�����ջ: ( | + | * | (
//�� ( �Ӳ�����ջ�е���!
//��ǰ�����ջ: ( | + | *
//�� * �Ӳ�����ջ�е���!
//�� 3 ������ջ�е���!
//�� 3 ������ջ�е���!
//����:3 * 3 = 9
//�� 9 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 9
//��ǰ�����ջ: ( | +
//�� / ѹ�뵽������ջ!
//��ǰ�����ջ: ( | + | /
//�� 3 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 9 | 3
//�� / �Ӳ�����ջ�е���!
//�� 3 ������ջ�е���!
//�� 9 ������ջ�е���!
//����:9 / 3 = 3
//�� 3 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 3
//��ǰ�����ջ: ( | +
//�� * ѹ�뵽������ջ!
//��ǰ�����ջ: ( | + | *
//�� ( ѹ�뵽������ջ!
//��ǰ�����ջ: ( | + | * | (
//�� 8 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 3 | 8
//�� - ѹ�뵽������ջ!
//��ǰ�����ջ: ( | + | * | ( | -
//�� 2 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 3 | 8 | 2
//�� * ѹ�뵽������ջ!
//��ǰ�����ջ: ( | + | * | ( | - | *
//�� 4 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 3 | 8 | 2 | 4
//�� * �Ӳ�����ջ�е���!
//�� 4 ������ջ�е���!
//�� 2 ������ջ�е���!
//����:2 * 4 = 8
//�� 8 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 3 | 8 | 8
//��ǰ�����ջ: ( | + | * | ( | -
//�� - �Ӳ�����ջ�е���!
//�� 8 ������ջ�е���!
//�� 8 ������ջ�е���!
//����:8 - 8 = 0
//�� 0 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 3 | 0
//��ǰ�����ջ: ( | + | * | (
//�� ( �Ӳ�����ջ�е���!
//��ǰ�����ջ: ( | + | *
//�� * �Ӳ�����ջ�е���!
//�� 0 ������ջ�е���!
//�� 3 ������ջ�е���!
//����:3 * 0 = 0
//�� 0 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 0
//��ǰ�����ջ: ( | +
//�� + �Ӳ�����ջ�е���!
//�� 0 ������ջ�е���!
//�� 3 ������ջ�е���!
//����:3 + 0 = 3
//�� 3 ѹ�뵽����ջ!
//��ǰ����ջ: 3
//��ǰ�����ջ: (
//�� - ѹ�뵽������ջ!
//��ǰ�����ջ: ( | -
//�� 9 ѹ�뵽����ջ!
//��ǰ����ջ: 3 | 9
//�� - �Ӳ�����ջ�е���!
//�� 9 ������ջ�е���!
//�� 3 ������ջ�е���!
//����:3 - 9 = -6
//�� -6 ѹ�뵽����ջ!
//��ǰ����ջ: -6
//��ǰ�����ջ: (
//�� ( �Ӳ�����ջ�е���!
//��ǰ�����ջΪ��!
//�� -6 ������ջ�е���!
//
//������Ϊ:-6

