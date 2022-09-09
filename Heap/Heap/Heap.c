#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int	HPDateType;

typedef struct Heap
{
	HPDateType* a;//����һ������
	int size;//��¼λ��
	int capacity;//��¼�ݻ�
}HP;//��Ȼ��˳���ͽṹһ�������ǲ�����ʽ�ǲ�ͬ�ģ�


void HeapPrint(HP* php)
{
	for (int i = 0; i < php->size; i++)
	{
		printf("%d ", php->a[i]);
	}
	printf("\n");
}

void swap(HPDateType* x,HPDateType* y)
{
	HPDateType temp = *x;
	*x = *y;
	*y = temp;
}
void HeapIint(HP* php)
{
	assert(php);
	php->a = NULL;
	php->capacity = 0;
	php->size = 0;
}

void HeapDestroy(HP* php)
{
	php->capacity = 0;
	php->size = 0;
	free(php->a);
	php->a = NULL;
}


void AdJustUp(HPDateType* a, int child)//childָ���Ǻ��ӵ�λ�ã� ���� = ������-1��/2��//��ʱ�Ǵ��
{
	int parent = (child - 1) / 2;
	while (child > 0)//parent >=0 ���������������,
	{
		if (a[child] < a[parent])//> �Ǵ�� ��< ��С��
		{
			swap(&a[child], &a[parent]);
			child = parent;//���ױ亢��
			parent = (child - 1 / 2);//�µĺ��������ĸ��ף�//��parent = 0ʱ�򣬣�0-1��/2 == 0���������һ�Σ�
		}
		else
		{
			break;
		}
		
 	}
}

//void AdJustDown(HPDateType* a,)
void HeapPush(HP* php,HPDateType x)//�����걣�ֶ�
{
	assert(php);
	if (php->size == php->capacity)
	{
		int NewCapacity = php->capacity == 0 ? 4 : php->capacity * 2;
		HPDateType* temp = (HPDateType*)realloc(php->a, sizeof(HPDateType)*NewCapacity);
		if (temp == NULL)
		{
			perror("malloc fail");
			return;
		}
		php->a = temp;
		php->capacity = NewCapacity;
	}
	php->a[php->size++] = x;//��size�����룬Ȼ��������ϵ����㷨
	AdJustUp(php->a, php->size - 1);

}//ʹ�����ϵ����㷨


void HeapCreat_Up(HP* php,int size,HPDateType* a)//�������ϵ����Ľ���Ч�ʵ������µ�����	
{
	for (int i = 0; i < size; i++)
	{
		HeapPush(php,a[i]);
	}
}

bool Heapempty(HP* php)
{
	return php->size == 0 ? true : false;
}

void AdjustDown(HPDateType* a, int parent,int size)
{
	int minchild = parent * 2 + 1;

	while (minchild <size)
	{
		//�ҳ�С���Ǹ�����//����С�ѵ��㷨����ѵ�Ҫ�ĳ��������Ǹ�����
		if (minchild + 1 < size && a[minchild] > a[minchild + 1])
			minchild++;
		if (a[minchild] < a[parent])//��ѵĻ�����ҲҪ�ģ�
		{
			swap(&a[minchild], &a[parent]);
			parent = minchild;
			minchild = parent * 2 + 1;
		}
		else
		{
			break;
		}

	}

}
void HeapPop(HP* php)//ɾ���Ѷ���Ԫ�ص��������������Ҵδ����С
{
	assert(php);
	assert(!Heapempty(php));
	swap(&php->a[0], &php->a[php->size - 1]);
	php->size--;
	AdjustDown(php->a, 0, php->size);

}//˼·���Ȱ�������ķŵ��Ѷ���Ȼ��ʹ�����µ����㷨���е�����



void HeapTop(HP* php) 
{
	assert(php);
	assert(!Heapempty(php));
	return php->a[0];
}



int main()
{
	HP test;//������ʹ��HP* 
	HeapIint(&test);//ʹ��ǰҪ��ʼ����
	HPDateType a[] = { 65,100,70,32,50,60};
	int size = sizeof(a)/sizeof(HPDateType);


	HeapCreat_Up(&test,size,a);

	HeapPush(&test, 10);
	HeapPrint(&test);

	HeapPop(&test);
	HeapPrint(&test);



	return 0;
}