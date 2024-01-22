/*4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
èitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/
#define CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX_LENGHT 1024

typedef struct Pol* Element;

typedef struct Pol {
	int coefficient;
	int exponent;
	Element next;
} Pol;

int readFile(Element, Element);
Element createEl(Element, int, int);
int SumPol(Element, Element, Element);
int MultiplyPol(Element, Element, Element);
int printPol(Element);
int insertSort(Element, Element);
int separateString(char*, Element);
int deleteEl(Element);
int freeEl(Element, Element);

int main() {

	Pol HeadPol1 = { .coefficient = 0,.exponent = 0,.next = NULL };
	Pol HeadPol2 = { .coefficient = 0,.exponent = 0,.next = NULL };
	Pol HeadSum = { .coefficient = 0,.exponent = 0,.next = NULL };
	Pol HeadMultiply = { .coefficient = 0,.exponent = 0,.next = NULL };

	readFile(&HeadPol1, &HeadPol2);
	printPol(&HeadPol1);
	printf("\n");
	printPol(&HeadPol2);
	MultiplyPol(&HeadPol1, &HeadPol2, &HeadMultiply);
	printf("\n");
	printPol(&HeadMultiply);
	printf("\n");
	SumPol(&HeadPol1, &HeadPol2, &HeadSum);
	printPol(&HeadSum);
	freeEl(&HeadPol1, &HeadPol2);

	return 0;
}

int PrintPol(Element Head)
{
	Element current = Head->next;
	while (current != NULL)
	{
		printf("%dx^%d  ", current->coefficient, current->exponent);
		current = current->next;
	}

	return 0;
}
int ReadFile(Element HeadPol1, Element HeadPol2)
{
	FILE* filepointer = NULL;
	char line[MAX_LENGHT] = "";

	filepointer = fopen("polinomi.txt", "r");

	if (!filepointer)
		return -1;

	fgets(line, MAX_LENGHT, filepointer);
	separateString(line, HeadPol1);

	fgets(line, MAX_LENGHT, filepointer);
	separateString(line, HeadPol2);

	printf("\n");

	fclose(filepointer);

	return 0;
}

int separateString(char* line, Element Head)
{
	int coefficient = 0;
	int exponent = 0;
	int val = 0;
	int byte = 0;
	int number = 0;

	while (strlen(line + number) > 0)
	{
		val = sscanf(line + number, "%d x^ %d %n", &coefficient, &exponent, &byte);
		number += byte;

		if (val != 2)
			return -1;

		if (val == 2)
			createEl(Head, coefficient, exponent);
	}
	return 0;
}

Element createEl(Element Head, int coefficient, int exponent)
{
	Element newElement = NULL;
	newElement = malloc(sizeof(Pol));

	if (!newElement)
		return NULL;

	newElement->coefficient = coefficient;
	newElement->exponent = exponent;

	return newElement;
}

int addEl(Element current, Element newElement)
{
	if (current->next == NULL)
	{
		newElement->next = NULL;
		current->next = newElement;
	}
	else
	{
		newElement->next = current->next;
		current->next = newElement;
	}

	return 0;
}
int insertSort(Element Head, Element newElement)
{
	Element current = Head;

	if (!newElement)
		return -1;

	while (current->next != NULL && current->next->exponent > newElement->exponent)
		current = current->next;

	if (current->next != NULL)
	{
		if (current->next->exponent < newElement->exponent)
			addToEnd(current, newElement);

		else
		{
			current->next->coefficient += newElement->coefficient;
			free(newElement);

			if (current->next->coefficient == 0)
				deleteEl(Head);
		}
	}
	else
		addToEnd(current, newElement);

	return 0;
}

int deleteEl(Element Head) {

	Element current = Head;
	Element temp = NULL;

	while (current != NULL && current->next != NULL && current->next->coefficient != 0)
		current = current->next;

	if (current->next->coefficient == 0)
	{
		temp = current->next;
		current->next = current->next->next;
		free(temp);
	}

	return 0;
}
int freeEl(Element HeadPol1, Element HeadPol2)
{
	Element currentPol1 = HeadPol1->next;
	Element currentPol2 = HeadPol2->next;
	Element temp = NULL;

	while (currentPol1 != NULL)
	{
		temp = currentPol1;
		currentPol1 = currentPol1->next;
		free(temp);

	}
	while (currentPol2 != NULL)
	{
		temp = currentPol2;
		currentPol2 = currentPol2->next;
		free(temp);
	}

	return 0;
}

int MultiplyPol(Element HeadPol1, Element HeadPol2, Element HeadMultiply)
{
	Element currentPol1 = HeadPol1->next;
	Element currentPol2 = HeadPol2->next;
	Element newElement = NULL;

	int mcoeff = 0, mexponent = 0;

	while (currentPol1 != NULL)
	{
		while (currentPol2 != NULL)
		{
			mcoeff = currentPol1->coefficient * currentPol2->coefficient;
			mexponent = currentPol1->exponent + currentPol2->exponent;
			newElement = AddEl(HeadMultiply, mcoeff, mexponent);

			currentPol2 = currentPol2->next;
		}
		currentPol1 = currentPol1->next;
		currentPol2 = HeadPol2->next;
	}

	return 0;
}
int SumPol(Element HeadPol1, Element HeadPol2, Element HeadSum)
{
	Element currentPol1 = HeadPol1->next;
	Element currentPol2 = HeadPol2->next;
	int sCoefficient = 0;

	while (currentPol1 != 0 && currentPol2 != 0)
	{
		if (currentPol1->exponent == currentPol2->exponent)
		{
			sCoefficient = currentPol1->coefficient + currentPol2->coefficient;
			if (sCoefficient != 0)
				addEl(HeadSum, sCoefficient, currentPol1->exponent);

			currentPol1 = currentPol1->next;
			currentPol2 = currentPol2->next;
		}
		else if (currentPol1->exponent > currentPol2->exponent)
		{
			addEl(HeadSum, currentPol1->coefficient, currentPol1->exponent);
			currentPol1 = currentPol1->next;
		}
		else
		{
			addEl(HeadSum, currentPol2->coefficient, currentPol2->exponent);
			currentPol2 = currentPol2->next;
		}
	}
	while (currentPol1 != 0)
	{
		addEl(HeadSum, currentPol1->coefficient, currentPol1->exponent);
		currentPol1 = currentPol1->next;
	}
	while (currentPol2 != 0)
	{
		addEl(HeadSum, currentPol2->coefficient, currentPol2->exponent);
		currentPol2 = currentPol2->next;
	}

	return 0;
}