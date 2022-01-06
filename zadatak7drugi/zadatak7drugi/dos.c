#pragma warning(disable : 4996)

#include "DOS.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Position md(char* ime, Position current)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(Direktorij));
	if (!newElement)
	{
		perror("Could not allocate memory.\n");
		return NULL;
	}
	strcpy(newElement->imeDirektorija, ime);
	newElement->child = NULL;
	newElement->sibling = NULL;

	current->child = Insert(current->child, newElement);

	return newElement;
}

Position Insert(Position current, Position q)
{
	if (current == NULL)
	{
		return q;
	}
	if (strcmp(current->imeDirektorija, q->imeDirektorija) > 0)
	{
		q->sibling = current;
		return q;
	}
	else if (strcmp(current->imeDirektorija, q->imeDirektorija) < 0)
	{
		current->sibling = Insert(current->sibling, q);
	}
	else
	{
		perror("A subdirectory or file %s already exists.\n", q->child);
		free(q);
	}
	return current;
}

PositionStack FindLast(PositionStack head)
{
	PositionStack temp = head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}

PositionStack FindBefore(PositionStack head)
{
	PositionStack temp = head;

	while (temp->next->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}


int Push(PositionStack head, Position dir)
{
	PositionStack newElement = NULL;
	newElement = (PositionStack)malloc(sizeof(Stack));
	if (!newElement)
	{
		perror("Could not allocate memory.\n");
		return NULL;
	}
	PositionStack last = FindLast(head);

	newElement->next = last->next;
	last->next = newElement;
	newElement->dir = dir;

	return EXIT_SUCCESS;
}

Position Pop(PositionStack head)
{
	if (!head->next)
	{
		return NULL;
	}

	PositionStack previous = FindBefore(head);
	PositionStack delete = previous->next;
	Position temp = delete->dir;

	previous->next = delete->next;
	free(delete);

	return previous->dir;
}

Position cddir(PositionStack head, Position current, char* imeDirektorija)
{
	if (current->child == NULL)
	{
		perror("The system cannot find the path specified.\n");
		return current;
	}
	else
	{
		Position temp = current->child;
		while (temp != NULL && strcmp(temp->imeDirektorija, imeDirektorija) != 0)
		{
			temp = temp->sibling;
		}

		if (temp == NULL)
		{
			perror("The system cannot find the path specified.\n");
			return current;
		}
		else
		{
			Push(head, current->child);
			return current->child;
		}
	}
}

int izlaz(Position current)
{
	if (current == NULL)
	{
		return EXIT_SUCCESS;
	}

	izlaz(current->sibling);
	izlaz(current->child);
	izlaz(current->sibling);

	return EXIT_SUCCESS;
}

int Print(PositionStack head)
{
	PositionStack temp = head->next;
	char line[MAX_LINE] = { 0 };

	while (temp != NULL)
	{
		strcat(line, temp->dir->imeDirektorija);
		strcat(line, "\\");
		temp = temp->next;
	}
	strcat(line, ">");

	printf("%s", line);

	return EXIT_SUCCESS;
}

int dir(Position current)
{
	if (current->child == NULL)
	{
		printf("Directory is empty.\n");
		return EXIT_SUCCESS;
	}
	else
	{
		Position temp = current->child;
		while (temp != NULL)
		{
			printf("<DIR>\t\t%s\n", temp->imeDirektorija);
			temp = temp->sibling;
		}
	}

	return EXIT_SUCCESS;
}

int ChooseAction(Position current, PositionStack head)
{
	Position first = current;
	char imeDirektorija[MAX_SIZE] = { 0 };
	char command[MAX_LINE] = { 0 };
	char line[MAX_LINE] = { 0 };
	Print(head);

	while (!0)
	{
		fgets(line, MAX_LINE, stdin);
		sscanf(line, "%s %s", command, imeDirektorija);

		if (strcmp(command, "md") == 0)
		{
			md(imeDirektorija, current);
			Print(head);
		}
		else if (strcmp(command, "cd") == 0 && strcmp(imeDirektorija, "..") != 0)
		{
			current = cddir(head, current, imeDirektorija);
			Print(head);
		}
		else if (strcmp(command, "cd") == 0 && strcmp(imeDirektorija, "..") == 0)
		{
			current = Pop(head);
			Print(head);
		}
		else if (strcmp(command, "dir") == 0)
		{
			dir(current);
			Print(head);
		}
		else if (strcmp(command, "exit") == 0)
		{
			izlaz(current);
			return EXIT_SUCCESS;
		}
		else
		{
			Print(head);
		}
	}

	return EXIT_SUCCESS;
}