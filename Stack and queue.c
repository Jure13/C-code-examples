/*
6. Napisati program koji pomoæu vezanih listi simulira rad:
a) stoga,
b) reda.
Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 -100
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

struct struktura;
typedef struct struktura* Position;
typedef struct struktura {
	int broj;
	Position next;
}Struktura;

Position NoviElement();
int NasumicniBroj();

int PushRed(Position);
//int PopRed(Position);
int PushStog(Position);
//int PopStog(Position);

int Pop(Position);

Position PronadiZadnjeg(Position);

int IspisiListu(Position);

void DealocirajMemoriju(Position);

int main()
{
	Struktura headReda = { 0 };
	Struktura headStoga = { 0 };

	headReda.next = NULL;
	headStoga.next = NULL;

	srand((unsigned)time(NULL));

	int unos = 10; int rezultat = 0;

	printf("Pocetak programa!\n");

	while (unos != 0)
	{
		printf("0 - kraj programa\n");
		printf("1 - push reda\n");
		printf("2 - pop reda \n");
		printf("3 - push stoga\n");
		printf("4 - pop stoga\n\n");
		scanf(" %d", &unos);

		switch (unos)
		{
			case 0: {
				break;
			}
			case 1: 
			{
				rezultat = PushRed(&headReda);
				if (rezultat == 1)
					printf("\nPush reda uspjesan!\n");
				else
					printf("\nGreska kod pusha reda!\n");
				rezultat = IspisiListu(headReda.next);
				if (rezultat == 1)
					printf("\nIspis nakon pusha reda uspjesan!\n");
				else
					printf("\nGreska kod ispisa pushanog reda!\n");
				break;
			}
			case 2: {
				rezultat = Pop(&headReda);
				if (rezultat == 1)
					printf("\nPop reda uspjesan!\n");
				else
					printf("\nGreska kod popa reda!\n");
				rezultat = IspisiListu(headReda.next);
				if (rezultat == 1)
					printf("\nIspis nakon popa reda uspjesan!\n");
				else
					printf("\nGreska kod ispisa popanog reda!\n");
				break;
			}
			case 3: {
				rezultat = PushStog(&headStoga);
				if (rezultat == 1)
					printf("\nPush stoga uspjesan!\n");
				else
					printf("\nGreska kod pusha stoga!\n");
				rezultat = IspisiListu(headReda.next);
				if (rezultat == 1)
					printf("\nIspis nakon pusha stoga uspjesan!\n");
				else
					printf("\nGreska kod ispisa pushanog stoga!\n");
				break;
			}
			case 4: {
				rezultat = Pop(&headStoga);
				if (rezultat == 1)
					printf("\nPop stoga uspjesan!\n");
				else
					printf("\nGreska kod popa stoga!\n");
				rezultat = IspisiListu(headStoga.next);
				if (rezultat == 1)
					printf("\nIspis nakon popa stoga uspjesan!\n");
				else
					printf("\nGreska kod ispisa popanog stoga!\n");
				break;
			}
		
			default:
				printf("\nUnesi normalan broj -_- ...\n");
				break;
		}
	}
	printf("\nSee you on the other side ;)\n");
	scanf(" %d", unos);

	DealocirajMemoriju(&headReda);
	DealocirajMemoriju(&headStoga);

}

Position NoviElement()
{
	Position noviElement = NULL;
	noviElement = (Position)malloc(sizeof(Struktura));

	if (noviElement != NULL)
	{
		noviElement->broj = NasumicniBroj();
		noviElement->next = NULL;

		return noviElement;
	}
	printf("\nGreska kod stvaranja novog elementa!\n");
	return NULL;
}

int NasumicniBroj()
{
	int broj = 0;

	broj = rand() % 91 + 10;

	return broj;
}

int IspisiListu(Position prvi)
{
	if (prvi == NULL)
	{
		printf("\nLista je prazna!\n");
		return 0;
	}
	printf("\n");
	while (prvi != NULL)
	{
		printf("%d\t", prvi->broj);
		prvi = prvi->next;
	}
	return 1;
}

int PushRed(Position head)
{
	Position zadnji = PronadiZadnjeg(head);
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

int PushStog(Position head)
{
	Position noviElement = NoviElement();
	printf("\nZa novi element stoga memorija uspjesno alocirana!\n");
	if (noviElement != NULL)
	{
		noviElement->next = head->next;
		head->next = noviElement;
		return 1;
	}
	return 0;
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
