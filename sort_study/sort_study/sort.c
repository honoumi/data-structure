#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

void _MgerSort(int* a, int begin, int end, int* temp)//��������ƱȽϺã���Ϊ�п���������п������ұ�
{
    if (begin >= end)
    {
        return;
    }
    int mid = (end + begin) / 2;
    //[begin,mid][mid+end]

    _MgerSort(a, begin, mid, temp);
    _MgerSort(a, mid + 1, end, temp);//����ϸ�֣�
    //�鲢�Ĺ��� ȡС��β��/����
    //����temp��ɹ鲢��Ȼ���ٿ���a�����У�
    int  begin1 = begin, end1 = mid;
    int  begin2 = mid + 1, end2 = end;

    int i = begin;
    while (begin <= end1 && begin2 <= end2)//��һ�������ͽ���
    {
        if (a[begin1] <= a[begin2])
        {
            temp[i++] = a[begin1++];
        }
        else
        {
            temp[i++] = a[begin2++];
        }
    }
    //��������ѭ������Ϊ��֪���ĸ��Ƚ��������԰���������һ��Ž�temp����
    while (begin1 <= end1)
    {
        temp[i++] = a[begin1++];
    }

    while (begin2 <= end2)
    {
        temp[i++] = a[begin1++];
    }
    //���������ǿ�����---�鲢�ǲ��־Ϳ����ǲ��ֻ�ȥ���������ǻ�ȥ���temp��������ֵҲ����ȥ
    memcpy(a + begin, temp + begin, (end - begin + 1) * sizeof(int));
    //memcpy���������ֽ�������Ҫ
}//һ��ƽ�ֱȽϺ�

void MergerSort(int* a, int n)
{
    int* temp = (int*)malloc(sizeof(int) * n);//������������еݹ�
    if (temp == NULL)
    {
        perror("malloc fail");
            return;
    }
    _MergeSort(a, 0, n - 1, temp);
    free(temp);
    temp = NULL;
}


void MergerSort2(int* a, int n)
{
    int* temp = (int*)malloc(sizeof(int) * n);//������������еݹ�
    if (temp == NULL)
    {
        perror("malloc fail");
            return;
    }
    int gap = 1;
    while(1)
    {
        //gap������ gap�����ݹ鲢��
        for (int j = 0; j < n; j += gap)
        {
            int  begin1 = j, end1 = j + gap - 1;
            int  begin2 = j + gap, end2 = j + 2 * gap - 1;


            if (end1 >= n)//��һ��Խ��
            {
                break;
            }
            if (begin2 >= n)//�ڶ���ȫ��Խ��
            {
                break;
            }
            if (end2 >= n)
            {
                //����end��
                end2 = n - 1;
            }
            int i = j;
            while (begin1 <= end1 && begin2 <= end2)//��һ�������ͽ���
            {

                if (a[begin1] <= a[begin2])
                {

                    temp[i++] = a[begin1++];
                }
                else
                {
                    temp[i++] = a[begin2++];
                }

            }
            while (begin1 <= end1)
            {
                temp[i++] = a[begin1++];
            }

            while (begin2 <= end2)
            {
                temp[i++] = a[begin1++];
            }

        
            memcpy(a + j, temp + j, (end2 - j + 1) * sizeof(int));
        }
        //�ݹ鵽����
        //memcpy(a,temp,(n)*sizeof(int));//���忽���Ļ���������Խ������ʱ����鷳���ܿ��ܻ��temp��������������ԭ���飡

        gap *= 2; 
    }
    free(temp);
    temp = NULL;
}
//gap==1 ���ڿ���һһ�飡