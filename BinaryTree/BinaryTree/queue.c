#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include "Queue.h"


void QueueInit(Queue* pq)
{
    assert(pq);
    pq->head = NULL;
    pq->tail = NULL;
}

void QueueDestroy(Queue* pq)
{
    assert(pq);
    QueueNode* cur = pq->head;
    while (cur != NULL)
    {
        QueueNode* next = cur->next;
        free(cur);
        cur = next;
    }
    pq->head = pq->tail = NULL;
}

void QueuePush(Queue* pq, QDateType x)
{
    assert(pq);
    QueueNode* newnode = (QueueNode*)malloc(sizeof(QueueNode));
    newnode->date = x;
    newnode->next = NULL;

    if (pq->head == NULL)//刚开始没有一个节点时候！
    {
        pq->head = newnode;
        pq->tail = newnode;
    }
    else
    {
        pq->tail->next = newnode;//先把tail指向newnode
        pq->tail = newnode;//再把自己变成newnode
    }
}

void QueuePop(Queue* pq)
{
    assert(pq);
    assert(!QueueEmpty(pq));//防止出现空！ 
    QueueNode* newhead = pq->head->next;
    free(pq->head);
    pq->head = newhead;
    if (pq->head == NULL)
        pq->tail = NULL;//防止出现野指针，head走到NULL去了，但是tail还是在那个位置！
}
QDateType Queuefront(Queue* pq)//取头的数据！
{
    assert(pq);
    assert(!QueueEmpty(pq));
    return pq->head->date;
}
QDateType QueueBack(Queue* pq)
{
    assert(pq);
    assert(!QueueEmpty(pq));
    return pq->tail->date;
}
int QueueSize(Queue* pq)//当前的size的实现方式
{
    assert(pq);
    assert(!QueueEmpty(pq));
    int size = 0;
    QueueNode* cur = pq->head;
    while (cur)
    {
        cur = cur->next;
        size++;
    }
    return size;
}
bool QueueEmpty(Queue* pq)
{
    assert(pq);
    return pq->head == NULL && pq->head == NULL;
}
