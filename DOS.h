#ifndef DOS_H
#define DOS_H
#define MAX_SIZE (128)
#define MAX_LINE (1024)

struct _Direktorij;
typedef struct _Direktorij* Position;
typedef struct _Direktorij
{
	char imeDirektorija[MAX_SIZE];
	Position sibling;
	Position child;
}Direktorij;

struct _Stack;
typedef struct _Stack* PositionStack;
typedef struct _Stack
{
	Position dir;
	PositionStack next;
}Stack;

Position md(char* ime);
Position Insert(Position current, Position q);
int Push(PositionStack head, Position dir);
PositionStack FindLast(PositionStack head);
Position Pop(PositionStack head);
PositionStack FindBefore(PositionStack head);
Position cddir(PositionStack head, Position current, char* imeDirektorija);
int izlaz(Position current);
int Print(PositionStack head);
int dir(Position current);
int ChooseAction(Position current, PositionStack head);

#endif // !DOS_H

