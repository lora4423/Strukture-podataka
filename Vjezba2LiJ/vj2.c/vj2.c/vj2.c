/*
Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX_LENGTH 50

typedef struct _Person *Position;
typedef struct _Person 
{
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthYear;

};
int main()
{

}
