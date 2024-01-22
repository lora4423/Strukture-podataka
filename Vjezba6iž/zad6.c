#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 1024

typedef struct _article* PositionArticle;
typedef struct _article {

	char article[MAX_LENGTH];
	int weight;
	float price;
	PositionArticle nextArticle;

}Article;

typedef struct _receipt* PositionReceipt;
typedef struct _receipt {

	int year, month, day;
	PositionReceipt nextReceipt;
	Article ArticleHead;

}Receipt;

int ReadFile(PositionReceipt);
PositionReceipt CreateReceipt(PositionReceipt, int, int, int);
int ReadReceipt(char[], PositionReceipt);
int SortArticles(PositionReceipt, char[], int, float);
int SortReceipts(PositionReceipt, PositionReceipt);
int DateSort(PositionReceipt, PositionReceipt);
int ArticleSum(PositionArticle, PositionArticle);
int ArticleMerge(PositionReceipt, PositionReceipt);
int Print(PositionReceipt);
int BetweenDatesArticels(PositionReceipt);


int main()
{
	Receipt HeadReceipt = { .year = 0,.month = 0,.day = 0,.nextReceipt = NULL,.ArticleHead = {.article = {0},.weight = 0,.price = 0.0,.nextArticle = NULL} };
	ReadFile(&HeadReceipt);
	Print(&HeadReceipt);
	BetweenDatesArticels(&HeadReceipt);

}

int ReadFile(PositionReceipt HeadReceipt) {

	FILE* filepointer = NULL;
	char receipts[MAX_LENGTH] = { 0 }, line[MAX_LENGTH];
	int value = 0, bytes = 0, counter = 0;

	filepointer = fopen("racuni.txt", "r");

	if (!filepointer)
		return -1;

	while (fscanf(filepointer, "%s", receipts) == 1)
	{
		//printf("\n%s", receipts);
		ReadReceipt(receipts, HeadReceipt);
	}
	if (!feof(filepointer))
		return -1;

	fclose(filepointer);

}

int ReadReceipt(char receipts[], PositionReceipt HeadReceipt) {

	FILE* filepointer_receipt = NULL;
	int year = 0, month = 0, day = 0, weight = 0, value = 0, bytes = 0;
	float price = 0.0;
	char article[MAX_LENGTH] = { 0 }, receipt[MAX_LENGTH];
	PositionReceipt newReceipteipt = NULL;

	filepointer_receipt = fopen(receipts, "r");

	if (!filepointer_receipt)
		return -1;

	fscanf(filepointer_receipt, "%d-%d-%d", &year, &month, &day);
	//printf("\n%d-%d-%d\n", year, month, day);
	newReceipteipt = CreateReceipt(newReceipteipt, year, month, day);

	if (!newReceipteipt)
		return -1;

	while (fscanf(filepointer_receipt, "%s %d %f", article, &weight, &price) == 3)
	{
		//printf("%s %d %.1f\n",article, weight, price);
		SortArticles(newReceipteipt, article, weight, price);

	}
	if (!feof(filepointer_receipt))
		return -1;

	SortReceipts(HeadReceipt, newReceipteipt);


	fclose(filepointer_receipt);
}

PositionReceipt CreateReceipt(PositionReceipt newReceipteipt, int year, int month, int day) {

	newReceipteipt = (PositionReceipt)malloc(sizeof(Receipt));

	if (!newReceipteipt)
		return NULL;

	newReceipteipt->year = year;
	newReceipteipt->month = month;
	newReceipteipt->day = day;
	newReceipteipt->nextReceipt = NULL;
	newReceipteipt->ArticleHead.nextArticle = NULL;

	return newReceipteipt;

}

int SortArticles(PositionReceipt newReceipteipt, char article[], int weight, float price) {

	PositionArticle newArticle = (PositionArticle)malloc(sizeof(Article));
	PositionArticle currentArticle = &(newReceipteipt->ArticleHead);

	if (!newArticle)
		return -1;

	strcpy(newArticle->article, article);
	newArticle->weight = weight;
	newArticle->price = price;

	while (currentArticle->nextArticle != NULL && strcmp(currentArticle->nextArticle->article, newArticle->article) <= 0)
		currentArticle = currentArticle->nextArticle;

	if (currentArticle->nextArticle != NULL && strcmp(currentArticle->nextArticle->article, newArticle->article) == 0)
		ArticleSum(currentArticle->nextArticle, newArticle);

	else
	{
		newArticle->nextArticle = currentArticle->nextArticle;
		currentArticle->nextArticle = newArticle;
	}

	return 0;
}

int ArticleSum(PositionArticle currentArticle, PositionArticle newArticle) {

	currentArticle->weight += newArticle->weight;
	currentArticle->price += newArticle->price;

	return 0;
}

int SortReceipts(PositionReceipt HeadReceipt, PositionReceipt newReceipteipt) {

	PositionReceipt currentReceipt = HeadReceipt;

	while (currentReceipt->nextReceipt != NULL && DateSort(currentReceipt->nextReceipt, newReceipteipt) == 2)
		currentReceipt = currentReceipt->nextReceipt;

	if (currentReceipt->nextReceipt != NULL && DateSort(currentReceipt->nextReceipt, newReceipteipt) == 3)
	{
		ArticleMerge(currentReceipt->nextReceipt, newReceipteipt);
	}
	else
	{
		newReceipteipt->nextReceipt = currentReceipt->nextReceipt;
		currentReceipt->nextReceipt = newReceipteipt;
	}

	return 0;

}

