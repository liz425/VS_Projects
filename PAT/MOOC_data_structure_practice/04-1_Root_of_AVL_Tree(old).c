#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree
{
	int data;
	int hight;
	int bf;                 //平衡因子：左树高度减去右树高度
	struct tree *lchild;
	struct tree *rchild;
	struct tree *parent;    //删除所用，指向父母
}Node, *Tree;

//Tree Init(Tree T, int data)//初始化根节点：父母为NULL
//{
//	T = (Tree)malloc(sizeof(Node));
//	T->data = data;
//	T->hight = 1;
//	T->bf = 0;
//	T->parent = T->lchild = T->rchild = NULL;
//	return T;
//}

int MAX(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int Height(Tree T)//返回高度
{
	if (T)
		return T->hight;
	return 0;
}

Tree SingleLeft(Tree k1)//单旋：左旋  注意父母的变化
{                       //引入如父母这一指针，所以需要注意在旋转的时候，需要将父母也变换
	Tree k2 = k1->rchild;

	k1->rchild = k2->lchild;
	if (k2->lchild)
		k2->lchild->parent = k1;
	k2->lchild = k1;

	k2->parent = k1->parent;//注意这二者的顺序，若是相反，则会有k2->parent = k2;
	k1->parent = k2;

	k1->hight = MAX(Height(k1->lchild), Height(k1->rchild)) + 1;
	k2->hight = MAX(Height(k2->lchild), Height(k2->rchild)) + 1;
	k1->bf = Height(k1->lchild) - Height(k1->rchild);
	k2->bf = Height(k2->lchild) - Height(k2->rchild);

	return k2;
}

Tree SingleRight(Tree k1)//单旋：右旋
{
	Tree k2 = k1->lchild;

	k1->lchild = k2->rchild;
	if (k2->rchild)
		k2->rchild->parent = k1;
	k2->rchild = k1;

	k2->parent = k1->parent;
	k1->parent = k2;

	k1->hight = MAX(Height(k1->lchild), Height(k1->rchild)) + 1;
	k2->hight = MAX(Height(k2->lchild), Height(k2->rchild)) + 1;
	k1->bf = Height(k1->lchild) - Height(k1->rchild);
	k2->bf = Height(k2->lchild) - Height(k2->rchild);

	return k2;
}

Tree LeftRight(Tree k1)//双旋：左旋——右旋
{
	k1->lchild = SingleLeft(k1->lchild);
	return SingleRight(k1);
}

Tree RightLeft(Tree k1)//双旋： 右旋--左旋
{
	k1->rchild = SingleRight(k1->rchild);
	return SingleLeft(k1);
}

Tree FindMin(Tree T)//找出最小节点
{
	Tree temp = T;
	while (temp->lchild)
		temp = temp->lchild;
	return temp;
}

Tree Insert(Tree T, Tree pre, int data)//插入,边插入边旋转调整平衡   四种对应关系
{                                       //由于有parent，所以需要引入pre指向前驱指针
	if (!T)
	{
		T = (Tree)malloc(sizeof(Node));  // 插入新结点or初始化根节点
		if (!T)
		{
			printf("Can Not Init");
			return NULL;
		}
		T->hight = 1;
		T->bf = 0;
		T->data = data;
		T->parent = pre;
		T->lchild = T->rchild = NULL;
	}
	else
	{
		if (T->data < data)
		{
			T->rchild = Insert(T->rchild, T, data);
			T->hight = MAX(Height(T->lchild), Height(T->rchild)) + 1;//高度和平衡因子的更新
			T->bf = Height(T->lchild) - Height(T->rchild);
			if (T->bf == -2)
			{
				if (data < T->rchild->data)//RL
					T = RightLeft(T);
				else if (data > T->rchild->data)//RR
					T = SingleLeft(T);
			}
		}
		if (T->data > data)
		{
			T->lchild = Insert(T->lchild, T, data);
			T->hight = MAX(Height(T->lchild), Height(T->rchild)) + 1;//高度和平衡因子的更新
			T->bf = Height(T->lchild) - Height(T->rchild);
			if (T->bf == 2)
			{
				if (data < T->lchild->data)//LL
					T = SingleRight(T);
				else if (data > T->lchild->data)//LR
					T = LeftRight(T);
			}
		}
	}

	T->hight = MAX(Height(T->lchild), Height(T->rchild)) + 1;//高度和平衡因子的更新
	T->bf = Height(T->lchild) - Height(T->rchild);

	return T;
}

Tree Delete(Tree T, int data)//删除操作，比较复杂
{                             //先按照一般的查找二叉树将节点删除后，再由该节点自下而上的回溯，调整每个节点到平衡至根节点
	Tree temp, target = T, parent = NULL, grand;
	int ele;

	while (target)//删除操作
	{
		if (target->data < data)
			target = target->rchild;
		else if (target->data > data)
			target = target->lchild;
		else if (target->lchild && target->rchild)//找出删除节点
		{//两个孩子情况
			temp = FindMin(target->rchild);
			parent = temp->parent;//注意该语句的顺序，若是对target做了处理且target就是temp的父母，那么此时parent并不准确
			target->data = temp->data;
			//if (temp->rchild)//最小节点必然没有左子树
			//判断删除节点是其父母的左（右）子树，分别处理；
			if (temp->parent->data <= temp->data)//右子树：注意等号，由于此时temp->parent可能正是target，故可能等于
			{
				temp->parent->rchild = temp->rchild;
				if (temp->rchild)//注意指针父母的变化
					temp->rchild->parent = temp->parent;
			}
			else //左子树
			{
				temp->parent->lchild = temp->rchild;
				if (temp->rchild)
					temp->rchild->parent = temp->parent;
			}

			free(temp);
			break;
		}
		else//只有一个孩子或者没有孩子（树叶） 
		{
			temp = target;
			parent = temp->parent;
			if (target->lchild)//有左孩子
			if (parent->data < data)//判断删除节点位置在父母节点的左还是右
			{
				parent->rchild = target->lchild;
				target->lchild->parent = parent;
			}
			else
			{
				parent->lchild = target->lchild;
				target->lchild->parent = parent;
			}
			else    //不用判断右孩子是否为空：若是为空，就是孩子，此时等于target->rchild也就是等于NULL
			if (parent->data < data)
			{
				parent->rchild = target->rchild;
				if (target->rchild)
					target->rchild->parent = parent;
			}
			else
			{
				parent->lchild = target->rchild;
				if (target->rchild)
					target->rchild->parent = parent;
			}

			free(temp);
			break;
		}
	}

	while (parent)//由删除节点往上调整平衡
	{
		ele = parent->data;
		parent->hight = MAX(Height(parent->lchild), Height(parent->rchild));//更新高度和平衡因子
		parent->bf = Height(parent->lchild) - Height(parent->rchild);
		grand = parent->parent;
		if (parent->bf == -2)//四种对应情况，相对于插入来说，有着特殊情况，即bf==0的情况
		{
			if (parent->rchild->bf > 0)
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
			if (parent->lchild->bf < 0)
				parent = LeftRight(parent);
			else
				parent = SingleRight(parent);
		}

		if (grand)//祖父母：这是必须的，否则无法连接
		{
			if (grand->data > ele)//判断位置
				grand->lchild = parent;
			else
				grand->rchild = parent;
			parent->parent = grand;
		}
		else
			T = parent;//注意：此时说明已经到了根节点，需要变化
		parent = parent->parent;//往上走
	}

	return T;
}


int main()
{
	Tree T = NULL;

	int i;
	int n;
	int node;
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		scanf("%d", &node);
		T = Insert(T, T, node);
	}
	printf("%d", T->data);

	
	//system("pause");
	return 0;
}