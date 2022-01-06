#define _CRT_SECURE_NO_WARNINGS

#include "binninth.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

Position CreateElement(int number)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(Tree));
	if (!newElement)
	{
		perror("Could not allocate memory!\n");
		return NULL;
	}

	newElement->number = number;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

Position Insert(int number, Position root)
{
	if (!root)
	{
		return CreateElement(number);
	}
	else if (root->number > number)
	{
		root->right = Insert(number, root->right);
	}
	else if (root->number < number)
	{
		root->left = Insert(number, root->left);
	}

	return root;
}

int replace(Position root)
{
	int number = 0;

	if (root == NULL)
	{
		return EXIT_SUCCESS;
	}
	else if (root->left != NULL && root->right != NULL)
	{
		number = root->number;
		root->number = replace(root->left) + replace(root->right);
		return root->number + number;
	}
	else if (root->left == NULL)
	{
		number = root->number;
		root->number = replace(root->right);
		return root->number + number;
	}
	else if (root->right == NULL)
	{
		number = root->number;
		root->number = replace(root->left);
		return root->number + number;
	}
	else
	{
		number = root->number;
		root->number = 0;
		return root->number;
	}
}

int Rand(Position root)
{
	srand((unsigned)time(NULL));
	int number = 0;
	
	number = (rand() % (90 - 10 + 1)) + 10;
	printf("Random element is %d.\n", number);
	root = Insert(number, root);

	return EXIT_SUCCESS;
}

ListPointer CreateListElement(int number)
{
	ListPointer newElement = NULL;

	newElement = (ListPointer)malloc(sizeof(List));
	if (!newElement)
	{
		perror("Could not allocate memory.\n");
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}

ListPointer FindLast(ListPointer head)
{
	ListPointer temp = NULL;
	temp = head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}

int InsertAfter(ListPointer after, ListPointer newElement)
{
	newElement->next = after->next;
	after->next = newElement;

	return EXIT_SUCCESS;
}

int AppendList(ListPointer head, int number)
{
	ListPointer newElement = NULL, last = NULL;

	newElement = CreateListElement(number);
	if (!newElement)
	{
		return -1;
	}

	last = FindLast(head);
	InsertAfter(last, newElement);

	return EXIT_SUCCESS;
}

int PrintList(ListPointer first)
{
	ListPointer temp = first;

	while (temp)
	{
		printf("%d ", temp->number);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int InorderPrint(Position root, ListPointer head)
{
	if (root)
	{
		InorderPrint(root->left, head);
		AppendList(head, root->number);
		InorderPrint(root->right, head);
	}

	return EXIT_SUCCESS;
}

int WriteListToFile(ListPointer head, char* nameOfFile)
{
	ListPointer temp = head->next;
	FILE* fp = NULL;
	
	fp = fopen(nameOfFile, "a");
	if (!fp)
	{
		perror("Could not open the file!\n");
		return -1;
	}

	while (temp != NULL)
	{
		fprintf(fp, "%d ", temp->number);
		temp = temp->next;
	}
	fclose(fp);
	
	return EXIT_SUCCESS;
}