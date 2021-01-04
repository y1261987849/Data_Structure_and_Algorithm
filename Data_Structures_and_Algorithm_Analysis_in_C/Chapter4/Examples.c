//树的实现
typedef struct TreeNode *PtrToNode;
struct TreeNode
{
	ElementType Element;
	PtrToNode FirstChild;
	PtrToNode NextSibling;
};

//列出分级文件系统中目录的例程 -> 树的先序遍历
static void ListDir(DirectoryOrFile D, int Depth)
{
	if(D is a legitimate entry)
	{
		PrintName(D, Depth);
		if(D is a directory)
		{
			for each child -> C of D
				ListDir(C, Depth + 1);
		}
	}
}

void ListDirectory(DirectoryOrFile D)
{
	ListDir(D, 0);
}

//计算一个目录大小的例程 -> 树的后序遍历
static int SizeDirectory(DirectoryOrFile D)
{
	int TotalSize;

	TotalSize = 0;
	if(D is a legitimate entry)
	{
		TotalSize = FileSize(D);
		if(D is a directory)
		{
			for each child -> C of D
				TotalSize += SizeDirectory(C);
		}
	}
	return TotalSize;
}

//二叉树的实现
typedef struct TreeNode *PtrToNode;
typedef struct PtrToNode Tree;
struct TreeNode
{
	ElementType Element;
	Tree Left;
	Tree Right;
}

//二叉查找树的声明
#ifndef _Tree_H

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty(SearchTree T) //初始化
{
	if(T != NULL)
	{
		MakeEmpty(T -> Left);
		MakeEmpty(T -> Right);
		free(T);
	}
	return NULL;
}

Position Find(ElementType X, SearchTree T) //返回树T中具有关键字X的结点的指针，如果这样的结点不存在则返回NULL
{
	if(T == NULL)
	{
		return NULL;
	}
	if(X < T -> Element)
	{
		return Find(X, T -> Left);
	}
	else
	{
		if(X > T -> Element)
		{
			return Find(X, T -> Right);
		}
		else
		{
			return T;
		}
	}
}

//分别返回树中最小元和最大元的位置(递归实现)
Position FinMin(SearchTree T)
{
	if(T == NULL)
	{
		return NULL;
	}
	else
	{
		if(T -> Left == NULL)
		{
			return T;
		}
		else
		{
			return FindMin(T -> Left);
		}
	}
}

Position FinMax(SearchTree T)
{
	if(T == NULL)
	{
		return NULL;
	}
	else
	{
		if(T -> Right == NULL)
		{
			return T;
		}
		else
		{
			return FindMax(T -> Right);
		}
	}

}

/*

FindMax的非递归实现

Position FindMax(SearchTree T)
{
	if(T != NULL)
	{
		while(T -> Right != NULL)
		{
			T = T -> Right;
		}
	}
	return T;
}
*/

SearchTree Insert(ElementType X, SearchTree T)
{
	if(T == NULL)
	{
		/*Create and return a one-node tree*/

		T = malloc(sizeof(struct TreeNode));
		if(T == NULL)
		{
			FatalError("Out of space!!!");
		}
		else
		{
			T -> Element = X;
			T -> Left = T -> Right = NULL;
		}
	}
	else
	{
		if(X < Element)
		{
			T -> Left = Insert(X, T -> Left);
		}
		else if(X > T -> Element)
		{
			T -> Right = Insert(X, T -> Right);
		}
		/*Else X is in the tree already; we'll do nothing*/
	}
	return T;
}

SearchTree Delete(ElementType X, SearchTree T)
{
	Position TmpCell;
	if(T == NULL)
	{
		Error("Element not found");
	}
	else if(X < Element) /* Go left */
		T -> Left = Delete(X, T -> Left);
	else if(X > Element)
		T -> Right = Delete(X, T -> Right);
	else /* Found element to be deleted */
	if(T -> Left && T -> Right) /* Two children */
	{
		TmpCell = Findmin(T -> Right);
		T -> Element = TmpCell -> Element;
		T -> Right = Delete(T -> Element, T -> Right);
	}
	else /* One or Zero children */
	{
		TmpCell = T;
		if(T -> Left == NULL)
			T = T -> Right;
		else if(T -> Right == NULL)
			T = T -> Left;
		free(TmpCell);
	}
	return T;
}
ElementType Retrieve(Position P);

#endif

/*Place in the implementation file*/
struct TreeNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
}


//AVL树
#ifndef _AvlTree_H

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType X, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType X, AvlTree T)
{
	if(T == NULL)
	{
		T = malloc(sizeof(struct AvlNode));
		if(T == NULL)
			FatalError("Out of space!!!");
		else
		{
			T -> Element = X;
			T -> Height = 0;
			T -> Left = T -> Right = 0;
		}
	}
	else if(X < T -> Element)
	{
		T -> Left = Insert(T -> Left);
		if(Height(T -> Left) - Height(T -> Right) == 2)
		{
			if(X < T -> Left -> Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else if(X > Element)
	{
		T -> Right = Insert(X, T -> Right);
		if(Height(T -> Right) - Height(T -> Left) == 2)
		{
			if(X > T -> Right -> Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWihtRight(T);
		}
	}
	/* Else X is in the tree already; we'll do nothing */
	T -> Height = Max(Height(T -> Left), Height(T -> Right)) + 1;
	return T;
}

AvlTree Delete(ElementTypeX, AvlTree T);
ElementType Retrieve(Position P);

#endif

/*Place in the implementation file*/
struct AvlNode
{
	ElementType Element;
	AvlTree Left;
	AvlTree Right;
	int Height;
}

static int Height(Position P) //计算AVL节点的高度的函数
{
	if(P == NULL)
		return -1;
	else
		return P -> Height;
}

//对K2的左儿子的左子树进行一次插入导致的不平衡
static Position SingleRotateWithLeft(Position K2)
{
	Position K1;

	K1 = K2 -> Left; //K1为K2的左儿子
	K2 -> Left = K1 -> Right;
	K1 -> Right = K2;

	K2 -> Height = Max(Height(K2 -> Left), Height(K2 -> Right)) + 1;
	K1 -> Height = Max(Height(K1 -> Left), Height(K2 -> Height)) + 1;
	return K1; /* New root*/
}

//对K3的左儿子的右子树进行一次插入导致的不平衡
static Position DoubleRotateWithLeft(Position K3)
{
	K3 -> Left = SingleRotateWithRight(K3 -> Left);

	return SingleRotateWithLeft(K3);
}

//按顺序打印二叉查找树的例程
void PrintTree(SearchTree T)
{
	if(T != NULL)
	{
		PrintTree(T -> Left);
		PrintElement(T -> Element);
		PrintTree(T -> Right);
	}
}

//使用后序遍历计算树的高度的例程
int Height(Tree T)
{
	if(T == NULL)
		return -1;
	else
		return 1 + Max(Height(T -> Left), Height(T -> Right));
}
























