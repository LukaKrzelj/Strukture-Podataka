#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hash.h"

int main(int argv, char** argc)
{
	List head = { .countryName = {0}, .next = NULL, .root = NULL };
	int action = 0;
	char country[MAX_SIZE] = { 0 };
	int population = 0;

	ReadFile("drzave.txt", &head);
	PrintList(&head);

	while (action != 2)
	{
		printf("Which country do you want to search: ");
		scanf(" %s", country);
		printf("City population > ");
		scanf("%d", &population);

		FindCountry(&head, country, population);

		printf("If you want to continue searching press 1, if you want to exit press 2: ");
		scanf("%d", &action);
	}


	return EXIT_SUCCESS;
}