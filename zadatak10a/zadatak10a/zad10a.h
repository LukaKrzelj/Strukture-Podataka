#ifndef ZAD_10A
#define ZAD_10A
#define MAX_LINE 1024
#define MAX_SIZE 128

struct _binTree;
typedef struct _binTree* BinPosition;
typedef struct _binTree
{
	char cityName[MAX_SIZE];
	int population;
	BinPosition left;
	BinPosition right;
}BinaryTree;

struct _list;
typedef struct _list* ListPosition;
typedef struct _list
{
	char countryName[MAX_SIZE];
	ListPosition next;
	BinPosition root;
}List;

ListPosition CreateListElement(char* country);
ListPosition InsertSortedInList(ListPosition head, char* country);
int InsertAfter(ListPosition previous, char* country);
int ReadFile(char* fileName, ListPosition head);
int ReadFileForTree(char* fileName, BinPosition root);
BinPosition CreateTreeElement(char* cityName, int population);
BinPosition InsertToTree(BinPosition newElement, BinPosition current);
int PrintList(ListPosition head);
int PrintTree(BinPosition current);

#endif // !ZAD_10A

