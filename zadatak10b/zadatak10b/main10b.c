#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "zad10b.h"

int main(int argv, char** argc)
{
	BinPosition root = NULL;

	ReadFileForTree("drzave.txt", root);
	PrintTree(root);

	return EXIT_SUCCESS;
}