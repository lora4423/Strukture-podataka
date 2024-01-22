#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1024

typedef struct S* Position;

typedef struct S {
	float operand;
	Position next;
}stack;

int ReadFile();
int PostfixCalc(char* line);
int Push(Position, float);
int Pop(Position);
int PrintStack(Position);
int Print(char*, Position, float);
Position AddOperand(Position);
int Operation(int, int, char, float*);

int main()
{
	ReadFile();

	return 0;
}

int ReadFile()
{
	FILE* filePointer = NULL;
	char line[MAX_SIZE] = "";

	filePointer = fopen("postfix_izraz.txt", "r");
	if (!filePointer) {
		return -1;
	}

	fgets(line, MAX_SIZE, filePointer);
	PostfixCalc(line);

	return 0;
}

int PostfixCalc(char* line)
{
	stack Head = { .operand = 0.0,.next = NULL };
	char operator = '\0', done[MAX_SIZE] = "\0", strOperand[MAX_SIZE] = "\0", strOperator[MAX_SIZE] = "\0";
	int value = 0, bytes = 0, counter = 0;
	float operand = 0.0, operand1 = 0.0, operand2 = 0.0, result = 0.0;

	while (strlen(line + bytes) > 0)
	{
		value = sscanf(line + bytes, "%f %n", &operand, &counter);
		if (value == 1)
		{
			bytes += counter;
			Push(&Head, operand);

		}
		else if (value == 0)
		{
			value = sscanf(line + bytes, " %c %n", &operator, &counter);
			bytes += counter;
			if (value == 1)
			{
				operand2 = Pop(&Head);
				operand1 = Pop(&Head);
				Operation(operand1, operand2, operator, &result);
				if (!Operation) {
					return -1;
				}

				Push(&Head, result);
			}
		}
		else
			return -1;

		Print(line + bytes, &Head, result);
	}
	return 0;
}

int Push(Position Head, float operand)
{
	Position New = NULL;
	New = AddOperand(New);
	if (!New)
		return -1;

	New->operand = operand;
	New->next = Head->next;
	Head->next = New;

	return 0;
}

int Pop(Position Head)
{
	Position temp = NULL;
	int operand = 0;

	if (Head->next != NULL)
	{
		temp = Head->next;
		operand = temp->operand;
		Head->next = Head->next->next;
		free(temp);

		return operand;
	}

	return -1;
}

int Operation(int operand1, int operand2, char operator, float* result)
{

	switch (operator)
	{
	case '+':
		*result = operand1 + operand2;
		break;

	case '-':
		*result = operand1 - operand2;
		break;

	case '*':
		*result = operand1 * operand2;
		break;

	case '/':
		*result = operand1 / operand2;
		break;

	default:
		printf("\nNe postoji!\n");
		return -1;
	}

	return 0;
}

int PrintStack(Position Head)
{
	printf("Stog: ");
	Position current = Head->next;

	while (current != NULL)
	{
		printf("%.f ", current->operand);
		current = current->next;
	}

	return 0;
}

int Print(char* toCalc, Position Head, float result)
{
	printf("Preostalo: %s", toCalc);
	PrintStack(Head);
	printf("\nResult: %.1f", result);
	printf("\n\n");
}

Position AddOperand(Position New)
{
	New = (Position)malloc(sizeof(stack));

	return New;
}