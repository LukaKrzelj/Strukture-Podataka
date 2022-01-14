#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "zad10a.h"

int main(int argv, char** argc)
{
	List head = { .countryName = {0}, .next = NULL, .root = NULL };
	
	ReadFile("drzave.txt", &head);
	PrintList(&head);

	return EXIT_SUCCESS;
}