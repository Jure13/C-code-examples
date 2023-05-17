#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN 1
#define MAX 20

typedef struct struktura* Position;
typedef struct struktura
{
	int broj;
	Position next;
}Struktura;

int Izbornik(Position, Position);
int ProcitajDatoteku(Position);
Position NoviElement();
int SortiraniUnos(Position, int);

int Unija(Position, Position, Position);
int Presjek(Position, Position, Position);
int SortiraniUnosSProvjerom(Position, int);

void IspisListe(Position);

int main()
{
	srand((unsigned)time(NULL));
	int unos = 0; int prviBroj = 0; int drugiBroj = 0; int rezultat = 0;
	Struktura head1 = { 0 };
	Struktura head2 = { 0 };
	Struktura headUnije = { 0 };
	Struktura headPresjeka = { 0 };

	Position noviElement1 = NULL; Position noviElement2 = NULL;

	head1.next = NULL;
	head2.next = NULL;
	headUnije.next = NULL;
	headPresjeka.next = NULL;

	rezultat = Izbornik(&head1, &head2);

	printf("\nPrva i druga lista:\n");
	IspisListe(head1.next);
	IspisListe(head2.next);

	printf("\nStvaranje unije i presjeka:\n");

	rezultat = Unija(head1.next, head2.next, &headUnije);
	if (rezultat == 1)
		printf("\nUnija uspjesno odradena!\n");
	
	IspisListe(headUnije.next);

	rezultat = Presjek(head1.next, head2.next, &headPresjeka);
	if (rezultat == 1)
		printf("\nPresjek uspjesno odraden!\n");

	IspisListe(headPresjeka.next);

	printf("\nKraj programa!\n");
	scanf(" %d", unos);
	return 0;
}

int Izbornik(Position head1, Position head2)
{
	int rezultat = 0;

	printf("\n\n");

		rezultat = ProcitajDatoteku(head1);
		
		if (rezultat == 1)
			printf("\nPrva datoteka uspjesno ucitana!\n");
		else
			printf("\nGreska s ucitavanjem prve datoteke!\n");

		rezultat = ProcitajDatoteku(head2);
		if (rezultat == 1)
			printf("\nDruga datoteka uspjesno ucitana!\n");
		else
			printf("\nGreska s ucitavanjem druge datoteke!\n");
	
	return 1;
}

int ProcitajDatoteku(Position head)
{
	FILE* fp = NULL;
	int noviBroj = 0;
	char ime[20];

	printf("\nUnesi ime datoteke:\n");
	scanf(" %s", ime);

	fp = fopen(ime, "r");
	if (fp == NULL) {
		printf("Greska prilikom otvaranja datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{

		fscanf(fp, "%d", &noviBroj);

		SortiraniUnos(head, noviBroj);

	}
	printf("\nLista ucitana!\n");
	fclose(fp);
	return 1;
}

Position NoviElement()
{
	Position noviElement = NULL;
	noviElement = (Position)malloc(sizeof(Struktura));

	if (noviElement == NULL) {
		printf("Greska kod alokacije memorije novog elementa!");
		return NULL;
	}
	
	return noviElement;
}

int SortiraniUnos(Position noviHead, int noviBroj) {
	Position noviElement = NULL;
	noviElement = NoviElement();
	noviElement->broj = noviBroj;

	while (noviHead->next != NULL) {

		if (noviElement->broj < noviHead->next->broj)
			break;
		noviHead = noviHead->next;
	}

	noviElement->next = noviHead->next;
	noviHead->next = noviElement;

	return 1;
}

void IspisListe(Position element)
{
	if (element == NULL)
	{
		printf("\nLista je prazna!\n");
		return;
	}

	while (element != NULL)
	{
		printf(" %d ", element->broj);
		element = element->next;
	}
	printf("\nKraj liste!\n");
}

int Unija(Position prva, Position druga, Position headUnije)
{
	Position noviElement = NULL;
	while (prva != NULL && druga != NULL)
	{
		if (prva->broj < druga->broj)
		{
			noviElement = NoviElement();
			noviElement->broj = prva->broj;
			SortiraniUnosSProvjerom(headUnije, noviElement->broj);
			prva = prva->next;
		}
		else if (druga->broj < prva->broj)
		{
			noviElement = NoviElement();
			noviElement->broj = druga->broj;
			SortiraniUnosSProvjerom(headUnije, noviElement->broj);
			druga = druga->next;
		}
		else if (prva->broj == druga->broj)
		{
			noviElement = NoviElement();
			noviElement->broj = prva->broj;
			SortiraniUnosSProvjerom(headUnije, noviElement->broj);
			prva = prva->next;
			druga = druga->next;
		}
	}
	if (prva == NULL)
	{
		while (druga != NULL)
		{
			noviElement = NoviElement();
			noviElement->broj = druga->broj;
			SortiraniUnosSProvjerom(headUnije, noviElement->broj);
			druga = druga->next;
		}
	}
	else if (druga == NULL)
	{
		while (prva != NULL)
		{
			noviElement = NoviElement();
			noviElement->broj = prva->broj;
			SortiraniUnosSProvjerom(headUnije, noviElement->broj);
			prva = prva->next;
		}
	}
	return 1;
}

int SortiraniUnosSProvjerom(Position noviHead, int noviBroj) {
	Position noviElement = NULL;
	noviElement = NoviElement();
	noviElement->broj = noviBroj;

	while (noviHead->next != NULL) {

		if (noviElement->broj <= noviHead->next->broj)
			break;
		noviHead = noviHead->next;
	}

	noviElement->next = noviHead->next;
	noviHead->next = noviElement;

	return 1;
}

int Presjek(Position prva, Position druga, Position headPresjeka)
{
	Position noviElement = NULL;
	while (prva != NULL && druga != NULL)
	{
		if (prva->broj > druga->broj)
		{
			prva = prva->next;
		}
		else if (prva->broj < druga->broj)
		{
			druga = druga->next;
		}
		else
		{
			noviElement = NoviElement();
			noviElement->broj = prva->broj;

			/*SortiraniUnosSProvjerom(headPresjeka, noviElement->broj);
			prva = prva->next;
			druga = druga->next;
			headPresjeka = headPresjeka->next;*/

			noviElement->next = headPresjeka->next;
			headPresjeka->next = noviElement;
			headPresjeka = noviElement;

			prva = prva->next;
			druga = druga->next;
		}
	}
	return 1;
}
