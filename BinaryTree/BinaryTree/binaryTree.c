#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<assert.h>

#include "Queue.h"


typedef int BTdataType;

typedef struct BinaryTreeNode
{
	BTdataType data;
	struct BinaryTreeNode* left;//ָ������
	struct BinartTreeNode* right;//ָ���Һ���
}BTNode;

//typedef struct BinaryTreeNode
//{
//	BTdataType data; //ָ��ýڵ������
//	struct BinaryTreeNode* parent;//ָ��ýڵ��˫��
//	struct BinaryTreeNode* left;//ָ������
//	struct BinaryTreeNode* right;//ָ���Һ���
//
//
//}BTNode;

void PreOrder(BTNode* root)
{
    if (root == NULL)
    {
        printf("NULL ");
        return;
    }
    printf("%d ", root->data);//�ȷ��ʸ�
    PreOrder(root->left);//�ٷ���������
    PreOrder(root->right);//������������   
}


void InOrder(BTNode* root)
{
    if (root == NULL)
    {
        printf("NULL ");
        return;
    }
    PreOrder(root->left);//�ȷ���������
    printf("%d ", root->data);//�ٷ��ʸ�
    PreOrder(root->right);//������������   
}


void PostOrder(BTNode* root)
{
    if (root == NULL)
    {
        printf("NULL ");
        return;
    }
    PreOrder(root->left);//�ȷ���������
    PreOrder(root->right);//Ȼ�����������   
    printf("%d ", root->data);//�����ʸ�
}

int BinaryTreeSize(BTNode* root)//��ʵ����һ��ǰ�����
{
    if (root == NULL)
        return 0;

    return 1 + BinaryTreeSize(root->left) + BinaryTreeSize(root->right);
}


int BinaryTreeLeafSize(BTNode* root)
{
    if (root == NULL)
        return 0;

    if (root->left == 0 && root->right == 0)
        return 1;

    return  BinaryTreeLeafSize(root->left) + BinaryTreeLeafSize(root->right);
}


int BinaryTreeLevelKSize(BTNode* root, int k)//�ֽ�Ϊ��k-1��Ľڵ����
{
    if (root == NULL)
        return 0;
    if (k == 1)
        return 1;

    return  BinaryTreeLevelKSize(root->left, k - 1) + BinaryTreeLevelKSize(root->left, k - 1);
}


int BinaryTreeHight(BTNode* root)
{
    if (root == NULL)
        return 0;

    int lefthight = BinaryTreeHight(root->left)+1;
    int righthight = BinaryTreeHight(root->right)+1;

    return lefthight > righthight ? lefthight : righthight;
}


BTNode* BinaryTreeFind(BTNode* root, BTdataType x)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->data == x)
        return root;
    
    BTNode* pleft = BinaryTreeFind(root->left,x);
    if (pleft)
        return pleft;

    BTNode* Pright = BinaryTreeFind(root->right, x);
    if(Pright)
        return Pright;

    return NULL;
}

BTNode* BinaryTreeCreat(BTdataType* a, int* pi)
{
    if (a[*pi] == '#')
    {
        (*pi)++;
        return NULL;
    }

    BTNode* root = (BTNode*)malloc(sizeof(BTNode));
    if (root == NULL)
    {
        perror("malloc fail");
    }

    root->data = a[*pi];
    (*pi)++;
    root->left = BinaryTreeCreat(a, pi);
    root->right = BinaryTreeCreat(a, pi);

    return root;

}

void BinaryTreeDestory(BTNode* root)//���ʾ���һ�����������
{
    if (root == NULL)
    {
        return;
    }
    BinaryTreeDestory(root->left);
    BinaryTreeDestory(root->right);

    free(root);
}


void LevelOrder(BTNode* root)
{
    Queue a;
    QueueInit(&a);
    if (root)
    {
        QueuePush(&a, root);
    }
    while (!QueueEmpty(&a))
    {
        BTNode* front = Queuefront(&a);
        QueuePop(&a);
        printf("%d ", front->data);
        //���Լ���ȥ�����Լ�����һ�㣡
        if (front->left)
        {
            QueuePush(&a, front->left);
        }
        if (front->right)
        {
            QueuePush(&a, front->right);
        }
    }

    QueueDestroy(&a);
}//���������ԭ��ʹ�ö��У��Ƚ��ȳ������Լ�������ʱ��Ͱ��Լ��ĺ��Ӵ���ȥ��
//��������ڵ���߽ڵ��ָ�룬���ǷŽڵ��ָ����Ӻã���Ϊ�Žڵ�Ļ�ռ�ڴ����
int BinaryTreeComplete(BTNode* root)//�����Ҫ�õ����������
{
    Queue a;
    QueueInit(&a);
    if (root)
        QueuePush(&a, root);
    while (!QueueEmpty(&a))
    {
        BTNode* front = Queuefront(&a);
        QueuePop(&a);
        if (front == NULL)
            break;
        QueuePush(&a, root->left);
        QueuePush(&a, root->right);

    }

    while (!QueueEmpty(&a))
    {
        BTNode* front = Queuefront(&a);
        QueuePop(&a);
        if (front != NULL)
        {
            //���ﷵ��ʱ����Ҫdes�����������ڴ�й©��
            return false;
        }
        QueuePush(&a, root->left);
        QueuePush(&a, root->right);
    }



    QueueDestroy(&a);
    return true;
}
//��Ҫ�ж��ǲ�����ȫ��������Ҫ�ж�NULL�����ǲ���ȫ��NULL
int main()
{
    return 0;
}


