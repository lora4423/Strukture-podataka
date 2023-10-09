

#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS
typedef struct{
	char ime[10];
	char prezime[10];
	double bodovi;
}student;

int main()
{
	int brojRedova = 0;
	char charBuffer[1024]="";
	FILE* filePointer = NULL;
	
	filePointer = fopen("studenti.txt", "r");

	if (filePointer == NULL){
		printf("Datoteka nije pronadjena");
		return 1;
	}
	
	while (!feof(filePointer)) {
		if (fgets(charBuffer,1024,filePointer) ) {
			brojRedova++;
		}

	}
	printf("%d", brojRedova);
	fclose(filePointer);
	return 0;
}