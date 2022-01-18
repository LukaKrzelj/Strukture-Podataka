#define _CRT_SECURE_NO_WARNINGS

#include "bin.h"
#include<stdio.h>
#include<stdlib.h>

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

Position InsertElement(int number, Position root)
{
	if (!root)
	{
		return CreateElement(number);
	}
	else if (root->number > number)
	{
		root->left = InsertElement(number, root->left);
	}
	else if (root->number < number)
	{
		root->right = InsertElement(number, root->right);
	}
	else
	{
		printf("That number is already in binary tree!\n");
		return root;
	}
	return root;
}

int Inorder(Position root)
{
	if (root)
	{
		Inorder(root->left);
		printf("%d", root->number);
		Inorder(root->right);
	}
	printf("\n");

	return EXIT_SUCCESS;
}

int Preorder(Position root)
{
	if (root)
	{	
		printf("%d", root->number);
		Preorder(root->left);
		Preorder(root->right);
	}
	printf("\n");

	return EXIT_SUCCESS;
}

int Postorder(Position root)
{
	if (root)
	{
		Postorder(root->left);
		Postorder(root->right);
		printf("%d", root->number);
	}
	printf("\n");

	return EXIT_SUCCESS;
}

int FindMin(Position root)
{
	if (root->left != NULL)
		return FindMin(root->left);

	return root;
}

Position FindElement(int num, Position root)
{
	if (!root)
	{
		printf("There is no such number!\n");
		return NULL;
	}
	else if (root->number < num)
	{
		return FindElement(num, root->right);
	}
	else if (root->number > num)
	{
		return FindElement(num, root->left);
	}
	else
		return root;
}

Position DeleteElement(int num, Position root)
{
	Position temp = NULL;
	if (!root)
		return root;
	else if (root->number > num)
	{
		root->left = DeleteElement(num, root->left);
	}
	else if (root->number < num)
	{
		root->right = DeleteElement(num, root->right);
	}
	else
	{
		if (root->left && root->right)
		{
			temp = FindMin(root->right);
			root->number = temp->number;
			root->right = DeleteElement(temp->number, root->right);
		}
		else
		{
			temp = root;
			if (!root->left)
			{
				root = root->right;
			}
			else if (!root->right)
			{
				root = root->left;
			}
				
			free(temp);
		}
	}

	return root;
}

int Menu(Position root)
{
	int action = 0, number = 0;
	Position temp = NULL;

	do
	{
		printf("Choose your action:\n"
		"1) Add a new number.\n"
		"2) Delete a number.\n"
		"3) Inorder printing.\n"
		"4) Preorder printing.\n"
		"5) Postorder printing.\n"
		"6) Find a number.\n"
		"7) Exit.\n"
		"8) Levelorder printing.\n");

		scanf("%d", &action);

		if (action < 1 || action > 8)
		{
			printf("Wrong number. Try again!\n");
		}
		else if (action == 1)
		{
			printf("Enter the number you want to insert: ");
			scanf("%d", &number);
			root = InsertElement(number, root);
		}
		else if (action == 2)
		{
			printf("Enter the number you want to delete: ");
			scanf("%d", &number);
			root = DeleteElement(number, root);
		}
		else if (action == 3)
		{
			Inorder(root);
		}
		else if (action == 4)
		{
			Preorder(root);
		}
		else if (action == 5)
		{
			Postorder(root);
		}
		else if (action == 6)
		{
			printf("Enter the number you want to search for: ");
			scanf("%d", &number);
			temp = FindElement(number, root);
			if (temp)
			{
				printf("Number %d is on adress %d.\n", temp->number, temp);
			}
		}
		else if (action == 8)
		{
			PrintLevelOrder(root);
		}
		else
			return EXIT_SUCCESS;
	} while (action != 7);

	return EXIT_SUCCESS;
}

int Levelorder(Position root, int level)
{
	if (!root)
	{
		return -1;
	}
	else if (level == 0)
	{
		printf("%d ", root->number);
	}
	else if (level > 0)
	{
		Levelorder(root->left, level - 1);
		Levelorder(root->right, level - 1);
	}

	return EXIT_SUCCESS;
}

int PrintLevelOrder(Position root)
{
	int level = 0;

	for (level = 0; level <= Depth(root); level++)
	{
		Levelorder(root, level);
	}

	return EXIT_SUCCESS;
}

int Depth(Position root)
{
	int lDepth = 0, rDepth = 0;

	if (!root)
	{
		return -1;
	}

	lDepth = Depth(root->left);
	rDepth = Depth(root->right);

	if (lDepth > rDepth)
	{
		return lDepth + 1;
	}
	else
	{
		return rDepth + 1;
	}
}