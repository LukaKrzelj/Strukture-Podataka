#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "zad10b.h"

ListPosition CreateListElement(char* city, int population)
{
	ListPosition newElement = NULL;

	newElement = (ListPosition)malloc(sizeof(List));
	if (!newElement)
	{
		perror("Could not allocate memory.\n");
		return NULL;
	}

	strcpy(newElement->cityName, city);
	newElement->population = population;
	newElement->next = NULL;

	return newElement;
}

int InsertInList(ListPosition head, ListPosition newElement)
{
	ListPosition temp = NULL;
	temp = head;

	if (temp->next == NULL)
	{
		InsertAfter(temp, newElement);
		return EXIT_SUCCESS;
	}

	while (temp->next != NULL && temp->next->population > newElement->population)
	{
		temp = temp->next;
	}
	
	InsertAfter(temp, newElement);
}

int InsertAfter(ListPosition previous, ListPosition newElement)
{
	newElement->next = previous->next;
	previous->next = newElement;

	return EXIT_SUCCESS;
}

BinPosition CreateTreeElement(char* country)
{
	BinPosition newElement = NULL;
	
	newElement = (BinPosition)malloc(sizeof(BinaryTree));
	if (!newElement)
	{
		perror("Could not allocate memory.\n");
		return NULL;
	}

	strcpy(newElement->countryName, country);
	newElement->head = (ListPosition)malloc(sizeof(List));
	if (!newElement->head)
	{
		perror("Could not allocate memory.\n");
		return NULL;
	}
	newElement->head->next = NULL;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

BinPosition InsertToTree(BinPosition root, BinPosition newElement)
{
	if (root == NULL)
	{
		return newElement;
	}
	else if (strcmp(root->countryName, newElement->countryName) > 0)
	{
		root->left = InsertToTree(root->left, newElement);
	}
	else if (strcmp(root->countryName, newElement->countryName) < 0)
	{
		root->right = InsertToTree(root->right, newElement);
	}
	else
	{
		free(newElement);
	}

	return root;
}

BinPosition ReadFileForTree(char* fileName, BinPosition root)
{
	char buffer[MAX_LINE] = { 0 };
	FILE* countryFile = NULL;
	char country[MAX_SIZE] = { 0 };
	char cityFile[MAX_SIZE] = { 0 };
	BinPosition newElement = NULL;

	countryFile = fopen(fileName, "r");
	if (!countryFile)
	{
		perror("Unable to open the file!\n");
		return NULL;
	}

	while (!feof(countryFile))
	{
		fgets(buffer, MAX_LINE, countryFile);
		if (sscanf(buffer, " %s %s", country, cityFile) == 2)
		{
			newElement = CreateTreeElement(country);
			ReadFile(cityFile, newElement->head);
			root = InsertToTree(root, newElement);
		}
	}
	fclose(countryFile);

	return EXIT_SUCCESS;
}

int ReadFile(char* fileName, ListPosition head)
{
	char buffer[MAX_LINE] = { 0 };
	FILE* file = NULL;
	char cityName[MAX_SIZE] = { 0 };
	int population = 0;
	ListPosition newElement = NULL;

	file = fopen(fileName, "r");
	if (!file)
	{
		perror("Could not open the file!\n");
		return NULL;
	}

	while (!feof(file))
	{
		fgets(buffer, MAX_LINE, file);
		if (sscanf(buffer, " %s %d", cityName, &population) == 2)
		{
			newElement = CreateListElement(cityName, population);
			InsertInList(head, newElement);
		}
	}
	fclose(file);

	return EXIT_SUCCESS;
}

int PrintTree(BinPosition current)
{
	if (current == NULL)
	{
		printf("There are no countries in the file.\n");
		return EXIT_SUCCESS;
	}

	PrintTree(current->left);
	printf("Country: %s\n", current->countryName);
	PrintList(current->head);
	PrintTree(current->right);

	return EXIT_SUCCESS;
}

int PrintList(ListPosition head)
{
	ListPosition temp = head->next;

	if (temp == NULL)
	{
		printf("There are no cities in that country");
		return EXIT_SUCCESS;
	}

	printf("Cities: \n");
	while (temp != NULL)
	{
		printf("City: %s\tPopulation: %d\n", temp->cityName, temp->population);
		temp = temp->next;
	}
}