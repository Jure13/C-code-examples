#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

struct struktura;
typedef struct struktura* Position;
typedef struct struktura {
	int broj;
	int pri; //prioritet
	Position next;
}Struktura;

/*
	Red s prioritetom
*/

int NasumicniBroj(int, int);
Position PronadiZadnjeg(Position);
Position NoviElement();
int Push(Position);
int Pop(Position);
int Ispis(Position);
void DealocirajMemoriju(Position);

int main()
{
	Struktura head = { 0 };

	head.next = NULL;

	srand((unsigned)time(NULL));

	int unos = 10; int rezultat = 0;

	printf("Pocetak programa!\n");

	while (unos != 0)
	{
		printf("0 - kraj programa\n");
		printf("1 - push reda\n");
		printf("2 - pop reda \n");
		scanf(" %d", &unos);

		switch (unos)
		{
		case 0: {
			break;
		}
		case 1:
		{
			rezultat = Push(&head);
			if (rezultat == 1)
				printf("\nPush reda uspjesan!\n");
			else
				printf("\nGreska kod pusha reda!\n");
			rezultat = Ispis(head.next);
			if (rezultat == 1)
				printf("\nIspis nakon pusha reda uspjesan!\n");
			else
				printf("\nGreska kod ispisa pushanog reda!\n");
			break;
		}
		case 2: {
			rezultat = Pop(&head);
			if (rezultat == 1)
				printf("\nPop reda uspjesan!\n");
			else
				printf("\nGreska kod popa reda!\n");
			rezultat = Ispis(head.next);
			if (rezultat == 1)
				printf("\nIspis nakon popa reda uspjesan!\n");
			else
				printf("\nGreska kod ispisa popanog reda!\n");
			break;
		}
		default:
			printf("\nUnesi normalan broj -_- ...\n");
			break;
		}
	}
	printf("\nSee you on the other side ;)\n");
	scanf(" %d", unos);

	DealocirajMemoriju(&head);
	return 0;
}

int NasumicniBroj(int min, int max)
{
	int x = 0;

	x = rand() % (max - min) + min;

	return x;
}

int Push(Position head)
{
	static Position zadnji = PronadiZadnjeg(head);
	Position noviElement = NoviElement();
	printf("\nZa novi element reda memorija uspjesno alocirana!\n");

	if (noviElement != NULL)
	{
		noviElement->next = zadnji->next;
		zadnji->next = noviElement;
		return 1;
	}
	return 0;
}

Position PronadiZadnjeg(Position head)
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	return head;
}

Position NoviElement()
{
	Position noviElement = NULL;
	noviElement = (Position)malloc(sizeof(Struktura));

	if (noviElement != NULL)
	{
		noviElement->broj = NasumicniBroj(1, 10);
		noviElement->pri = NasumicniBroj(1, 5);
		noviElement->next = NULL;

		return noviElement;
	}
	printf("\nGreska kod stvaranja novog elementa!\n");
	return NULL;
}

int Pop(Position head)
{
	Position temp = NULL;
	if (head->next == NULL)
	{
		printf("\nGreska kod ucitavanja liste kod popa!\n");
		return 0;
	}
	else
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return 1;
}

int Ispis(Position prvi)
{
	int max = 0; //maksimalna vrijednost za provjeru prioriteta
	static Position pocetak = prvi;
	
	if (prvi == NULL)
	{
		printf("\nLista je prazna!\n");
		return 0;
	}

		while (prvi != NULL)
		{
			if (prvi->pri > max)
				max = prvi->pri;
			prvi = prvi->next;
		}

		prvi = pocetak;

		while(prvi->pri == max)
		{
			printf(" %d", prvi->broj);
			prvi = prvi->next;
			
			max--;
		}
	
	return 1;
}

void DealocirajMemoriju(Position head)
{
	Position temp = NULL;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}
