#define _CRT_SECURE_NO_WARNINGS
#define datoteka "text.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct struktura;
typedef struct struktura* Position;
typedef struct struktura {
	char ime[25];
	char prezime[25];
	int godRod;
	Position next;
}Osoba;

Position NoviElement();
int UnesiNaPocetak(Position);
int IspisListe(Position);
int UnesiNaKraj(Position);
Position NadiZadnji(Position);
Position PronadiElement(Position);
int IzbrisiElement(Position);
Position PronadiPrethodni(Position, Position);

int DodajIza(Position);
int DodajIspred(Position);
int Sortiraj(Position);
void UpisiUDat(Position);
int CitajIzDat(Position);

int main()
{
	int kraj = 0; int izbor = 0; int rezultat = 0;
	Osoba head = { 0 };
	head.next = NULL;

	printf("Odaberite, molim:\n");

	printf("0 - Izlaz iz petlje!\n");
	printf("1 - Dodaj na pocetak\n2 - Ispisi\n3 - Dodaj na kraj\n4 - Pronadi element po prezimenu\n5 - Brisi odredeni element\n");
	printf("6 - Dodaj iza odredenog\n7 - Dodaj ispred odredenog\n8 - Sortiraj listu\n9 - Upisi listu u datoteku\n10 - Citaj listu iz datoteke\n");

	while (1) {
		scanf(" %d", &izbor);

		switch (izbor)
		{
		case 0: { return 0;
			break;	}
		case 1: { rezultat = UnesiNaPocetak(&head);
			if (rezultat == 1)
				printf("\nUnos na pocetak uspjesan!\n");
			break;	}
		case 2: { rezultat = IspisListe(head.next);
			if (rezultat == 1)
				printf("\nIspis uspjesan!\n");
			break;	}
		case 3: {rezultat = UnesiNaKraj(&head);
			if (rezultat == 1)
				printf("\nUnos na kraj uspjesan!\n");
			break;	}
		case 4: { PronadiElement(head.next);
			break; }
		case 5: { rezultat = IzbrisiElement(&head);
			if (rezultat == 1)
				printf("\nBrisanje uspjesno!\n");
			break; }
		case 6: { rezultat = DodajIza(&head);
			if (rezultat == 1)
				printf("\nUnos iza uspjesan!\n");
			break;	}
		case 7: { rezultat = DodajIspred(&head);
			if (rezultat == 1)
				printf("\nUnos ispred uspjesan!\n");
			break; }
		case 8: { rezultat = Sortiraj(&head);
			if (rezultat == 1)
				printf("\nSortiranje uspjesno!\n");
			break; }
		case 9: {UpisiUDat(head.next);
			break;	}
		case 10: { rezultat = CitajIzDat(&head);
			if (rezultat == 1)
				printf("\nCitanje iz datoteke uspjesno!\n");
			break; }
		default:
			printf("Unesi pravi broj!! \n");
			break;
		}
	}
	return 0;
}

Position NoviElement()
{
	Position noviElement = NULL;
	noviElement = (Position)malloc(sizeof(Osoba));
	noviElement->next = NULL;

	return noviElement;	
}

int UnesiNaPocetak(Position head)
{
	Position noviElement = NoviElement();

	printf("Upisite ime osobe:");
	scanf(" %s", noviElement->ime);
	printf("Upisite prezime osobe:");
	scanf(" %s", noviElement->prezime);
	printf("Upisite godinu rodenja osobe:");
	scanf(" %d", &noviElement->godRod);

	noviElement->next = head->next;
	head->next = noviElement;

	return 1;
}

int IspisListe(Position prvi)
{
	if (prvi == NULL)
	{
		printf("\nPrazno!\n");
		return 0;
	}
	while (prvi != NULL)
	{
		printf("\nIme: %s \n", prvi->ime);
		printf("Prezime: %s \n", prvi->prezime);
		printf("Roden je: %d \n ", prvi->godRod);

		prvi = prvi->next;
	}

	return 1;
}

int UnesiNaKraj(Position head)
{
	Position noviElement = NULL;
	Position zadnji = NadiZadnji(head);
	noviElement = NoviElement();

	printf("Upisite ime osobe:");
	scanf(" %s", noviElement->ime);
	printf("Upisite prezime osobe:");
	scanf(" %s", noviElement->prezime);
	printf("Upisite godinu rodenja osobe:");
	scanf(" %d", &noviElement->godRod);

	noviElement->next = zadnji->next;
	zadnji->next = noviElement;

	return 1;
}

