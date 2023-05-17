#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<string.h>
#include<time.h>


/*
	Raèunanje postfixa stoga vezanom listom.
*/


struct struktura;
typedef struct struktura* Position;
typedef struct struktura
{
	int broj;
	Position next;
}Struktura;

int CitajDatoteku(Position);
int Push(Position, int);
int Pop(Position);
int Izracunaj(int, int, char);

int main()
{
	Struktura head;
	head.next = NULL;
	int rezultat = 0;

	rezultat = CitajDatoteku(&head);
	if (rezultat == 1)
		printf("\nSve uspjesno odradeno!\n");
	
	rezultat = (head.next)->broj;
	printf("\nKrajnji rezultat stoga: %d\n", rezultat);
	free(head.next); //Samo je jedan èlan ostao, nema potrebe za (klasiènom) funkcijom "Dealokacija memorije"

	return 0;
}

int CitajDatoteku(Position head) {
	FILE* fp;
	char imeDatoteke[1024] = { 0 };
	int rezultat = 0; //za provjeru izvrsetka funkcije
	char buffer[32] = { 0 };
	int provjera = 0;
	int op1 = 0;
	int op2 = 0;
	int rez = 0; // za racunanje stoga

	printf("\nUnesi ime datoteke:\n");
	scanf_s(" %s", imeDatoteke, 1024);

	fp = fopen(imeDatoteke, "r");
	if (fp == NULL)
		printf("\nGreska kod otvaranja datoteke!\n");
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, " %s", buffer, 32);
			printf(" %s", buffer);

			provjera = atoi(buffer); //pohrani samo brojeve u "provjera"
			if (provjera == 0 && buffer[0] != '0') //ako su slova (operacije), raèunaj
			{


				op1 = Pop(head);
				op2 = Pop(head);
				rez = Izracunaj(op1, op2, buffer[0]);
				rezultat = Push(head, rez);
				if (rezultat == 1)
					printf("\nPush rezultata uspjesno odraden!\n");
			}
			else // spremi broj
				rezultat = Push(head, provjera);
			if (rezultat == 1)
				printf("\nPush operanda uspjesno odraden!\n");
		}
		fclose(fp);
	}
	return 1;
}

int Push(Position head, int broj)
{
	Position noviElement;

	noviElement = (Position)malloc(sizeof(Struktura));
	if (noviElement != NULL)
	{
		noviElement->broj = broj;
		noviElement->next =head->next;
		head->next = noviElement;

		return 1;
	}

	return 0;
}

int Pop(Position head)
{
	Position temp;
	int broj = 0;

	if (head->next == NULL)
	{
		printf("\nGreska kod head->next-a u funkciji Pop()!\nVraca nulu!\n");
		return 0;
	}
	if (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		broj = temp->broj;
		free(temp);
	}
	return broj;
}

int Izracunaj(int x, int y, char op)
{	//x i y su operandi, a op je operacija
	int z = 0; //zbroj/umnozak/kolicnik
	switch (op)
	{
	case '+':
		z = x + y;
		break;
	case '-':
		z = x - y;
		break;
	case '*':
		z = x * y;
		break;
	case '/':
		if (y != 0)
			z = x / y;
		else
		{
			printf("\nDijeljenje s nulom!\nKolicnik vraca nulu!\n");
			z = 0;
		}
		break;
	default:
		break;
	}
	return z;
}
