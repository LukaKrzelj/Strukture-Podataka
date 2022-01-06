#define _CRT_SECURE_NO_WARNINGS

#include "binninth.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv)
{
	List head = { .next = 0, .next = NULL };
	Position root = NULL, temp = NULL;
	int i = 0, x = 0;
	int choice = 0, number = 0;
	char* name = '\0';

	root = Insert(2, root);
	root = Insert(5, root);
	root = Insert(7, root);
	root = Insert(8, root);
	root = Insert(11, root);
	root = Insert(1, root);
	root = Insert(4, root);
	root = Insert(2, root);
	root = Insert(3, root);
	root = Insert(7, root);

	replace(root);

	do 
	{
		printf("\nChoose your action:\n"
		"1) Add new element.\n"
		"2) Inorder print to file.\n"
		"3) Input random numbers in range from 10 to 90.\n"
		"4) Exit.\n");

		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("Enter the number you want to insert: ");
			scanf("%d", &number);
			root = Insert(number, root);
			break;

		case 2:
			InorderPrint(root, &head);
			PrintList(head.next);
			WriteListToFile(&head, "dat.txt");
			break;

		case 3:
			Rand(root);
			break;

		case 4:
			break;

		default:
			printf("Wrong input.\n");
		}
	} while (choice != 4);

	return EXIT_SUCCESS;
}