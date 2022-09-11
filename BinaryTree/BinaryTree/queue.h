#pragma once
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef int BTdataType;

typedef struct BinaryTreeNode
{
	BTdataType data;
	struct BinaryTreeNode* left;
	struct BinartTreeNode* right;
}BTNode;

typedef  BTNode* QDateType;


typedef struct QueueNode
{
	struct QueueNode* next;
	QDateType date;
}QueueNode;

typedef struct Queue
{
	QueueNode* head;
	QueueNode* tail;
}Queue;
//使用这种结构的方法是一是为了不传二级指针保证接口的一致性！二是更加的方便！

void QueueInit(Queue* pq);
void QueueDestroy(Queue* pq);
void QueuePush(Queue* pd, QDateType x);//不分头插尾插 因为队列一定值头尾插！
void QueuePop(Queue* pd);//不分头删还是尾删因为队列一定头删！
QDateType Queuefront(Queue* pd);
QDateType QueueBack(Queue* pd);
int QueueSize(Queue* pd);
bool QueueEmpty(Queue* pd);
