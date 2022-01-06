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

struct _list;
typedef struct _list* ListPointer;
typedef struct _list
{
	int number;
	ListPointer next;
}List;

Position CreateElement(int number);
Position Insert(int number, Position root);
int replace(Position root);
int Rand(Position root);
ListPointer CreateListElement(int number);
ListPointer FindLast(ListPointer head);
int InsertAfter(ListPointer after, ListPointer newElement);
int AppendList(ListPointer head, int number);
int PrintList(ListPointer first);
int InorderPrint(Position root, ListPointer head);
int WriteListToFile(ListPointer head, char* nameOfFile);


#endif // !BIN_H