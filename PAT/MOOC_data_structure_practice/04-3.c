#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct HeapStruct * MinHeap;
typedef struct ElementType * Node;
typedef struct HuffmanTree * TreeNode;
struct HuffmanTree {
	char Character;
	int Weight;
	int Height;
	TreeNode LeftChild;
	TreeNode RightChild;
};
struct ElementType {
	char Character;
	int Weight;
	TreeNode NodeAddress;
};
struct HeapStruct {
	struct ElementType * Elements;
	int CurrentSize;
	int Capacity;
};

MinHeap Create(int);
bool IsFull(MinHeap);
bool IsEmpty(MinHeap);
void Insert(MinHeap, Node);
struct ElementType Delete(MinHeap);
void PrintHeap(MinHeap);
TreeNode CreateHuffmanTree(MinHeap);
void PrintHuffmanTree(TreeNode);
int CalculateWPL(TreeNode, int);
int EvaluateTheAnswer(int, int, Node);

int main(void) {
	int MaxSize, index, WPL, NumberOfStudents, Result;
	MinHeap Heap;
	struct ElementType Input;
	Node Backup;
	TreeNode Root;

	scanf("%d", &MaxSize);
	getchar();
	if(MaxSize == 0)
		return 0;
	Heap = Create(MaxSize);
	Backup = calloc(MaxSize, sizeof(struct ElementType));
	for(index = 0; index < MaxSize; index++) {
		scanf("%c %d", &(Input.Character), &(Input.Weight));
		getchar();
		Backup[index].Character = Input.Character;
		Backup[index].Weight = Input.Weight;
		Insert(Heap, &Input);
//		PrintHeap(Heap);
	}
	PrintHeap(Heap);
	Root = CreateHuffmanTree(Heap);
	WPL = CalculateWPL(Root, 0);
//	printf("WPL: %d\n", WPL);
//	PrintHuffmanTree(Root);
	scanf("%d", &NumberOfStudents);
	getchar();
	for(index = 0; index < NumberOfStudents; index++) {
		Result = EvaluateTheAnswer(MaxSize, WPL, Backup);
		if(Result != 0)
			printf("No\n");
		else
			printf("Yes\n");
	}
	system("pause");
	return 0;
}

MinHeap Create(int MaxSize) {
	MinHeap Heap;

	Heap = calloc(1, sizeof(struct HeapStruct));
	Heap->Elements = calloc(MaxSize + 1, sizeof(struct ElementType));
	Heap->Capacity = MaxSize;

	return Heap;
}

bool IsFull(MinHeap Heap) {
	return Heap->CurrentSize < Heap->Capacity ? false : true;
}

bool IsEmpty(MinHeap Heap) {
	return Heap->CurrentSize == 0 ? true : false;
}

void Insert(MinHeap Heap, Node NewNode) {
	int i;

	if(IsFull(Heap)) {
		printf("Heap Element Insert Error: Already Full!\n");
		return;
	}
	Heap->CurrentSize++;
	for(i = Heap->CurrentSize; Heap->Elements[i/2].Weight > NewNode->Weight; i=i/2) {
		Heap->Elements[i] = Heap->Elements[i/2];
	}
	Heap->Elements[i] = *NewNode;

	return;
}

struct ElementType Delete(MinHeap Heap) {
	int Parent, Child;
	struct ElementType MinItem = {-1, -1 ,0}, temp;

	if(IsEmpty(Heap)) {
		printf("Heap Element Delete Error: Empty!\n");
		return MinItem;
	}

	MinItem = Heap->Elements[1];
	temp = Heap->Elements[Heap->CurrentSize--];
	for(Parent = 1; Parent * 2 <= Heap->CurrentSize; Parent = Child) {
		Child = Parent * 2;
		if((Child != Heap->CurrentSize) && Heap->Elements[Child].Weight > Heap->Elements[Child + 1].Weight)
			Child++;
		if(temp.Weight <= Heap->Elements[Child].Weight)
			break;
		else
			Heap->Elements[Parent] = Heap->Elements[Child];
	}
	Heap->Elements[Parent] = temp;
	return MinItem;
}

void PrintHeap(MinHeap Heap) {
	int i;

	for(i = 1; i <= Heap->CurrentSize; i++) {
		printf("%c %d ", Heap->Elements[i].Character, Heap->Elements[i].Weight);
	}
	printf("\n");

	return;
}

