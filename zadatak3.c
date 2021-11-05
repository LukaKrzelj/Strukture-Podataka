#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _Person* Position;

typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

Position createPerson(char* name, char* surname, int birthYear);
Position findLast(Position head);
Position findBySurname(Position head, char* surnameSearch);
Position findBefore(Position head, char* surnameSearch);
int insertAfter(Position after, Position newPerson);
int addToBeginning(Position head, char* name, char* surname, int birthYear);
int addToEnd(Position head, char* name, char* surname, int birthYear);
int printList(Position head);
int deleteElement(Position head, char* surnameSearch);
int insertAfterElement(Position head, char* surnameSearch, char* name, char* surname, int birthYear);
int insertBeforeElement(Position head, char* surnameSearch, char* name, char* surname, int birthYear);
int sortInput(Position head, char* name, char* surname, int birthYear);
int addToFile(Position head, char* nameOfFile);
int readFromFile(Position head, char* nameOfFile);

int main(int argv, char** argc)
{
	Person head = { .name = {0}, .surname = {0}, .birthYear = 0, .next = NULL };
	Position p = &head;
	Position p1 = NULL, p2 = NULL, p3 = NULL, sur = NULL;

	p1 = createPerson("Zvonimir", "Cntic", 2000);
	p2 = createPerson("Ante", "Antic", 1991);
	p3 = createPerson("Mate", "Matic", 2003);

	/*insertAfter(p, p1);
	insertAfter(p1, p2);
	insertAfter(p2, p3);
	insertAfterElement(p, "Antic", "Luka", "Lukic", 1999);
	insertBeforeElement(p, "Zvoncic", "Sime", "Simic", 1973);
	sur = findBefore(p, "Matic");
	printf("%s %s %d", sur->name, sur->surname, sur->birthYear);

	sortInput(p, "Zvonimir", "Entic", 2000);
	sortInput(p, "Mate", "Bntic", 2003);
	sortInput(p, "Ante", "Antic", 1991);
	insertBeforeElement(p, "Entic", "Miladin", "Dntic", 1941);
	insertAfterElement(p, "Bntic", "Maksimilijan", "Cntic", 2020);
	
	addToFile(p, "ljudi.txt");*/
	readFromFile(p, "ljudi.txt");
	printList(p);
	return EXIT_SUCCESS;
}

Position createPerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Could not allocate memory!\n");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int insertAfter(Position after, Position newPerson)
{
	newPerson->next = after->next;
	after->next = newPerson;

	return EXIT_SUCCESS;
}

int addToBeginning(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = createPerson(name, surname, birthYear);
	if(!newPerson)
	{
		perror("Error!\n");
		return -1;
	}

	insertAfter(head, newPerson);
	
	return EXIT_SUCCESS;
}

Position findLast(Position head)
{
	Position temp = NULL;
	temp = head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}

int addToEnd(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = createPerson(name, surname, birthYear);
	if (!newPerson)
	{
		perror("Error!\n");
		return -1;
	}

	last = findLast(head);

	insertAfter(last, newPerson);
	
	return EXIT_SUCCESS;
}

int printList(Position head)
{
	Position temp = head->next;

	while (temp != NULL)
	{
		printf("Name: %s\tSurname: %s\tBirth year: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

Position findBySurname(Position head, char* surnameSearch)
{
	Position temp = head->next;

	while (temp != NULL)
	{
		if (strcmp(temp->surname, surnameSearch) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	
	return NULL;
}

int deleteElement(Position head, char* surnameSearch)
{
	Position temp = NULL, temp1 = NULL;

	temp = findBefore(head, surnameSearch);
	if (temp == NULL)
	{
		perror("There is no such surname!\n");
		return 1;
	}
	else
	{
		temp1 = temp->next;
		temp->next = temp1->next;
		free(temp1);
	}

	return EXIT_SUCCESS;
}

Position findBefore(Position head, char* surnameSearch)
{
	Position temp = head->next, temp1 = head;

	while (temp != NULL)
	{
		if (strcmp(temp->surname, surnameSearch) == 0)
		{
			return temp1;
		}
		temp1 = temp;
		temp = temp->next;
	}

	return NULL;
}

int insertAfterElement(Position head, char* surnameSearch, char* name, char* surname, int birthYear)
{
	Position temp = NULL, newPerson = NULL;

	newPerson = createPerson(name, surname, birthYear);
	if (!newPerson)
	{
		perror("Could not create new element!\n");
		return -1;
	}

	temp = findBySurname(head, surnameSearch);
	if (temp == NULL)
	{
		perror("Could not find that surname!\n");
		return 1;
	}

	insertAfter(temp, newPerson);

	return EXIT_SUCCESS;
}

int insertBeforeElement(Position head, char* surnameSearch, char* name, char* surname, int birthYear)
{
	Position temp = NULL, newPerson = NULL;

	newPerson = createPerson(name, surname, birthYear);
	if (!newPerson)
	{
		perror("Could not create new element!\n");
		return -1;
	}

	temp = findBefore(head, surnameSearch);
	if (temp == NULL)
	{
		perror("Could not find that surname!\n");
		return 1;
	}

	insertAfter(temp, newPerson);

	return EXIT_SUCCESS;
}

int sortInput(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = createPerson(name, surname, birthYear);
	if (!newPerson) {
		perror("Error!\n");
		return -1;
	}

	while (head->next != NULL && strcmp(head->next->surname, newPerson->surname) < 0)
		head = head->next;

	insertAfter(head, newPerson);

	return EXIT_SUCCESS;
}

int addToFile(Position head, char* nameOfFile)
{
	FILE* file = NULL;
	Position temp = NULL;
	temp = head;

	file = fopen(nameOfFile, "w");
	if (!file)
	{
		perror("Unable to open the file.\n");
		return -1;
	}

	while (temp->next != NULL)
	{
		fprintf(file, "%s %s %d\n", temp->next->name, temp->next->surname, temp->next->birthYear);
		temp = temp->next;
	}

	fclose(file);

	return EXIT_SUCCESS;
}

int readFromFile(Position head, char* nameOfFile)
{
	char buffer[MAX_LINE] = { 0 };
	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = 0;
	FILE* file = NULL;
	Position newPerson = NULL;
	Position temp = NULL;
	temp = head;

	file = fopen(nameOfFile, "r");
	if (!file)
	{
		perror("Unable to open the file.\n");
		return -1;
	}
	while (!feof(file))
	{
		fgets(buffer, MAX_LINE, file);
		if (sscanf(buffer, " %s %s %d", name, surname, &birthYear) == 3)
		{
			sortInput(head, name, surname, birthYear);
			temp = temp->next;
		}
	}

	fclose(file);

	return EXIT_SUCCESS;
}