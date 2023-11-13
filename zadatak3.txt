/*2. Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
A. dinamièki dodaje novi element na poèetak liste,
B. ispisuje listu,
C. dinamièki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.

3. Prethodnom zadatku dodati funkcije:
A. dinamièki dodaje novi element iza odreðenog elementa,
B. dinamièki dodaje novi element ispred odreðenog elementa,
C. sortira listu po prezimenima osoba (ne treba),
D. upisuje listu u datoteku,
E. èita listu iz datoteke.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LENGTH 50 
#define MAX_L 1024

struct _Person;
typedef struct _Person *Position;

typedef struct _Person {
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int yearOfBirth;
	Position next;
} Person;

Position createPerson();

int addNewElement(Position head);  //dinamièki dodaje novi element na poèetak liste
int printList(Position first); //ispisuje listu
int addNewElementToEndOfList(Position head);  //dinamièki dodaje novi element na kraj liste
int findPerson(Position head);  //pronalazi element u listi (po prezimenu)
int deletePerson(Position head);   //briše odreðeni element iz liste

Position findLastPerson(Position head);
int printPerson(Position person);
char* requestedSurname();

int menu(Position head);

int insertAfter(Position head); //dinamièki dodaje novi element iza odreðenog elementa,
int insertBefore(Position head, char[]);  //dinamièki dodaje novi element ispred odreðenog elementa
int writeInFile(Position head, char[]);    //upisuje listu u datoteku,
int readFile();	//èita listu iz datoteke


int main() {

	Person Head = { .next= NULL , .name = {0}, .surname = {0}, .yearOfBirth=0 };
	
	menu(&Head);

	return EXIT_SUCCESS;
}

Position createPerson() {
	Position newPerson = NULL;
	char name[MAX_LENGTH] = { 0 };
	char surname[MAX_LENGTH] = { 0 };
	int yearOfBirth = 0;

	newPerson = malloc(sizeof(Person));

	if (!newPerson) {
		printf("Nije moguæa alokacija memorije za novu osobu");
		return NULL;
	}
	printf("Unesi ime: \n");
	scanf("%s", name);
	printf("Unesi prezime: \n");
	scanf("%s", surname);
	printf("Unesi godinu roðenja: \n");
	scanf("%d", &yearOfBirth);

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->yearOfBirth=yearOfBirth;

	return newPerson;
}

int addNewElement(Position head) 
{
	Position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson) {
		newPerson->next = head->next;
		head->next = newPerson;
	}
	return EXIT_SUCCESS;
}

int printList(Position first)
{
	if (!first) {
		printf("Prazna lista \n");
	}

	for (; first != NULL; first = first->next) { // for(i=0;i<n;i++)
		printf("Ime: %s, prezime %s, godina rodenja %d", first->name, first->surname, first->yearOfBirth);
	}
	return EXIT_SUCCESS;
}

Position findLastPerson(Position head) {
	while (head->next != NULL) {
		head = head->next;
	}
	return head;
}

int addNewElementToEndOfList(Position head) {
	Position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson) {
		head = findLastPerson(head);
		newPerson->next = head->next;
		head->next = newPerson;
	}
	return EXIT_SUCCESS;
}

int printPerson(Position person)
{
	printf("Ime: %s, prezime %s, godina rodenja %d", person->name, person->surname, person->yearOfBirth);
	return EXIT_SUCCESS;
}

char* requestedSurname() {
	char surname[MAX_LENGTH] = { 0 };
	printf("Upišite traženo prezime: \n");
	scanf("%s", surname);
	return surname;
}

int findPerson(Position head) {
	if (head->next) {
		while (head->next && strcmp(head->next->surname, requestedSurname() != 0)) {
			head = head->next;
		}
		if (head->next) {
			printPerson(head->next);
		}
		else {
			printf("Nije pronadena tražena osoba \n");
		}
	}
	return EXIT_SUCCESS;
}

int deletePerson(Position head) {

	if (head->next) {
		Position previous = NULL;
		while (head->next && strcmp(head->surname,requestedSurname())!=0) {
			previous = head;
			head=head->next;
		}
		if (previous->next && strcmp(head->surname, requestedSurname()) == 0) {
			printPerson(head);
			previous->next = head->next;
			printf("Obrisana osoba \n");
			free(head);
		}
		else {
			printf("Nema trazene osobe\n");
			return -1;
		}
	}
	return EXIT_SUCCESS;
}

int insertBefore(Position head,char surname[]) {
	Position newPerson = NULL;

	newPerson = createPerson();

	while (head != NULL && head->next != NULL) {
		if (strcmp(head->next->surname, surname) == 0) {
			newPerson->next = head->next;
			head->next = newPerson;
			break;
		}
		head = head->next;
	}
	return 0;
}

int insertAfter(Position head,char surname[]) {
	Position newPerson = NULL;
	newPerson = createPerson();

	while (newPerson != NULL) {
		if (strcmp(head->surname, surname) == 0) {
			newPerson->next = head->next;
			head->next = newPerson;
			break;
		}
		head = head->next;
	}
	return 0;
}
int writeInFile(Position head) {
	FILE *filePointer=NULL;
	
	filePointer = fopen("people.txt","w");

	if (!filePointer) {
		return -1;
	}
	while(head->next!=NULL){
		head = head->next;
		fprintf(filePointer, "%s %s %d \n", head->name, head->surname, head->yearOfBirth);
	}
	
	fclose(filePointer);

	return 0;
}
int readFile() {
	FILE *filePointer = NULL;
	Person Head = { .name = {0},.surname = {0},.yearOfBirth = 0,.next = NULL };

	filePointer = fopen("people.txt", "r");

	if (!filePointer) {
		return -1;
	}
	while (1) {
		fscanf(filePointer, "%s %s %d", Head.name, Head.surname, &Head.yearOfBirth);

		if (feof(filePointer)) {
			break;
		}
		printf("%s %s %d \n", Head.name, Head.surname, Head.yearOfBirth);
	}
	fclose(filePointer);

	return 0;
}

int menu(Position Head) {
	char c =  '\0';
	printf("Unesi: A. dodavanje novog elementa na poèetak liste, B. ispis liste, C. dodavanje novog elementa na kraj liste, D. traženje elementa u listi(po prezimenu), E. brisanje odreðenog elementa iz liste\n");
	scanf("%c", &c);

	if (c == 'A') {
		addNewElement(Head);
	}
	else if (c == 'B') {
		printList(Head->next);
	}
	else if (c == 'C') {
		addNewElementToEndOfList(Head);
	}
	else if (c == 'D') {
		while (findPerson(Head) == -1) {
			findPerson(Head);
		}
	}
	else if (c == 'E') {
		while (deletePerson(Head) == -1) {
			deletePerson(Head);
		}
	}
	return EXIT_SUCCESS;
}
