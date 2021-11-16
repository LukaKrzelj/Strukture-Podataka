#ifndef STACK_H
#define STACK_H

struct _StackElement;
typedef struct _StackElement* Position;
typedef struct _StackElement {
	double number;
	Position next;
}StackElement;

Position CreateElement(double number);
int InsertAfter(Position position, Position newElement);
int Push(Position head, double number);
int Pop(double* resultAdress, Position head);
int DeleteAfter(Position position);
int PerformOperation(Position head, char operation);
int CalculatePostfixFromFile(double* resultDestination, char* fileName);
int DeleteAll(Position head);

#endif // !STACK_H
