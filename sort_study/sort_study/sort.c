#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

void _MgerSort(int* a, int begin, int end, int* temp)//用区间控制比较好，因为有可能是左边有可能是右边
{
    if (begin >= end)
    {
        return;
    }
    int mid = (end + begin) / 2;
    //[begin,mid][mid+end]

    _MgerSort(a, begin, mid, temp);
    _MgerSort(a, mid + 1, end, temp);//继续细分！
    //归并的过程 取小的尾插/升序
    //现在temp完成归并，然后再拷回a数组中！
    int  begin1 = begin, end1 = mid;
    int  begin2 = mid + 1, end2 = end;

    int i = begin;
    while (begin <= end1 && begin2 <= end2)//有一个结束就结束
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
    //后面两个循环是因为不知是哪个先结束了所以把两个都走一遍放进temp里面
    while (begin1 <= end1)
    {
        temp[i++] = a[begin1++];
    }

    while (begin2 <= end2)
    {
        temp[i++] = a[begin1++];
    }
    //接下来就是拷贝！---归并那部分就拷贝那部分回去！整个覆盖回去会把temp里面的随机值也拷过去
    memcpy(a + begin, temp + begin, (end - begin + 1) * sizeof(int));
    //memcpy拷贝的是字节数所以要
}//一般平分比较好

void MergerSort(int* a, int n)
{
    int* temp = (int*)malloc(sizeof(int) * n);//借用这数组进行递归
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
    int* temp = (int*)malloc(sizeof(int) * n);//借用这数组进行递归
    if (temp == NULL)
    {
        perror("malloc fail");
            return;
    }
    int gap = 1;
    while(1)
    {
        //gap个数据 gap个数据归并！
        for (int j = 0; j < n; j += gap)
        {
            int  begin1 = j, end1 = j + gap - 1;
            int  begin2 = j + gap, end2 = j + 2 * gap - 1;


            if (end1 >= n)//第一组越界
            {
                break;
            }
            if (begin2 >= n)//第二组全部越界
            {
                break;
            }
            if (end2 >= n)
            {
                //修正end；
                end2 = n - 1;
            }
            int i = j;
            while (begin1 <= end1 && begin2 <= end2)//有一个结束就结束
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
        //递归到哪里
        //memcpy(a,temp,(n)*sizeof(int));//整体拷贝的坏处当处理越界问题时候很麻烦，很可能会把temp里面的随机数拷回原数组！

        gap *= 2; 
    }
    free(temp);
    temp = NULL;
}
//gap==1 是在控制一一归！