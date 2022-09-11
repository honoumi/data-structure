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

    if (pq->head == NULL)//�տ�ʼû��һ���ڵ�ʱ��
    {
        pq->head = newnode;
        pq->tail = newnode;
    }
    else
    {
        pq->tail->next = newnode;//�Ȱ�tailָ��newnode
        pq->tail = newnode;//�ٰ��Լ����newnode
    }
}

void QueuePop(Queue* pq)
{
    assert(pq);
    assert(!QueueEmpty(pq));//��ֹ���ֿգ� 
    QueueNode* newhead = pq->head->next;
    free(pq->head);
    pq->head = newhead;
    if (pq->head == NULL)
        pq->tail = NULL;//��ֹ����Ұָ�룬head�ߵ�NULLȥ�ˣ�����tail�������Ǹ�λ�ã�
}
QDateType Queuefront(Queue* pq)//ȡͷ�����ݣ�
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
int QueueSize(Queue* pq)//��ǰ��size��ʵ�ַ�ʽ
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
