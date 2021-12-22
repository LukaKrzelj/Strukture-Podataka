#define CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include "DOS.h"

int main(int argc, char** argv)
{
	Direktorij root = { .imeDirektorija = "C:", .child = NULL, .sibling = NULL};
	Stack head = { .dir = NULL, .next = NULL };

	Push(&head, &root);
	ChooseAction(&root, &head);

	return EXIT_SUCCESS;
}