TreeNode CreateHuffmanTree(MinHeap Heap) {
	struct ElementType Node1, Node2, NewNode;
	TreeNode TreeNode1, TreeNode2, Parent;

	Parent = NULL;
	if(Heap->CurrentSize == 1) {
		Node1 = Delete(Heap);
		Parent = (TreeNode)calloc(1, sizeof(struct HuffmanTree));
		Node1.NodeAddress = Parent;
		Parent->Weight = Node1.Weight;
		Parent->Character = Node1.Character;
		Insert(Heap, &Node1);
	}

	while(Heap->CurrentSize > 1) {
		Node1 = Delete(Heap);
		Node2 = Delete(Heap);

		if(Node1.NodeAddress == NULL) {
			TreeNode1 = (TreeNode)calloc(1, sizeof(struct HuffmanTree));
			Node1.NodeAddress = TreeNode1;
			TreeNode1->Character = Node1.Character;
			TreeNode1->Weight = Node1.Weight;
		} else {
			TreeNode1 = Node1.NodeAddress;
		}

		if(Node2.NodeAddress == NULL) {
			TreeNode2 = (TreeNode)calloc(1, sizeof(struct HuffmanTree));
			Node2.NodeAddress = TreeNode2;
			TreeNode2->Character = Node2.Character;
			TreeNode2->Weight = Node2.Weight;
		} else {
			TreeNode2 = Node2.NodeAddress;
		}

		Parent = (TreeNode)calloc(1, sizeof(struct HuffmanTree));
		Parent->Weight = TreeNode1->Weight + TreeNode2->Weight;
		Parent->LeftChild = TreeNode1;
		Parent->RightChild = TreeNode2;

		NewNode.Weight = Node1.Weight + Node2.Weight;
		NewNode.NodeAddress = Parent;
		Insert(Heap, &NewNode);
//		printf("%c %d %c %d | ", Node1.Character, Node1.Weight, Node2.Character, Node2.Weight);
//		PrintHeap(Heap);
	}

	return Parent;
}

void PrintHuffmanTree(TreeNode CurrentNode) {
	if(CurrentNode == NULL)
		return;
	printf("Node:   %c\n", CurrentNode->Character);
	printf("Weight: %d\n", CurrentNode->Weight);
	printf("Height: %d\n", CurrentNode->Height);
	if(CurrentNode->LeftChild != NULL) {
		printf("Left:   %c\n", CurrentNode->LeftChild->Character);
	}
	if(CurrentNode->RightChild != NULL) {
		printf("Right:  %c\n", CurrentNode->RightChild->Character);
	}
	PrintHuffmanTree(CurrentNode->LeftChild);
	PrintHuffmanTree(CurrentNode->RightChild);
	return;
}

int CalculateWPL(TreeNode CurrentNode, int Height) {
	CurrentNode->Height = Height;
	if(CurrentNode->LeftChild == NULL && CurrentNode->RightChild == NULL)
		return CurrentNode->Weight * Height;
	else if(CurrentNode->LeftChild != NULL && CurrentNode->RightChild != NULL)
		return CalculateWPL(CurrentNode->LeftChild, Height + 1) + CalculateWPL(CurrentNode->RightChild, Height + 1);
	else if(CurrentNode->LeftChild != NULL)
		return CalculateWPL(CurrentNode->LeftChild, Height + 1);
	else
		return CalculateWPL(CurrentNode->RightChild, Height + 1);
}

int EvaluateTheAnswer(int MaxSize, int SampleWPL, Node Backup) {
	char Character, Code;
	int i, j, WPL, Weight;
	TreeNode Root, CurrentNode, NewNode;

	Root = (TreeNode)calloc(1, sizeof(struct HuffmanTree));
	for(i = 0; i < MaxSize; i++) {
		CurrentNode = Root;
		Character = getchar();
		getchar();
		while((Code = getchar()) != '\n') {
			if(CurrentNode->Character != 0)
				return 1;
			if(Code == '0') {
				if(CurrentNode->LeftChild == NULL) {
					NewNode = (TreeNode)calloc(1, sizeof(struct HuffmanTree));
					CurrentNode->LeftChild = NewNode;
				}
				CurrentNode = CurrentNode->LeftChild;
			} else if(Code == '1') {
				if(CurrentNode->RightChild == NULL) {
					NewNode = (TreeNode)calloc(1, sizeof(struct HuffmanTree));
					CurrentNode->RightChild = NewNode;
				}
				CurrentNode = CurrentNode->RightChild;
			} else {
				printf("Error : Invalid Input!\n");
			}
		}
		CurrentNode->Character = Character;
		for(j = 0; j < MaxSize; j++) {
			if(Backup[j].Character != Character)
				continue;
			else
				break;
		}
		if(j == MaxSize)
			printf("Error : Character Not Found!\n");
		CurrentNode->Weight = Backup[j].Weight;
	}
	WPL = CalculateWPL(Root, 0);
//	PrintHuffmanTree(Root);
//	printf("WPL of Student's Answer is %d\n", WPL);
	if(WPL != SampleWPL)
		return 2;
	return 0;
}