#ifndef ZAD_10A
#define ZAD_10A
#define MAX_LINE 1024
#define MAX_SIZE 128
#define HASH_SIZE 11

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

struct _hash;
typedef struct _hash* HashPosition;
typedef struct _hash {
	List hashTable[HASH_SIZE];
}Hash;

ListPosition CreateListElement(char* country);
ListPosition InsertSortedInList(ListPosition head, char* country);
int InsertAfter(ListPosition previous, char* country);
int ReadFile(char* fileName, ListPosition head);
BinPosition ReadFileForTree(char* fileName, BinPosition root);
BinPosition CreateTreeElement(char* cityName, int population);
BinPosition InsertToTree(BinPosition newElement, BinPosition current);
int PrintList(ListPosition head);
int PrintTree(BinPosition current);
int FindCountry(ListPosition head, char* country, int population);
BinPosition FindCity(BinPosition current, int population);
int HashNumber(char* country);
int InitializeList(ListPosition head);
HashPosition CreateHashTable();

#endif // !ZAD_10A