Position NadiZadnji(Position head)
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	return head;
}

Position PronadiElement(Position osoba)
{
	Position temp = NULL;
	char posljednji[30] = { 0 };

	printf("Upisite prezime:");
	scanf(" %s", posljednji);


	while (osoba != NULL)
	{
		if (strcmp(osoba->prezime, posljednji) == 0)
		{
			printf("Osoba prezimena %s pronadena!\n", posljednji);
			printf("Ime: %s \n ", osoba->ime);
			printf("Prezime: %s \n ", osoba->prezime);
			printf("Godina rodenja: %d \n ", osoba->godRod);

			temp = osoba;
		}
		osoba = osoba->next;
	}
	if (temp == NULL)
	{
		printf("Nema nikoga \n");
	}
	return temp;
}

int IzbrisiElement(Position head)
{
	Position prethodni = NULL;
	Position izbrisi = PronadiElement(head);
	if (izbrisi == NULL)
	{
		printf("Nema se što izbrisati!");
		return 0;
	}

	prethodni = PronadiPrethodni(head, izbrisi);
	prethodni->next = izbrisi->next;

	free(izbrisi);

	return 1;
}

Position PronadiPrethodni(Position head, Position trenutni)
{

	while (head->next != trenutni)
	{
		head = head->next;
	}
	return head;

}

int DodajIza(Position head)
{
	Position trenutni = PronadiElement(head);
	if (trenutni != NULL)
	{
		Position noviElement = NoviElement();

		printf("Upisite ime osobe:");
		scanf(" %s", noviElement->ime);
		printf("Upisite prezime osobe:");
		scanf(" %s", noviElement->prezime);
		printf("Upisite godinu rodenja osobe:");
		scanf(" %d", &noviElement->godRod);

		noviElement->next = trenutni->next;
		trenutni->next = noviElement;
	}
	else
		printf("Nesto ne valja!\n");

	return 1;
}

int DodajIspred(Position head)
{
	Position trenutni = PronadiElement(head);
	Position prethodni = NULL;
	if (trenutni != NULL)
	{
		Position noviElement = NoviElement();

		printf("Upisite ime osobe:");
		scanf(" %s", noviElement->ime);
		printf("Upisite prezime osobe:");
		scanf(" %s", noviElement->prezime);
		printf("Upisite godinu rodenja osobe:");
		scanf(" %d", &noviElement->godRod);

		prethodni = PronadiPrethodni(head, trenutni);

		noviElement->next = prethodni->next;
		prethodni->next = noviElement;
	}
	else
		printf("Nesto ne valja!\n");

	return 1;
}

int Sortiraj(Position head)
{
	Position trenutni, prethodni;
	Position temp = NULL; Position kraj = NULL;

	while (head->next != kraj)
	{
		trenutni = head->next;
		prethodni = head;
		while (trenutni->next != kraj)
		{
			if (strcmp(trenutni->prezime, trenutni->next->prezime) > 0)
			{
				temp = trenutni->next;
				trenutni->next = temp->next;
				temp->next = trenutni;
				prethodni->next = temp;

				trenutni = temp;
			}
			prethodni = trenutni;
			trenutni = trenutni->next;
		}
		kraj = trenutni;
	}
	printf("Lista sortirana! \n");

	return 1;
}

void UpisiUDat(Position head)
{
	FILE* fp = NULL;

	fp = fopen(datoteka, "w");

	if (fp == NULL)
	{
		printf("Greška u otvaranju datoteke!\n");
	}


	if (head == NULL)
	{
		printf("Lista je prazna!\n");
		return;
	}

	while (head != NULL)
	{
		fprintf(fp, "%s %s %d \n", head->ime, head->prezime, head->godRod);
		head = head->next;
	}
	fclose(fp);

}

int CitajIzDat(Position head)
{
	Position noviElement = NULL;
	FILE* fp;

	fp = fopen(datoteka, "r");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(fp)) {
		noviElement = NoviElement();

		fscanf(fp, "%s %s %d", noviElement->ime, noviElement->prezime, &noviElement->godRod);

		noviElement->next = head->next;
		head->next = noviElement;

	}

	fclose(fp);
	return 1;
}
