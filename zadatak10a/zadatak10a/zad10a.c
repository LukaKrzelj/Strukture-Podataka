#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "zad10a.h"

ListPosition CreateListElement(char* country)
{
	ListPosition newElement = NULL;

	newElement = (ListPosition)malloc(sizeof(List));
	if (!newElement)
	{
		perror("Could not allocate memory.\n");
		return NULL;
	}

	strcpy(newElement->countryName, country);
	newElement->next = NULL;
	newElement->root = NULL;

	return newElement;
}

ListPosition InsertSortedInList(ListPosition head, char* country)
{
	ListPosition temp = head;

	while (temp->next != NULL && strcmp(temp->next->countryName, country) < 0)
	{
		temp = temp->next;
	}

	InsertAfter(temp, country);

	return temp->next;
}

int InsertAfter(ListPosition previous, char* country)
{
	ListPosition newElement = NULL;

	newElement = CreateListElement(country);

	newElement->next = previous->next;
	previous->next = newElement;

	return EXIT_SUCCESS;
}

int ReadFile(char* fileName, ListPosition head)
{
	char buffer[MAX_LINE] = { 0 };
	char cityFile[MAX_SIZE] = { 0 };
	char country[MAX_SIZE] = { 0 };
	ListPosition newElement = NULL;
	FILE* file = NULL;
	

	file = fopen(fileName, "r");
	if (!file)
	{
		perror("Unable to open the file.\n");
		return -1;
	}

	while (!feof(file))
	{
		fgets(buffer, MAX_SIZE, file);

		if (sscanf(buffer, " %s %s", country, cityFile) == 2)
		{
			newElement = InsertSortedInList(head, country);

			newElement->root = ReadFileForTree(cityFile, newElement->root);
		}
	}
	fclose(file);

	return EXIT_SUCCESS;
}

int ReadFileForTree(char* fileName, BinPosition root)
{
	char buffer[MAX_LINE] = { 0 };
	FILE* cityFile = NULL;
	
	cityFile = fopen(fileName, "r");
	if (!cityFile)
	{
		perror("Unable to open the file.\n");
		return -1;
	}

	while (!feof(cityFile))
	{
		int population = 0;
		char cityName[MAX_SIZE] = { 0 };
		
		BinPosition newElement = NULL;

		fgets(buffer, MAX_LINE, cityFile);
		if (sscanf(buffer, " %s %d", cityName, population) == 2)
		{
			newElement = CreateTreeElement(cityName, population);
			root = InsertToTree(newElement, root);
		}
	}

}

BinPosition CreateTreeElement(char* cityName, int population)
{
	BinPosition newElement = NULL;

	newElement = (BinPosition)malloc(sizeof(BinaryTree));
	if (!newElement)
	{
		perror("Could not allocate memory.\n");
		return NULL;
	}

	strcpy(newElement->cityName, cityName);
	newElement->population = population;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

BinPosition InsertToTree(BinPosition newElement, BinPosition current)
{
	if (current == NULL)
	{
		return current;
	}
	else if (current->population < newElement->population)
	{
		current->right = InsertToTree(newElement, current->right);
	}
	else if (current->population < newElement->population)
	{
		current->left = InsertToTree(newElement, current->left);
	}
	else
	{
		if (strcmp(current->cityName, newElement->cityName) < 0)
		{
			current->right = InsertToTree(newElement, current->right);
		}
		else if (strcmp(current->cityName, newElement->cityName) < 0)
		{
			current->left = InsertToTree(newElement, current->left);
		}
	}

	return current;
}

int PrintList(ListPosition head)
{
	ListPosition temp = head->next;

	while (temp)
	{
		printf("Country: %s\nGradovi: ", temp->countryName);
		if (temp->root)
		{
			PrintTree(temp->root);
		}
		else
		{
			printf("No cities in that country.\n");
		}

		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int PrintTree(BinPosition current)
{
	if (current = NULL)
	{
		return EXIT_SUCCESS;
	}

	PrintTree(current->left);
	printf("%s\t%d\n", current->cityName, current->population);
	PrintTree(current->right);

	return EXIT_SUCCESS;
}