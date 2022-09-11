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
		//找出小的那个孩子//这是小堆的算法！大堆的要改成找最大的那个孩子
		if (minchild + 1 < size && a[minchild] > a[minchild + 1])
			minchild++;
		if (a[minchild] <  a[parent])//大堆的话这里也要改！
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



HPDateType HeapTop(HP* php) 
{
	assert(php);
	assert(!Heapempty(php));
	return php->a[0];
}



void HeapSort(HPDateType* a,int size)
{
	//for (int i = 1; i < size; i++)//不要建堆，而是把a本身变成堆
	//{
	//	AdJustUp(a, i);//不是使用HeapPush！而是直接进行调整算法！把每个位置都进行一次向上调整算法！
	//}
	//还有向下调整建堆！向下调整的前提是左右子树都是同一个大（小）堆！
	//所以但是可以从最后一个的非叶子节点开始，向下调整，然后逐渐往上！
	//向下调整的算法是优于向上调整的，因为最后一层的在一定情况下叶子节点占了所有节点的一半！
	//向下调整是越多越快！向上调整是越多越慢！

	for (int i = (size - 1 - 1) / 2; i >= 0; i--)//一定要i>=0 否则顶部的无法调整到！
	{
		AdjustDown(a, i, size);
	}

	for (int i = 0; i < size; i++)
	{
		swap(&a[0], &a[size - 1-i]);//为什么要-i呢，因为把该堆最大（小）的放在最后面，然后就不要动他，开始放次大（小）
		AdjustDown(a,0, size-1-i);//然后开始进行调整！
	}
}

//升序建大堆 降序建小堆！

//如果选小堆最大的问题是如何找到次小的！
//方法可以重新建堆！但是每次都这样的话实在太麻烦了！
//

//小堆中最小的一定在最前面，大堆中最大的一定在最前面！
//所以在大堆中只要把第一个和最后一个互换然后，把最后一个看成是不放在队里的进行向下调整！这样就可以排出升序！



//TOP前K最大个问题！
// 建大堆：就要Pop K 次！如果没有数据结构的堆要先建堆效率为O(N),然后pop每次	Pop的效率为O(logN),所以效率为O(N+logN*K)
//但是问题是 N一旦很大，建堆就不可以了！因为数据太大，内存放不下
//所以建小堆比较好，因为小堆Top绝对是最小的，然后把要进堆的数据对比一下，比TOP大的就放进堆里，然后向下调整！把新的次小放上来，到最后数据中最大的都会放进这个堆里！
//时间复杂度为O(K+logK*(N-K)


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

	for (int i = (k - 1 - 1)/2;i >= 0;i--)//i是>=0!!!!!!!!,不是<n!!!!!
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
	HP test;//不可以使用HP* 
	HeapIint(&test);//使用前要初始化！
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