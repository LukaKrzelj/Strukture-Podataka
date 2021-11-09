#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#define MAX_LINE (1024)
#define MAX_SIZE (128)

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	int coefficient;
	int exponent;
	Position next;
}Element;

int FillOutFileName(char* nameOfFile);
int ReadFile(Position head1, Position head2, char* fileName);
int ParseStringIntoList(Position head, char* buff);
Position CreateElement(int coeff, int exp);
int InsertSorted(Position head, Position newElement);
int MergeAfter(Position mergeAfter, Position newElement);
int InsertAfter(Position insertAfter, Position newElement);
int DeleteAfter(Position toDeleteAfter);
int PrintPoly(char* name, Position head);
int AddPoly(Position head1, Position head2, Position Add);
int CreateAndInsertAfter(int coeff, int exp, Position position);
int MultiplyPoly(Position head1, Position head2, Position Multiply);
int FreeMemory(Position head);

#endif !POLYNOMIAL_H
