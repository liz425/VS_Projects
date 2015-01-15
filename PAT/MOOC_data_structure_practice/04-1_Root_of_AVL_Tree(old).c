#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree
{
	int data;
	int hight;
	int bf;                 //ƽ�����ӣ������߶ȼ�ȥ�����߶�
	struct tree *lchild;
	struct tree *rchild;
	struct tree *parent;    //ɾ�����ã�ָ��ĸ
}Node, *Tree;

//Tree Init(Tree T, int data)//��ʼ�����ڵ㣺��ĸΪNULL
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

int Height(Tree T)//���ظ߶�
{
	if (T)
		return T->hight;
	return 0;
}

Tree SingleLeft(Tree k1)//����������  ע�⸸ĸ�ı仯
{                       //�����縸ĸ��һָ�룬������Ҫע������ת��ʱ����Ҫ����ĸҲ�任
	Tree k2 = k1->rchild;

	k1->rchild = k2->lchild;
	if (k2->lchild)
		k2->lchild->parent = k1;
	k2->lchild = k1;

	k2->parent = k1->parent;//ע������ߵ�˳�������෴�������k2->parent = k2;
	k1->parent = k2;

	k1->hight = MAX(Height(k1->lchild), Height(k1->rchild)) + 1;
	k2->hight = MAX(Height(k2->lchild), Height(k2->rchild)) + 1;
	k1->bf = Height(k1->lchild) - Height(k1->rchild);
	k2->bf = Height(k2->lchild) - Height(k2->rchild);

	return k2;
}

Tree SingleRight(Tree k1)//����������
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

Tree LeftRight(Tree k1)//˫����������������
{
	k1->lchild = SingleLeft(k1->lchild);
	return SingleRight(k1);
}

Tree RightLeft(Tree k1)//˫���� ����--����
{
	k1->rchild = SingleRight(k1->rchild);
	return SingleLeft(k1);
}

Tree FindMin(Tree T)//�ҳ���С�ڵ�
{
	Tree temp = T;
	while (temp->lchild)
		temp = temp->lchild;
	return temp;
}

Tree Insert(Tree T, Tree pre, int data)//����,�߲������ת����ƽ��   ���ֶ�Ӧ��ϵ
{                                       //������parent��������Ҫ����preָ��ǰ��ָ��
	if (!T)
	{
		T = (Tree)malloc(sizeof(Node));  // �����½��or��ʼ�����ڵ�
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
			T->hight = MAX(Height(T->lchild), Height(T->rchild)) + 1;//�߶Ⱥ�ƽ�����ӵĸ���
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
			T->hight = MAX(Height(T->lchild), Height(T->rchild)) + 1;//�߶Ⱥ�ƽ�����ӵĸ���
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

	T->hight = MAX(Height(T->lchild), Height(T->rchild)) + 1;//�߶Ⱥ�ƽ�����ӵĸ���
	T->bf = Height(T->lchild) - Height(T->rchild);

	return T;
}

Tree Delete(Tree T, int data)//ɾ���������Ƚϸ���
{                             //�Ȱ���һ��Ĳ��Ҷ��������ڵ�ɾ�������ɸýڵ����¶��ϵĻ��ݣ�����ÿ���ڵ㵽ƽ�������ڵ�
	Tree temp, target = T, parent = NULL, grand;
	int ele;

	while (target)//ɾ������
	{
		if (target->data < data)
			target = target->rchild;
		else if (target->data > data)
			target = target->lchild;
		else if (target->lchild && target->rchild)//�ҳ�ɾ���ڵ�
		{//�����������
			temp = FindMin(target->rchild);
			parent = temp->parent;//ע�������˳�����Ƕ�target���˴�����target����temp�ĸ�ĸ����ô��ʱparent����׼ȷ
			target->data = temp->data;
			//if (temp->rchild)//��С�ڵ��Ȼû��������
			//�ж�ɾ���ڵ����丸ĸ�����ң��������ֱ���
			if (temp->parent->data <= temp->data)//��������ע��Ⱥţ����ڴ�ʱtemp->parent��������target���ʿ��ܵ���
			{
				temp->parent->rchild = temp->rchild;
				if (temp->rchild)//ע��ָ�븸ĸ�ı仯
					temp->rchild->parent = temp->parent;
			}
			else //������
			{
				temp->parent->lchild = temp->rchild;
				if (temp->rchild)
					temp->rchild->parent = temp->parent;
			}

			free(temp);
			break;
		}
		else//ֻ��һ�����ӻ���û�к��ӣ���Ҷ�� 
		{
			temp = target;
			parent = temp->parent;
			if (target->lchild)//������
			if (parent->data < data)//�ж�ɾ���ڵ�λ���ڸ�ĸ�ڵ��������
			{
				parent->rchild = target->lchild;
				target->lchild->parent = parent;
			}
			else
			{
				parent->lchild = target->lchild;
				target->lchild->parent = parent;
			}
			else    //�����ж��Һ����Ƿ�Ϊ�գ�����Ϊ�գ����Ǻ��ӣ���ʱ����target->rchildҲ���ǵ���NULL
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

	while (parent)//��ɾ���ڵ����ϵ���ƽ��
	{
		ele = parent->data;
		parent->hight = MAX(Height(parent->lchild), Height(parent->rchild));//���¸߶Ⱥ�ƽ������
		parent->bf = Height(parent->lchild) - Height(parent->rchild);
		grand = parent->parent;
		if (parent->bf == -2)//���ֶ�Ӧ���������ڲ�����˵�����������������bf==0�����
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

		if (grand)//�游ĸ�����Ǳ���ģ������޷�����
		{
			if (grand->data > ele)//�ж�λ��
				grand->lchild = parent;
			else
				grand->rchild = parent;
			parent->parent = grand;
		}
		else
			T = parent;//ע�⣺��ʱ˵���Ѿ����˸��ڵ㣬��Ҫ�仯
		parent = parent->parent;//������
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