/* Napisati program koji omoguæava rad s binarnim stablom pretraživanja.
Treba omoguæiti unošenje novog elementa u stablo, ispis elemenata
(inorder, preorder, postorder i level order), brisanje i pronalaženje nekog elementa.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct node node;
typedef struct node* position;

struct node {
	int val;
	position left;
	position right;
};

typedef struct _element* positionList;
typedef struct _element {
	position listElement;
	positionList next;
}element;

position createNode(int val);
position insert(position root, int val);

int Inorder(position root);
int Preorder(position root);
int Postorder(position root);

position searchNode(position root, int val);
position deleteNode(position root, int val);
position Min(position root);

int main() {

	int rootVal = 0;
	int choice;
	position root = NULL;
	printf("Vrijednost root-a:\n");
	scanf("%d", &rootVal);
	root = insert(root, rootVal);
	while (1) {
		printf("Odaberite sto zelite:\n 1- Unijeti novu vrijednost\n 2- Inorder ispis\n 3- Preorder ispis\n 4- Postorder ispis\n 5- Pretrazivanje elementa\n 6- Brisanje elementa iz stabla\n");
		scanf("%d", &choice);
		if (choice == 1) {
			int value = 0;
			printf("Unesite vrijednost:\n");
			scanf("%d", &value);
			root = insert(root, value);
		}
		else if (choice == 2) {
			printf("Inorder ispis:\n");
			root = Inorder(root);
		}
		else if (choice == 3) {
			printf("Preorder ispis:\n");
			root = Preorder(root);
		}
		else if (choice == 4) {
			printf("Postorder ispis:\n");
			root = Postorder(root);
		}
		else if (choice == 5) {
			int value = 0;
			printf("Koju vrijednost zelite pretraziti:\n");
			scanf("%d", &value);
			position result = NULL;
			result = searchNode(root, value);
			if (result != NULL)
				printf("\nPronaden je element %d.\n", value);
			else
				printf("Element %d nije pronaden.\n", value);

		}
		else if (choice == 6) {
			int val = 0;
			printf("Unesite element koji zelite obrisati:\n");
			scanf("%d", &val);
			deleteNode(root, val);
		}

		else {
			printf("Pogresan odabir.\n");
		}
	}
	

	node* root = NULL;

	int a[] = { 2,5,7,8,11,1,4,2,3,7 };

	replace(root);

	inOrderFile(root, "text.txt");

	
	node* rRoot = NULL;

	int value = 0;

	for (int i = 0; i < 10; i++) {
		value = 10 + rand();
		if (value > 90) {
			value = value % 91;
		}
		rRoot = insertNode(rRoot, value);
	}

	inOrderFile(rRoot, "text.txt");


	return 0;
}
position createNode(int val) {
	position newnode = NULL;
	newnode = (position)malloc(sizeof(struct node));
	if (newnode == NULL) {
		printf("Greska pri alociranju memorije.\n");
		return NULL;
	}
	newnode->val = val;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;

}
position insert(position root, int val) {

	if (root == NULL) {
		root = createNode(val);
	}
	else if (val < root->val) {
		root->left = insert(root->left, val);
	}
	else if (val > root->val) {
		root->right = insert(root->right, val);
	}
	return root;
}
int Inorder(position root) {
	if (root != NULL) {
		root->left = Inorder(root->left);
		printf("%d ", root->val);
		root->right = Inorder(root->right);
	}
	return 0;
}
int Preorder(position root) {
	if (root != NULL) {
		printf("%d ", root->val);
		root->left = Preorder(root->left);
		root->right = Preorder(root->right);
	}
	return 0;
}
int Postorder(position root) {
	if (root != NULL) {
		root->left = Postorder(root->left);
		root->right = Postorder(root->right);
		printf("%d ", root->val);
	}
	return 0;
}
position searchNode(position root, int val) {
	if (root == NULL) {
		return NULL;
	}
	else if (val < root->val) {
		return searchNode(root->left, val);
	}
	else if (val > root->val) {
		return searchNode(root->right, val);
	}
	else
		return root;

}

position deleteNode(position root, int val) {
	if (root == NULL) {
		return root;
	}
	else if (val < root->val) {
		root->left = deleteNode(root->left, val);
	}
	else if (val > root->val) {
		root->right = deleteNode(root->right, val);
	}
	else {
		if (root->left == NULL) {
			position temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			position temp = root->left;
			free(root);
			return temp;
		}

		//dvoje djece
		position temp = Min(root->right);
		root->val = temp->val;
		root->right = deleteNode(root->right, temp->val);
	}
	return root;
}

position Min(position root) {
	if (root == NULL) {
		return NULL;
	}
	else {
		if (root->left == NULL) {
			return root;
		}
		else {
			return findMin(root->left);
		}
	}
}

/*9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u èvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraæa
pokazivaè na korijen stabla.
b) Napisati funkciju replace koja æe svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat æe se u stablo na
slici Slika 2.
c) Prepraviti program na naèin da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira sluèajne brojeve u rasponu <10, 90>. Takoðer, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.*/

position Delete(position root); 
int replace(position root); 

int random(); 
int levelOrderFile(position root, FILE* filePointer); 
positionList addToTheEnd(positionList head, position newVal);
positionList deleteList(positionList head);

int replace(position root)
{
	if (root == NULL)
	{
		return 0;
	}
	int leftVal = 0, rightVal = 0, originalVal = 0;
	originalVal = root->val;

	leftVal = replace(root->left);
	rightVal = replace(root->right);
	root->val = leftVal + rightVal;

	return originalVal + root->val;
}

int random()
{
	int value = 0;
	value = rand() % 81 + 10;
	return value;

}int inOrderFile(position root, FILE* filePointer)
{
	if (root != NULL)
	{
		positionList head = NULL, temp = NULL;
		head = malloc(sizeof(element));

		if (head == NULL) {
			return NULL;
		}
		head->listElement = root;
		head->next = NULL;

		while (head != NULL) {
			fprintf(filePointer, "%d ", head->listElement->val);
			if (head->listElement->left != NULL)
				head = addToTheEnd(head, head->listElement->left);
			if (head->listElement->right != NULL)
				head = addToTheEnd(head, head->listElement->right);
			head = head->next;
		}

		head = temp;
		deleteList(head);
	}
	fprintf(filePointer, "\n");

	return EXIT_SUCCESS;

}positionList addToTheEnd(positionList head, position newVal)
{
	positionList newElement = NULL, first = NULL;
	first = head;

	while (first->next != NULL)
		first = first->next;

	newElement = malloc(sizeof(element));

	if (newElement == NULL)
	{
		return NULL;
	}
	newElement->listElement = newVal;
	newElement->next = NULL;
	first->next = newElement;
	return head;
}

positionList deleteList(positionList head)
{
	if (head == NULL) {
		return NULL;
	}

	head->next = Delete(head->next);
	free(head);

	return NULL;
}

position Delete(position root)
{
	if (root == NULL) {
		return NULL;
	}
	root->left = Delete(root->left);
	root->right = Delete(root->right);
	free(root);
	return NULL;
}