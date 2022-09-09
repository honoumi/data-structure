//#define _CRT_SECURE_NO_WARNINGS 1
//#include <stdio.h>
//
//typedef int HPDateType;
//
//struct  Heap
//{
//	HPDateType* a;
//	int size;
//	int capacity;
//};
//
//void swap(HPDateType* x, HPDateType* y)
//{
//	HPDateType temp = *x;
//	*x = *y;
//	*y = temp;
//}
//
//void AdJustUp(HPDateType* a, int child)
//{
//	int parent = (child - 1) / 2;
//
//	while (child > 0)
//	{
//		if (a[child] > a[parent])
//		{
//			swap(&a[child], &a[parent]);
//			child = parent;
//			parent = (child - 1) / 2;
//		}
//		else
//			break;
//	}
//
//
//
//
//
//
//}