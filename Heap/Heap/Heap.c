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



void HeapCreat(HP* php, HPDateType* a,int size)
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
		if (a[minchild] <  a[parent])//��ѵĻ�����ҲҪ�ģ�
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



HPDateType HeapTop(HP* php) 
{
	assert(php);
	assert(!Heapempty(php));
	return php->a[0];
}



void HeapSort(HPDateType* a,int size)
{
	//for (int i = 1; i < size; i++)//��Ҫ���ѣ����ǰ�a�����ɶ�
	//{
	//	AdJustUp(a, i);//����ʹ��HeapPush������ֱ�ӽ��е����㷨����ÿ��λ�ö�����һ�����ϵ����㷨��
	//}
	//�������µ������ѣ����µ�����ǰ����������������ͬһ����С���ѣ�
	//���Ե��ǿ��Դ����һ���ķ�Ҷ�ӽڵ㿪ʼ�����µ�����Ȼ�������ϣ�
	//���µ������㷨���������ϵ����ģ���Ϊ���һ�����һ�������Ҷ�ӽڵ�ռ�����нڵ��һ�룡
	//���µ�����Խ��Խ�죡���ϵ�����Խ��Խ����

	for (int i = (size - 1 - 1) / 2; i >= 0; i--)//һ��Ҫi>=0 ���򶥲����޷���������
	{
		AdjustDown(a, i, size);
	}

	for (int i = 0; i < size; i++)
	{
		swap(&a[0], &a[size - 1-i]);//ΪʲôҪ-i�أ���Ϊ�Ѹö����С���ķ�������棬Ȼ��Ͳ�Ҫ��������ʼ�Ŵδ�С��
		AdjustDown(a,0, size-1-i);//Ȼ��ʼ���е�����
	}
}

//���򽨴�� ����С�ѣ�

//���ѡС����������������ҵ���С�ģ�
//�����������½��ѣ�����ÿ�ζ������Ļ�ʵ��̫�鷳�ˣ�
//

//С������С��һ������ǰ�棬���������һ������ǰ�棡
//�����ڴ����ֻҪ�ѵ�һ�������һ������Ȼ�󣬰����һ�������ǲ����ڶ���Ľ������µ����������Ϳ����ų�����



//TOPǰK�������⣡
// ����ѣ���ҪPop K �Σ����û�����ݽṹ�Ķ�Ҫ�Ƚ���Ч��ΪO(N),Ȼ��popÿ��	Pop��Ч��ΪO(logN),����Ч��ΪO(N+logN*K)
//���������� Nһ���ܴ󣬽��ѾͲ������ˣ���Ϊ����̫���ڴ�Ų���
//���Խ�С�ѱȽϺã���ΪС��Top��������С�ģ�Ȼ���Ҫ���ѵ����ݶԱ�һ�£���TOP��ľͷŽ����Ȼ�����µ��������µĴ�С����������������������Ķ���Ž�������
//ʱ�临�Ӷ�ΪO(K+logK*(N-K)


void PrintTopK(int* a, int n, int k)
{
	int* maxheap;
	int* temp = (int*)malloc(sizeof(int) * k);
	if (temp == NULL)
	{
		perror("malloc fail");
	}
	maxheap = temp;

	for (int i = 0; i < k; i++)
	{
		maxheap[i] = a[i];
	}

	for (int i = (k - 1 - 1)/2;i >= 0;i--)//i��>=0!!!!!!!!,����<n!!!!!
	{
		AdjustDown(maxheap, i, k);
	}

	for (int i = k; i < n; i++)
	{
		if (maxheap[0] < a[i])
		{
			maxheap[0] = a[i];
			AdjustDown(maxheap, 0, k);
		}
	}
	for (int i = 0; i < k; i++)
	{
		printf("%d ", maxheap[i]);
	}
	free(maxheap);
}


void PrintTopK2(int* a, int n, int k)
{
	HP b;
	HeapIint(&b);
	HeapCreat(&b, a, k);

	for (int i = k; i < n; i++)
	{
		if (b.a[0]< a[i])
		{
			b.a[0] = a[i];
			AdjustDown(b.a, 0, k);
		}
	}
	HeapPrint(&b);
	HeapDestroy(&b);
}

void PrintTopK3(int* a, int n, int k)
{
	for (int i = 0; i < k; i++)
	{
		AdjustDown(a, i, k);
	}
	for (int i = k; i < n; i++)
	{
		if (a[0] < a[i])
		{
			a[0] = a[i];
			AdjustDown(a, 0, k);
		}
	}
	for (int i = 0; i < k; i++)
	{
		printf("%d ", a[i]);
	}

}
void test()
{
	HP test;//������ʹ��HP* 
	HeapIint(&test);//ʹ��ǰҪ��ʼ����
	HPDateType a[] = { 65,100,70,32,50,60 };
	int size = sizeof(a) / sizeof(HPDateType);


	HeapCreat(&test,a, size);

	HeapPush(&test, 10);
	HeapPrint(&test);

	HeapPop(&test);
	HeapPrint(&test);
}
void test2()
{
	HPDateType a[] = { 65,100,70,32,50,60 };
	int size = sizeof(a) / sizeof(HPDateType);
	HeapSort(a, size);
	for (int i = 0; i < size; i++)
	{
		printf("%d ", a[i]);
	}

}


void TestTopk()
{
	int n = 10000;
	int* a = (int*)malloc(sizeof(int) * n);
	srand(time(0));
	for (size_t i = 0; i < n; ++i)
	{
		a[i] = rand() % 1000000;
	}
	a[5] = 1000000 + 1;
	a[1231] = 1000000 + 2;
	a[531] = 1000000 + 3;
	a[5121] = 1000000 + 4;
	a[115] = 1000000 + 5;
	a[2335] = 1000000 + 6;
	a[9999] = 1000000 + 7;
	a[76] = 1000000 + 8;
	a[423] = 1000000 + 9;
	a[3144] = 1000000 + 10;
	PrintTopK3(a, n, 10);
}

int main()
{

	//test2();
	TestTopk();
	//test3();

	



	return 0;
}