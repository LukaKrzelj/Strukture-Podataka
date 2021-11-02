#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (1024)
#define MAX_SIZE (128)

struct Person;
typedef struct _Person* Position;

typedef struct _Person
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
}Person;

Position createPerson(char* name, char* surname, int birthYear);
Position findByLastName(Position first, char* surname);
Position findBefore(Position first, char* surname);
int insertAfter(Position _position, Position newPerson);
int insertAfterElement(char* surnameSearch, Position head, char* name, char* surname, int birthYear);
int insertBeforeElement(char* surnameSearch, Position head, char* name, char* surname, int birthYear);
int sortInput(Position head, Position newPerson);
int addToFile(Position head, char* nameOfFile);
int readFromFile(Position head, char* nameOfFile);

int main(int argc, char** argv)
{
    Person head = {.name = {0}, .surname = {0}, .birthYear = 0, .next = NULL};
    Position p = &head;
    Position temp = NULL;   
    
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

Position findByLastName(Position first, char* surname)
{
    Position positionOfElement = first;

    while(positionOfElement){
        if(strcmp(positionOfElement->surname, surname) == 0)
        {
            return positionOfElement;
        }
        positionOfElement = positionOfElement->next;
    }
    
    return NULL;
}

Position findBefore(Position first, char* surname)
{
    Position before = first;

    while(before->next != NULL && strcmp(before->next->surname, surname) != 0)
    {
        before = before->next;
    }
    if(before->next != NULL)
        return before;
    
    return NULL;
}

int insertAfter(Position _position, Position newPerson)
{
    newPerson->next = _position->next;
    _position->next = newPerson;
    
    return EXIT_SUCCESS;
}

int insertAfterElement(char* surnameSearch, Position head, char* name, char* surname, int birthYear)
{
    Position toInsertAfter = NULL;
    Position newPerson = NULL;

    toInsertAfter = findByLastName(head, surnameSearch);
    if(!toInsertAfter)
    {
        perror("There is no such surname.\n");
        return -1;
    }

    newPerson = createPerson(name, surname, birthYear);
    if(!newPerson)
    {
        perror("Error!\n");
        return -1;
    }
    else
    {
        insertAfter(toInsertAfter, newPerson);
    }
    
    return EXIT_SUCCESS;
}

int insertBeforeElement(char* surnameSearch, Position head, char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;
    Position previous = NULL;
    
    previous = findBefore(head, surnameSearch);
    if(!previous)
    {
        perror("Error!\n");
        return -1;
    }

    newPerson = createPerson(name, surname, birthYear);
    if(!newPerson)
    {
        perror("Error!\n");
        return -1;
    }

    insertAfter(previous, newPerson);
    
    return EXIT_SUCCESS;
}

int sortInput(Position head, Position newPerson)
{
    Position temp = NULL;
    temp = head;

    while(temp->next != NULL && strcmp(temp->next->surname, newPerson->surname))
    {
        temp = temp->next;
    }
    
    insertAfter(temp, newPerson);

    return EXIT_SUCCESS;
}

int addToFile(Position head, char* nameOfFile)
{
    FILE* file = NULL;
    Position temp = NULL;
    temp = head;

    file = fopen(nameOfFile, "w");
    if(!file)
    {
        perror("Unable to open the file.\n");
        return -1;
    }

    while(temp->next != NULL)
    {
        fprintf(file, "%s %s %d", temp->next->name, temp->next->surname, temp->next->birthYear);
        temp = temp->next;
    }
    
    fclose(file);

    return EXIT_SUCCESS;
}

int readFromFile(Position head, char* nameOfFile)
{
    char buffer[MAX_LINE] = {0};
    char name[MAX_SIZE] = {0};
    char surname[MAX_SIZE] = {0};
    int birthYear = 0;
    FILE* file = NULL;
    Position newPerson = NULL;
    Position temp = NULL;
    temp = head;

    file = fopen(nameOfFile, "r");
    if(!file)
    {
        perror("Unable to open the file.\n");
        return -1;
    }
    while(!feof(file))
    {
        fgets(buffer, MAX_LINE, file);
        if(sscanf(buffer, " %s %s %d", name, surname, &birthYear) == 3)
        {
            newPerson = createPerson(name, surname, birthYear);
            sortInput(head, newPerson);
            temp = temp->next;
        }
    }

    fclose(file);
    
    return EXIT_SUCCESS;
}