#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


typedef struct tree
{
	int data;
	int height;			     // Define that: height of NULL is 0, height of leaves is 1
	int bf;                 //ƽ�����ӣ������߶ȼ�ȥ�����߶�
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

Tree SingleLeft(Tree k1)			//���������� 
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

Tree SingleRight(Tree k1)			//����������
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

Tree LeftRight(Tree k1)				//˫����������������
{
	k1->left = SingleLeft(k1->left);
	//��ʱK1->left ��height��bf�Ѹ��£�k1��height��bf��Ӧ�������¡�
	//������SingleRight(k1)���������k1��height��bf�ĸ��¹������ʴ˴���ʡ��
	return SingleRight(k1);
}

Tree RightLeft(Tree k1)				//˫���� ����--����
{
	k1->right = SingleRight(k1->right);
	return SingleLeft(k1);
}

/******************************************
Tree FindMin(Tree T)//�ҳ���С�ڵ�
{
	Tree temp = T;
	while (temp->left)
		temp = temp->left;
	return temp;
}
*******************************************/

Tree Insert(Tree T, int X)				//����,�߲������ת����ƽ��   ���ֶ�Ӧ��ϵ
{                                      
	if (!T)
	{
		T = (Tree)malloc(sizeof(Node));  // �����½��or��ʼ�����ڵ�
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
				if (X < T->right->data)			//RL�Σ���ҪRightLeft��ת
					T = RightLeft(T);
				else if (X > T->right->data)	//RR�Σ���ҪSingleLeft��ת
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
				if (X < T->left->data)			//LL�Σ���ҪSingleRight��ת
					T = SingleRight(T);
				else if (X > T->left->data)     //LR��ʽ����ҪLeftRight��ת
					T = LeftRight(T);
			}
		}
	}

	return T;
}


/********************************************************************************************
Tree Delete(Tree T, int X)//ɾ���������Ƚϸ���
{                             //�Ȱ���һ��Ĳ��Ҷ��������ڵ�ɾ�������ɸýڵ����¶��ϵĻ��ݣ�����ÿ���ڵ㵽ƽ�������ڵ�
	Tree temp, target = T, parent = NULL, grand;
	int ele;

	while (target)//ɾ������
	{
		if (target->data < X)
			target = target->right;
		else if (target->data > X)
			target = target->left;
		else if (target->left && target->right)//�ҳ�ɾ���ڵ�
		{//�����������
			temp = FindMin(target->right);
			parent = temp->parent;//ע�������˳�����Ƕ�target���˴�����target����temp�ĸ�ĸ����ô��ʱparent����׼ȷ
			target->data = temp->data;
			//if (temp->right)//��С�ڵ��Ȼû��������
			//�ж�ɾ���ڵ����丸ĸ�����ң��������ֱ���
			if (temp->parent->data <= temp->data)//��������ע��Ⱥţ����ڴ�ʱtemp->parent��������target���ʿ��ܵ���
			{
				temp->parent->right = temp->right;
				if (temp->right)//ע��ָ�븸ĸ�ı仯
					temp->right->parent = temp->parent;
			}
			else //������
			{
				temp->parent->left = temp->right;
				if (temp->right)
					temp->right->parent = temp->parent;
			}

			free(temp);
			break;
		}
		else//ֻ��һ�����ӻ���û�к��ӣ���Ҷ�� 
		{
			temp = target;
			parent = temp->parent;
			if (target->left)//������
			if (parent->data < X)//�ж�ɾ���ڵ�λ���ڸ�ĸ�ڵ��������
			{
				parent->right = target->left;
				target->left->parent = parent;
			}
			else
			{
				parent->left = target->left;
				target->left->parent = parent;
			}
			else    //�����ж��Һ����Ƿ�Ϊ�գ�����Ϊ�գ����Ǻ��ӣ���ʱ����target->rightҲ���ǵ���NULL
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

	while (parent)//��ɾ���ڵ����ϵ���ƽ��
	{
		ele = parent->data;
		heightUpdate(T);
		bfUpdate(T);
		grand = parent->parent;
		if (parent->bf == -2)//���ֶ�Ӧ���������ڲ�����˵�����������������bf==0�����
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

		if (grand)//�游ĸ�����Ǳ���ģ������޷�����
		{
			if (grand->data > ele)//�ж�λ��
				grand->left = parent;
			else
				grand->right = parent;
			parent->parent = grand;
		}
		else
			T = parent;//ע�⣺��ʱ˵���Ѿ����˸��ڵ㣬��Ҫ�仯
		parent = parent->parent;//������
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
