#define CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv)
{
	double result = 0;

	if (CalculatePostfixFromFile(&result, "postfix.txt") == EXIT_SUCCESS)
	{
		printf("Result is: %.2lf\n", result);
	}

	return EXIT_SUCCESS;
}