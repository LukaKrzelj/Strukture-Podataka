#ifndef ZAD_10B
#define ZAD_10B
#define MAX_LINE 1024
#define MAX_SIZE 128

struct _binTree;
typedef struct _binTree* BinPosition;
struct _list;
typedef struct _list* ListPosition;
typedef struct _binTree
{
	char countryName[MAX_SIZE];
	BinPosition left;
	BinPosition right;
	ListPosition head;
}BinaryTree;


typedef struct _list
{
	char cityName[MAX_SIZE];
	int population;
	ListPosition next;
}List;

int PrintList(ListPosition head);
int PrintTree(BinPosition current);
int ReadFile(char* fileName, ListPosition head);
BinPosition ReadFileForTree(char* fileName, BinPosition root);
BinPosition InsertToTree(BinPosition root, BinPosition newElement);
BinPosition CreateTreeElement(char* country);
int InsertAfter(ListPosition previous, ListPosition newElement);
int InsertInList(ListPosition head, ListPosition newElement);
ListPosition CreateListElement(char* city, int population);

#endif // !ZAD_10B

