#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


typedef struct tree
{
	int data;
	int height;			     // Define that: height of NULL is 0, height of leaves is 1
	int bf;                 //平衡因子：左树高度减去右树高度
	struct tree *left;
	struct tree *right;
}Node, *Tree;


int Max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

Tree heightUpdate(Tree T)
{
	if (T->left && T->right)
		T->height = Max((T->left->height), (T->right->height)) + 1;
	else if (T->left)
		T->height = T->left->height + 1;
	else if (T->right)
		T->height = T->right->height + 1;
	else
		T->height = 1;
	return T;
}

Tree bfUpdate(Tree T)
{
	if (T->left && T->right)
		T->bf = (T->left->height) - (T->right->height);
	else if (T->left)
		T->bf = (T->left->height);
	else if (T->right)
		T->bf = -(T->right->height);
	return T;
}

Tree SingleLeft(Tree k1)			//单旋：左旋 
{                       
	Tree k2 = k1->right;

	k1->right = k2->left;
	k2->left = k1;

	heightUpdate(k1);
	heightUpdate(k2);
	bfUpdate(k1);
	bfUpdate(k2);

	return k2;
}

Tree SingleRight(Tree k1)			//单旋：右旋
{
	Tree k2 = k1->left;

	k1->left = k2->right;
	k2->right = k1;

	heightUpdate(k1);
	heightUpdate(k2);
	bfUpdate(k1);
	bfUpdate(k2);

	return k2;
}

Tree LeftRight(Tree k1)				//双旋：左旋——右旋
{
	k1->left = SingleLeft(k1->left);
	//此时K1->left 的height和bf已更新，k1的height和bf本应立即更新。
	//但下面SingleRight(k1)函数会完成k1的height和bf的更新工作，故此处可省略
	return SingleRight(k1);
}

Tree RightLeft(Tree k1)				//双旋： 右旋--左旋
{
	k1->right = SingleRight(k1->right);
	return SingleLeft(k1);
}

/******************************************
Tree FindMin(Tree T)//找出最小节点
{
	Tree temp = T;
	while (temp->left)
		temp = temp->left;
	return temp;
}
*******************************************/

Tree Insert(Tree T, int X)				//插入,边插入边旋转调整平衡   四种对应关系
{                                      
	if (!T)
	{
		T = (Tree)malloc(sizeof(Node));  // 插入新结点or初始化根节点
		T->height = 1;
		T->bf = 0;
		T->data = X;
		T->left = T->right = NULL;
	}
	else
	{
		if (X > T->data)
		{
			T->right = Insert(T->right, X);
			heightUpdate(T);
			bfUpdate(T);
			if (T->bf == -2)
			{
				if (X < T->right->data)			//RL形，需要RightLeft旋转
					T = RightLeft(T);
				else if (X > T->right->data)	//RR形，需要SingleLeft旋转
					T = SingleLeft(T);
			}
		}
		else if (X < T->data)
		{
			T->left = Insert(T->left, X);
			heightUpdate(T);
			bfUpdate(T);
			if (T->bf == 2)
			{
				if (X < T->left->data)			//LL形，需要SingleRight旋转
					T = SingleRight(T);
				else if (X > T->left->data)     //LR形式，需要LeftRight旋转
					T = LeftRight(T);
			}
		}
	}

	return T;
}


/********************************************************************************************
Tree Delete(Tree T, int X)//删除操作，比较复杂
{                             //先按照一般的查找二叉树将节点删除后，再由该节点自下而上的回溯，调整每个节点到平衡至根节点
	Tree temp, target = T, parent = NULL, grand;
	int ele;

	while (target)//删除操作
	{
		if (target->data < X)
			target = target->right;
		else if (target->data > X)
			target = target->left;
		else if (target->left && target->right)//找出删除节点
		{//两个孩子情况
			temp = FindMin(target->right);
			parent = temp->parent;//注意该语句的顺序，若是对target做了处理且target就是temp的父母，那么此时parent并不准确
			target->data = temp->data;
			//if (temp->right)//最小节点必然没有左子树
			//判断删除节点是其父母的左（右）子树，分别处理；
			if (temp->parent->data <= temp->data)//右子树：注意等号，由于此时temp->parent可能正是target，故可能等于
			{
				temp->parent->right = temp->right;
				if (temp->right)//注意指针父母的变化
					temp->right->parent = temp->parent;
			}
			else //左子树
			{
				temp->parent->left = temp->right;
				if (temp->right)
					temp->right->parent = temp->parent;
			}

			free(temp);
			break;
		}
		else//只有一个孩子或者没有孩子（树叶） 
		{
			temp = target;
			parent = temp->parent;
			if (target->left)//有左孩子
			if (parent->data < X)//判断删除节点位置在父母节点的左还是右
			{
				parent->right = target->left;
				target->left->parent = parent;
			}
			else
			{
				parent->left = target->left;
				target->left->parent = parent;
			}
			else    //不用判断右孩子是否为空：若是为空，就是孩子，此时等于target->right也就是等于NULL
			if (parent->data < X)
			{
				parent->right = target->right;
				if (target->right)
					target->right->parent = parent;
			}
			else
			{
				parent->left = target->right;
				if (target->right)
					target->right->parent = parent;
			}

			free(temp);
			break;
		}
	}

	while (parent)//由删除节点往上调整平衡
	{
		ele = parent->data;
		heightUpdate(T);
		bfUpdate(T);
		grand = parent->parent;
		if (parent->bf == -2)//四种对应情况，相对于插入来说，有着特殊情况，即bf==0的情况
		{
			if (parent->right->bf > 0)
			{
				parent = RightLeft(parent);
			}
			else
			{
				parent = SingleLeft(parent);
			}
		}
		else if (parent->bf == 2)
		{
			if (parent->left->bf < 0)
				parent = LeftRight(parent);
			else
				parent = SingleRight(parent);
		}

		if (grand)//祖父母：这是必须的，否则无法连接
		{
			if (grand->data > ele)//判断位置
				grand->left = parent;
			else
				grand->right = parent;
			parent->parent = grand;
		}
		else
			T = parent;//注意：此时说明已经到了根节点，需要变化
		parent = parent->parent;//往上走
	}

	return T;
}
***********************************************************************/

int main()
{
	Tree T = NULL;

	int i;
	int n;
	int node;
	///*******************************/
	//FILE *fp = NULL;
	//fp = fopen("04-1.txt", "r");
	//fscanf(fp,"%d", &n);
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
	///*******************************/
	//	fscanf(fp,"%d", &node);
		scanf("%d", &node);

		T = Insert(T, node);
	}
	printf("%d", T->data);
	
	///*******************************/
	//fclose(fp);
	//system("pause");
	///*******************************/
	return 0;
}
