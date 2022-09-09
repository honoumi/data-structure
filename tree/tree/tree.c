#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
struct TreeNode
{
	int date;
	struct TreeNode* child1;
	struct TreeNode* child2;
	struct TreeNode* child3;
	struct TreeNode* child4;
	// ........
}

#define N 5
struct TreeNode
{
	int date;
	struct TreeNode* children[N];
	int childsize;
}//这种结构是类似于静态的顺序表！但是这样很浪费！


struct TreeNode
{
	int date;
	//用一个顺序表存储孩子节点的指针！
	struct TreeNode** children;//为什么要二级指针呢？因为要存储数据是数组的指针，所以要二级指针数组来存储！
	int childsize;
	int childcapacity;
}


typedef int DateType;
struct TreeNode
{
	struct TreeNode* Child;// 第一个孩子结点
	struct TreeNode* brother;// 指向其下一个兄弟结点
	DateType date;//存储数据！
}


void printTree(struct TreeNode* parent)
{
	if (parent == NULL)
		return;
	struct TreeNode* cur = parent;
	while (cur)
	{
		printf("%d", cur->date);//先访问当前节点
		printTree(cur->child);//访问自孩子节点
		cur = cur->brother//再访问兄弟节点！
	}
}