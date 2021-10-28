#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct _Person;
typedef struct _Person* Position;

typedef struct _Person {
	char name[50];
	char surname[50];
	int birthYear;
	Position next;
}Person;

Position createPerson(char* name, char* surname, int birthYear);
Position findBefore(Position head, char* surname);
int deleteElement(Position head, char* surname);

int main(int argc, char** argv)
{
	Person head = {.name = {0}, .surname = {0}, .birthYear = 0, .next = NULL};
	Position p = &head;
	Position p1, p2, p3;

	p1 = createPerson("Sime", "Simic", 2000);
	p2 = createPerson("Duje", "Dujic", 1950);
	p3 = createPerson("Mate", "Matic", 1911);

	deleteElement(p, "Dujic");
	
	return EXIT_SUCCESS;
}

Position createPerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if(!newPerson)
	{
		perror("Could not allocate memory.\n");
		return -1;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

Position findBefore(Position head, char* surname)
{
	Position before = head;

	while(before->next != NULL && strcmp(before->next->surname, surname) != 0){
		before = before->next;
	}

	if(before->next != NULL)
		return before;
	else
		return NULL;
}

int deleteElement(Position head, char* surname)
{
	Position toDelete = head;
	Position before = findBefore(toDelete, surname);

	if(before == NULL)
	{
		perror("There is no such person.\n");
		return -1;
	}
	else{
		toDelete = before->next;
		before->next = toDelete->next;
		free(toDelete);
	}


	return EXIT_SUCCESS;
}