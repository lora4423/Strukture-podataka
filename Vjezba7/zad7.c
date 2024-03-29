#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 1024

typedef struct _directory* PositionDirectory;
typedef struct _directory {

	char name[MAX_LENGTH];
	PositionDirectory subDirectory;
	PositionDirectory nextDirectory;

}Directory;

typedef struct _stack* PositionStack;
typedef struct _stack {

	PositionDirectory currentDirectory;
	PositionStack nextStack;

}Stack;

int ChooseCommand(PositionDirectory DirectoryHead, PositionStack StackHead);
int MakeDirectory(PositionDirectory DirectoryHead, PositionStack StackHead, char* name);
int ChangeDirectory(PositionDirectory Directory, PositionStack StackHead, char* name);
int ListDirectories(PositionDirectory Directory, PositionStack StackHead);
int Push(PositionDirectory Directory, PositionStack StackHead);
PositionDirectory Pop(PositionDirectory DirectoryHead, PositionStack StackHead);
PositionDirectory FindCurrentDirectory(PositionStack StackHead);


int main() {

	Directory DirectoryHead = { .name = {0},.subDirectory = NULL,.nextDirectory = NULL };
	Stack StackHead = { .currentDirectory = NULL,.nextStack = NULL };
	PositionStack newStack = (PositionStack)malloc(sizeof(Stack));

	newStack->currentDirectory = &DirectoryHead;
	newStack->nextStack = NULL;

	(&StackHead)->nextStack = newStack;

	ChooseCommand(&DirectoryHead, &StackHead);

	free(newStack);

}

int ChooseCommand(PositionDirectory DirectoryHead, PositionStack StackHead) {

	int choice = 0;
	char name[MAX_LENGTH] = { 0 };
	PositionDirectory currentDirectory = NULL;

	while (1)
	{
		printf("\nIzaberite:\n1-md\n2-cd\n3-cd..\n4-dir\n5-exit\n\n");
		scanf("%d", &choice);
		switch (choice) {

		case 1:
			printf("Unesite ime direktorija: ");
			scanf("%s", name);
			MakeDirectory(DirectoryHead, StackHead, name);
			break;

		case 2:
			printf("Unesite ime direktorija: ");
			scanf("%s", name);
			ChangeDirectory(DirectoryHead, StackHead, name);
			break;

		case 3:
			Pop(DirectoryHead, StackHead);
			currentDirectory = FindCurrentDirectory(StackHead);

			if (!currentDirectory)
				return -1;

			if (currentDirectory == DirectoryHead)
				printf("Nalazite se u root direktoriju\n");
			else
				printf("Sada se nalazite u %s direktoriju\n", currentDirectory->name);

			break;

		case 4:
			ListDirectories(DirectoryHead, StackHead);
			break;

		case 5:
			printf("Izlaz");
			return 0;

		default:
			printf("Greska");
			break;
		}
	}
	return 0;
}

int MakeDirectory(PositionDirectory DirectoryHead, PositionStack StackHead, char* name) {

	PositionDirectory newDirectory;
	PositionDirectory currentDirectory = FindCurrentDirectory(StackHead);

	if (!currentDirectory)
		return -1;

	newDirectory = (PositionDirectory)malloc(sizeof(Directory));
	strcpy(newDirectory->name, name);
	newDirectory->nextDirectory = NULL;
	newDirectory->subDirectory = NULL;

	if (currentDirectory->subDirectory == NULL)
		currentDirectory->subDirectory = newDirectory;

	else
	{
		currentDirectory = currentDirectory->subDirectory;
		while (currentDirectory->nextDirectory != NULL && strcmp(currentDirectory->name, name) != 0)
			currentDirectory = currentDirectory->nextDirectory;

		newDirectory->nextDirectory = currentDirectory->nextDirectory;
		currentDirectory->nextDirectory = newDirectory;
	}
	return 0;

}

int ChangeDirectory(PositionDirectory Directory, PositionStack StackHead, char* name) {

	PositionDirectory currentDirectory = FindCurrentDirectory(StackHead)->subDirectory;

	while (currentDirectory != NULL && strcmp(currentDirectory->name, name) != 0)
		currentDirectory = currentDirectory->nextDirectory;

	if (currentDirectory != NULL)
		Push(currentDirectory, StackHead);

	else
		printf("\nTaj direktorij ne postoji ili mu ne mozete pristupiti!\n");

	return 0;

}

int ListDirectories(PositionDirectory Directory, PositionStack StackHead) {

	PositionDirectory currentDirectory = FindCurrentDirectory(StackHead);

	if (!currentDirectory)
		return -1;

	currentDirectory = currentDirectory->subDirectory;

	while (currentDirectory != NULL)
	{
		printf("%s  ", currentDirectory->name);
		currentDirectory = currentDirectory->nextDirectory;

	}
	return 0;

}

int Push(PositionDirectory currentDirectory, PositionStack StackHead) {

	PositionStack newStack = (PositionStack)malloc(sizeof(Stack));

	newStack->currentDirectory = currentDirectory;

	newStack->nextStack = StackHead->nextStack;
	StackHead->nextStack = newStack;

	return 0;

}

PositionDirectory Pop(PositionDirectory DirectoryHead, PositionStack StackHead) {

	PositionStack tempStack = NULL;
	PositionDirectory currentDirectory = NULL;

	if (StackHead->nextStack->currentDirectory == DirectoryHead)
		return DirectoryHead;

	else
	{
		tempStack = StackHead->nextStack;
		currentDirectory = tempStack->currentDirectory;
		StackHead->nextStack = StackHead->nextStack->nextStack;
		free(tempStack);

		return currentDirectory;
	}
}

PositionDirectory FindCurrentDirectory(PositionStack StackHead) {

	return StackHead->nextStack->currentDirectory;
}