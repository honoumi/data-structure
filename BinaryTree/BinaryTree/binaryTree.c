#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<assert.h>

#include "Queue.h"


typedef int BTdataType;

typedef struct BinaryTreeNode
{
	BTdataType data;
	struct BinaryTreeNode* left;//指向左孩子
	struct BinartTreeNode* right;//指向右孩子
}BTNode;

//typedef struct BinaryTreeNode
//{
//	BTdataType data; //指向该节点的数据
//	struct BinaryTreeNode* parent;//指向该节点的双亲
//	struct BinaryTreeNode* left;//指向左孩子
//	struct BinaryTreeNode* right;//指向右孩子
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
    printf("%d ", root->data);//先访问根
    PreOrder(root->left);//再访问左子树
    PreOrder(root->right);//最后访问右子树   
}


void InOrder(BTNode* root)
{
    if (root == NULL)
    {
        printf("NULL ");
        return;
    }
    PreOrder(root->left);//先访问左子树
    printf("%d ", root->data);//再访问根
    PreOrder(root->right);//最后访问右子树   
}


void PostOrder(BTNode* root)
{
    if (root == NULL)
    {
        printf("NULL ");
        return;
    }
    PreOrder(root->left);//先访问左子树
    PreOrder(root->right);//然后访问右子树   
    printf("%d ", root->data);//最后访问根
}

int BinaryTreeSize(BTNode* root)//其实就是一个前序遍历
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


int BinaryTreeLevelKSize(BTNode* root, int k)//分解为第k-1层的节点个数
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

void BinaryTreeDestory(BTNode* root)//本质就是一个后序遍历！
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
        //把自己出去，入自己的下一层！
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
}//层序遍历的原理：使用队列，先进先出，当自己出来的时候就把自己的孩子带进去！
//队列里面节点或者节点的指针，但是放节点的指针更加好，因为放节点的话占内存更大
int BinaryTreeComplete(BTNode* root)//这就需要用到层序遍历！
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
            //这里返回时候需要des！否则会造成内存泄漏！
            return false;
        }
        QueuePush(&a, root->left);
        QueuePush(&a, root->right);
    }



    QueueDestroy(&a);
    return true;
}
//想要判断是不是完全二叉树就要判断NULL后面是不是全是NULL
int main()
{
    return 0;
}


