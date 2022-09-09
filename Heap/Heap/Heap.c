#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int	HPDateType;

typedef struct Heap
{
	HPDateType* a;//创建一个数组
	int size;//记录位置
	int capacity;//记录容积
}HP;//虽然和顺序表和结构一样，但是操作方式是不同的！


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


void AdJustUp(HPDateType* a, int child)//child指的是孩子的位置！ 父亲 = （孩子-1）/2；//此时是大堆
{
	int parent = (child - 1) / 2;
	while (child > 0)//parent >=0 这个条件会有问题,
	{
		if (a[child] < a[parent])//> 是大堆 ，< 是小堆
		{
			swap(&a[child], &a[parent]);
			child = parent;//父亲变孩子
			parent = (child - 1 / 2);//新的孩子找它的父亲！//当parent = 0时候，（0-1）/2 == 0，还会进来一次！
		}
		else
		{
			break;
		}
		
 	}
}

//void AdJustDown(HPDateType* a,)
void HeapPush(HP* php,HPDateType x)//插入完保持堆
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
	php->a[php->size++] = x;//在size除插入，然后进行向上调整算法
	AdJustUp(php->a, php->size - 1);

}//使用向上调整算法


void HeapCreat_Up(HP* php,int size,HPDateType* a)//但是向上调整的建堆效率低于向下调整！	
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
		//找出小的那个孩子//这是小堆的算法！大堆的要改成找最大的那个孩子
		if (minchild + 1 < size && a[minchild] > a[minchild + 1])
			minchild++;
		if (a[minchild] < a[parent])//大堆的话这里也要改！
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
void HeapPop(HP* php)//删除堆顶的元素的真正意义在于找次大与次小
{
	assert(php);
	assert(!Heapempty(php));
	swap(&php->a[0], &php->a[php->size - 1]);
	php->size--;
	AdjustDown(php->a, 0, php->size);

}//思路是先把最下面的放到堆顶，然后使用向下调整算法进行调整！



void HeapTop(HP* php) 
{
	assert(php);
	assert(!Heapempty(php));
	return php->a[0];
}



int main()
{
	HP test;//不可以使用HP* 
	HeapIint(&test);//使用前要初始化！
	HPDateType a[] = { 65,100,70,32,50,60};
	int size = sizeof(a)/sizeof(HPDateType);


	HeapCreat_Up(&test,size,a);

	HeapPush(&test, 10);
	HeapPrint(&test);

	HeapPop(&test);
	HeapPrint(&test);



	return 0;
}