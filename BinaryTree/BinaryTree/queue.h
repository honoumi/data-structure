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
//ʹ�����ֽṹ�ķ�����һ��Ϊ�˲�������ָ�뱣֤�ӿڵ�һ���ԣ����Ǹ��ӵķ��㣡

void QueueInit(Queue* pq);
void QueueDestroy(Queue* pq);
void QueuePush(Queue* pd, QDateType x);//����ͷ��β�� ��Ϊ����һ��ֵͷβ�壡
void QueuePop(Queue* pd);//����ͷɾ����βɾ��Ϊ����һ��ͷɾ��
QDateType Queuefront(Queue* pd);
QDateType QueueBack(Queue* pd);
int QueueSize(Queue* pd);
bool QueueEmpty(Queue* pd);
