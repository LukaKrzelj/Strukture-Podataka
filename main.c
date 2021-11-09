#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include "polynomial.h"

int main(int argv, char** argc)
{
	Element Head1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element Head2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element Add = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element Multiply = { .coefficient = 0, .exponent = 0, .next = NULL };
	char fileName[MAX_SIZE] = { 0 };

	if (ReadFile(&Head1, &Head2, fileName) == EXIT_SUCCESS)
	{
		PrintPoly("Polynom 1", &Head1);
		PrintPoly("Polynom 2", &Head2);

		AddPoly(&Head1, &Head2, &Add);
		MultiplyPoly(&Head1, &Head2, &Multiply);

		PrintPoly("Add", &Add);
		PrintPoly("Multiply", &Multiply);

		FreeMemory(&Head1);
		FreeMemory(&Head2);
		FreeMemory(&Add);
		FreeMemory(&Multiply);
	}

	return EXIT_SUCCESS;
}