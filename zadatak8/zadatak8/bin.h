#ifndef BIN_H
#define BIN_H

struct _binTree;
typedef struct _binTree* Position;
typedef struct _binTree
{
	int number;
	Position left;
	Position right;
}Tree;

Position DeleteElement(int num, Position root);
Position FindElement(int num, Position root);
int FindMin(Position root);
int Postorder(Position root);
int Preorder(Position root);
int Inorder(Position root);
Position InsertElement(int number, Position root);
Position CreateElement(int number);
int Menu(Position root);
int Levelorder(Position root, int level);
int PrintLevelOrder(Position root);
int Depth(Position root);

#endif // !BIN_H