int DateSort(PositionReceipt currentReceipt, PositionReceipt newReceipteipt) {

	if (currentReceipt->year > newReceipteipt->year)
		return 1;

	if (currentReceipt->year < newReceipteipt->year)
		return 2;

	else
	{
		if (currentReceipt->month > newReceipteipt->month)
			return 1;

		if (currentReceipt->month < newReceipteipt->month)
			return 2;

		else {

			if (currentReceipt->day > newReceipteipt->day)
				return 1;

			if (currentReceipt->day < newReceipteipt->day)
				return 2;

			else
				return 3;
		}
	}
}

int ArticleMerge(PositionReceipt Receipt, PositionReceipt newReceipt) {

	PositionArticle currentArticle = &(Receipt->ArticleHead);
	PositionArticle newCurrArticel = &(newReceipt->ArticleHead);
	PositionArticle temp;


	while (currentArticle != NULL && currentArticle->nextArticle != NULL)
	{
		while (newCurrArticel != NULL && newCurrArticel->nextArticle != NULL)
		{
			if (strcmp(currentArticle->nextArticle->article, newCurrArticel->nextArticle->article) == 0)
			{
				ArticleSum(currentArticle->nextArticle, newCurrArticel->nextArticle);
				temp = newCurrArticel->nextArticle;
				newCurrArticel->nextArticle = newCurrArticel->nextArticle->nextArticle;
				free(temp);

			}

			newCurrArticel = newCurrArticel->nextArticle;
		}
		currentArticle = currentArticle->nextArticle;
		newCurrArticel = &(newReceipt->ArticleHead);
	}
	newCurrArticel = &(newReceipt->ArticleHead);
	while (newCurrArticel != NULL && newCurrArticel->nextArticle != NULL)
	{
		SortArticles(Receipt, newCurrArticel->nextArticle->article, newCurrArticel->nextArticle->weight, newCurrArticel->nextArticle->price);
		temp = newCurrArticel->nextArticle;
		newCurrArticel->nextArticle = newCurrArticel->nextArticle->nextArticle;
		free(temp);

		newCurrArticel = newCurrArticel->nextArticle;
	}
	if (newReceipt->ArticleHead.nextArticle != NULL)
	{
		SortArticles(Receipt, newReceipt->ArticleHead.nextArticle->article, newReceipt->ArticleHead.nextArticle->weight, newReceipt->ArticleHead.nextArticle->price);
		free(newReceipt->ArticleHead.nextArticle);
	}
	free(newReceipt);


	return 0;

}

int Print(PositionReceipt HeadReceipt)
{
	PositionReceipt currentReceipt = HeadReceipt->nextReceipt;
	PositionArticle currentArticle = HeadReceipt->ArticleHead.nextArticle;

	while (currentReceipt != NULL)
	{
		printf("%d-%d-%d\n\n", currentReceipt->year, currentReceipt->month, currentReceipt->day);
		currentArticle = currentReceipt->ArticleHead.nextArticle;
		while (currentArticle != NULL)
		{
			printf("%s %d %.1f\n", currentArticle->article, currentArticle->weight, currentArticle->price);
			currentArticle = currentArticle->nextArticle;
		}
		currentReceipt = currentReceipt->nextReceipt;
		printf("\n\n\n");

	}
	return 0;

}

int BetweenDatesArticels(PositionReceipt HeadReceipt) {

	int year_s = 0, month_s = 0, day_s = 0;
	int year_e = 0, month_e = 0, day_e = 0;
	int sum_weight = 0, sum_price = 0;
	char article[MAX_LENGTH] = { 0 };
	PositionReceipt ReceiptBetween_s = NULL;
	PositionReceipt ReceiptBetween_e = NULL;
	PositionReceipt currentReceipt = HeadReceipt->nextReceipt;
	PositionArticle currentArticle = NULL;

	printf("Unesite artikl: ");
	scanf("%s", article);

	printf("Unesite pocetni datum YY.MM.DD: ");
	scanf("%d.%d.%d", &year_s, &month_s, &day_s);
	ReceiptBetween_s = CreateReceipt(ReceiptBetween_s, year_s, month_s, day_s);

	printf("Unesite krajnji datum YY.MM.DD: ");
	scanf("%d.%d.%d", &year_e, &month_e, &day_e);
	ReceiptBetween_e = CreateReceipt(ReceiptBetween_e, year_e, month_e, day_e);

	if (!ReceiptBetween_e || !ReceiptBetween_s)
		return -1;

	while (currentReceipt != NULL)
	{
		currentArticle = currentReceipt->ArticleHead.nextArticle;
		while (currentArticle != NULL)
		{
			if (strcmp(currentArticle->article, article) == 0 && (DateSort(currentReceipt, ReceiptBetween_s) == 1) && (DateSort(currentReceipt, ReceiptBetween_e) == 2))
			{
				sum_weight += currentArticle->weight;
				sum_price += currentArticle->price;

			}
			currentArticle = currentArticle->nextArticle;
		}
		currentReceipt = currentReceipt->nextReceipt;
	}
	printf("\nUkupna kolicina artikla %s: %d\nUkupna cijena artikla %s:  %d", article, sum_weight, article, sum_price);

	return 0;

}