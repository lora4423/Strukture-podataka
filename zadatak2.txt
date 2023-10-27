/*2. Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
A.dinamièki dodaje novi element na poèetak liste,
B.ispisuje listu,
C.dinamièki dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person *Position;

typedef struct _Person{
	char name[50];
	char surname[50];
	int year;
	Position next;
} Person;

Person createNewPerson();
int addToList(Position head);
int printList(Position first);
Position findLastPerson(Position head);
int addPersonToEndOfList(Position head);

int main() {

	Person Head = { .next = NULL,.name = {0},.surname = {0},.year = 0 };

	return EXIT_SUCCESS;
}

Person createNewPerson(){
	Position newPerson = NULL;
	char name[50] = { 0 }, surname[50] = {0};
	int year = 0;

	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson) {
		printf("Alokacija memorije nije moguæa. \n");
		exit (1);
	}

	printf("Ime: \n");
	scanf(" %[ ^\n]", name);
	printf("Prezime: \n");
	scanf(" %[ ^\n]", surname);
	printf("Godina roðenja: \n");
	scanf(" %d", &year);

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->year=year;

	return newPerson;
}

int addToList(Position head) {
	Position newPerson = NULL;

	newPerson = createNewPerson();

	if (newPerson) {

		newPerson->next = head->next;
		head->next = newPerson;

	}
	return EXIT_SUCCESS;
}

Position findLastPerson(Position head) {
	
	while (head->next != NULL) {
		head = head->next;
	}
	return head;
}

int addPersonToEndOfList(Position head) {

	Position newPerson = NULL;
	newPerson=createNewPerson();

	if (newPerson) {
		head = findLastPerson(head);
		newPerson->next = head->next;
		head->next = newPerson;
	}
	return EXIT_SUCCESS;
}

int printList(Position first) {

	if (!first) {
		printf("Prazna lista!\n");
	}
	for (; first != NULL; first = first->next) {
		printf("Ime: %s, prezime: %s, Godina roðenja %d \n", first->name, first->surname, first->year);

	}
	return EXIT_SUCCESS;
}

