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
}//���ֽṹ�������ھ�̬��˳��������������˷ѣ�


struct TreeNode
{
	int date;
	//��һ��˳���洢���ӽڵ��ָ�룡
	struct TreeNode** children;//ΪʲôҪ����ָ���أ���ΪҪ�洢�����������ָ�룬����Ҫ����ָ���������洢��
	int childsize;
	int childcapacity;
}


typedef int DateType;
struct TreeNode
{
	struct TreeNode* Child;// ��һ�����ӽ��
	struct TreeNode* brother;// ָ������һ���ֵܽ��
	DateType date;//�洢���ݣ�
}


void printTree(struct TreeNode* parent)
{
	if (parent == NULL)
		return;
	struct TreeNode* cur = parent;
	while (cur)
	{
		printf("%d", cur->date);//�ȷ��ʵ�ǰ�ڵ�
		printTree(cur->child);//�����Ժ��ӽڵ�
		cur = cur->brother//�ٷ����ֵܽڵ㣡
	}
}