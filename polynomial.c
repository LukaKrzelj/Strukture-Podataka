#define _CRT_SECURE_NO_WARNINGS

#include "polynomial.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int FillOutFileName(char* fileName)
{
	printf("Enter the name of file:\t");
	scanf(" %s", fileName);

	return EXIT_SUCCESS;
}

int ReadFile(Position head1, Position head2, char* fileName)
{
	FILE* file = NULL;
	char buffer[MAX_LINE] = { 0 };
	int status = EXIT_SUCCESS;

	FillOutFileName(fileName);
	file = fopen(fileName, "r");
	if (!file)
	{
		perror("Could not find a file with such name!\n");
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, file);
	status = ParseStringIntoList(head1, buffer);
	if (status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, file);
	status = ParseStringIntoList(head2, buffer);
	if (status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fclose(file);

	return EXIT_SUCCESS;
}

int ParseStringIntoList(Position head, char* buff)
{
	char* permBuffer = buff;
	int coeff = 0;
	int exp = 0;
	int numberOfBytes = 0;
	int status = 0;
	Position newElement = NULL;

	while (strlen(permBuffer) > 0)
	{
		status = sscanf(permBuffer, "%d %d %n", &coeff, &exp, &numberOfBytes);
		if (status != 2)
		{
			perror("This file is not good!\n");
			return EXIT_FAILURE;
		}

		newElement = CreateElement(coeff, exp);
		if (!newElement)
			return EXIT_FAILURE;

		InsertSorted(head, newElement);

		permBuffer += numberOfBytes;
	}

	return EXIT_SUCCESS;
}

Position CreateElement(int coeff, int exp)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(Element));
	if (!newElement)
	{
		perror("Could not allocate memory!\n");
		return NULL;
	}

	newElement->coefficient = coeff;
	newElement->exponent = exp;
	newElement->next;

	return newElement;
}

int InsertSorted(Position head, Position newElement)
{
	Position temp = head;

	while (temp->next != NULL && temp->next->exponent < newElement->exponent)
	{
		temp = temp->next;
	}

	MergeAfter(temp, newElement);

	return EXIT_SUCCESS;
}

int MergeAfter(Position mergeAfter, Position newElement)
{
	if (mergeAfter->next == NULL || mergeAfter->next->exponent != newElement->exponent)
	{
		InsertAfter(mergeAfter, newElement);
	}
	else
	{
		int resultCoeff = mergeAfter->next->coefficient + newElement->coefficient;
		if (resultCoeff == 0)
		{
			DeleteAfter(mergeAfter);
		}
		else
		{
			mergeAfter->next->coefficient = resultCoeff;
		}
		free(newElement);
	}

	return EXIT_SUCCESS;
}

int InsertAfter(Position insertAfter, Position newElement)
{
	newElement->next = insertAfter->next;
	insertAfter->next = newElement;
	
	return EXIT_SUCCESS;
}

int DeleteAfter(Position toDeleteAfter)
{
	Position toDelete = NULL;

	toDelete = toDeleteAfter->next;
	toDeleteAfter->next = toDelete->next;
	free(toDelete);

	return EXIT_SUCCESS;
}

int PrintPoly(char* name, Position head)
{
	Position temp = head->next;

	printf("%s: ", name);
	if (temp)
	{
		if (temp->exponent < 0)
		{
			if (temp->coefficient == 1)
			{
				printf("x^(%d)", temp->exponent);
			}
			else
			{
				printf("%dx^(%d)", temp->coefficient, temp->exponent);
			}
		}
		else
		{
			if (temp->coefficient == 1)
			{
				printf("x^%d", temp->exponent);
			}
			else
			{
				printf("%dx^%d", temp->coefficient, temp->exponent);
			}
		}

		temp = temp->next;
	}

	for (temp; temp != NULL; temp = temp->next)
	{
		if (temp->coefficient < -1)
		{
			if (temp->exponent < 0)
			{
				printf(" - %dx^(%d)", temp->coefficient, temp->exponent);
			}
			else
			{
				printf(" - %dx^%d", temp->coefficient, temp->exponent);
			}
		}
		else if (temp->coefficient == 1)
		{
			if (temp->exponent < 0)
			{
				printf(" + x^(%d)", temp->exponent);
			}
			else
			{
				printf(" + x^%d", temp->exponent);
			}
		}
		else if (temp->coefficient == -1)
		{
			if (temp->exponent < 0)
			{
				printf(" - x^(%d)", temp->exponent);
			}
			else
			{
				printf(" - x^%d", temp->exponent);
			}
		}
		else
		{
			if (temp->exponent < 0)
			{
				printf(" + %dx^(%d)", temp->coefficient, temp->exponent);
			}
			else
			{
				printf(" + %dx^%d", temp->coefficient, temp->exponent);
			}
		}
		
	}
	printf("\n");

	return EXIT_SUCCESS;
}

int AddPoly(Position head1, Position head2, Position Add)
{
	Position temp = NULL, tempi = head1->next, tempj = head2->next, tempk = Add;

	while (tempi != NULL && tempj != NULL)
	{
		if (tempi->exponent == tempj->exponent)
		{
			CreateAndInsertAfter(tempi->coefficient + tempj->coefficient, tempi->exponent, tempk);
			tempi = tempi->next;
			tempj = tempj->next;
		}
		else if (tempi->exponent < tempj->exponent)
		{
			CreateAndInsertAfter(tempi->coefficient, tempi->exponent, tempk);
			tempi = tempi->next;
		}
		else
		{
			CreateAndInsertAfter(tempj->coefficient, tempj->exponent, tempk);
			tempj = tempj->next;
		}
	}

	if (tempi == NULL)
	{
		temp = tempj;
	}
	else
	{
		temp = tempi;
	}
	
	while (temp != NULL)
	{
		CreateAndInsertAfter(temp->coefficient, temp->exponent, tempk);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int CreateAndInsertAfter(int coeff, int exp, Position position)
{
	Position newElement = CreateElement(coeff, exp);
	if (!newElement)
	{
		return EXIT_FAILURE;
	}

	InsertAfter(position, newElement);
	position = position->next;

	return EXIT_SUCCESS;
}

int MultiplyPoly(Position head1, Position head2, Position Multiply)
{
	Position tempi = NULL, tempj = NULL;

	for (tempi = head1->next; tempi != NULL; tempi = tempi->next)
	{
		for (tempj = head2->next; tempj != NULL; tempj = tempj->next)
		{
			Position newElement = CreateElement(tempi->coefficient * tempj->coefficient, tempi->exponent + tempj->exponent);
			if (!newElement)
			{
				return EXIT_FAILURE;
			}

			InsertSorted(Multiply, newElement);
		}
	}

	return EXIT_SUCCESS;
}

int FreeMemory(Position head)
{
	Position temp = head;

	while (temp->next)
	{
		DeleteAfter(temp);
	}

	return EXIT_SUCCESS;
}