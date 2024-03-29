#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

struct struktura;
typedef struct struktura* Position;
typedef struct struktura {
int broj;
Position next;
}Struktura;

int NasumicniBroj(int, int);
int Push(Position, int, int);
int Pop(Position, int);
void Ispis(Position, int);

void main(void)
{
srand((unsigned)time(NULL));

Struktura head;
head.next = NULL;

int izbor = 0;
int x = 0;
int velicinaStoga = 0;


while (velicinaStoga == 0)
{
printf("\n\nUnesite velicinu stoga(od 5 do 10):\n");
scanf(" %d", &velicinaStoga);
if (velicinaStoga < 5 || velicinaStoga > 10)
{
velicinaStoga = 0;
printf("\n\nGreska kod unosa!");
}
}

while (izbor != 3)
{
printf("\n\t1 - push");
printf("\n\t2 - pop");
printf("\nUnesite 3 za kraj programa!");
printf("\n\n\tIzbor : ");
scanf_s(" %d", &izbor);

switch (izbor)
{
case 1:
if (x < velicinaStoga)
x = Push(&head, NasumicniBroj(10, 100), x);
else
printf("\n\nStog je pun!\n\n");
Ispis(head.next, x);
break;
case 2:
if (x > 0)
x = Pop(&head, x);
Ispis(head.next, x);
break;
case 3:
printf("\n\nSayonara!\n\n");
break;
default:
printf("\n\nPogresan izbor!\n\nDe ponovno.\n\n");
}
}


}

int NasumicniBroj(int min, int max)
{
int x = 0;

x = rand() % (max - min) + min;

return x;
}

int Push(Position head, int x, int y)
{
static Position zadnji = NULL;
Position noviElement;

noviElement = (Position)malloc(sizeof(Struktura));
if (noviElement != NULL)
{
if (head->next == NULL)
zadnji = noviElement;

noviElement->broj = x;

printf("\n\nNa listu ide %d.", x);
noviElement->next = head->next;
head->next = noviElement;

zadnji->next = noviElement;
y++;
}
return y;
}

int Pop(Position head, int x)
{
static Position zadnji = NULL;
Position temp;

if (head->next != NULL)
{

temp = head->next;

printf("\n\nSa liste odlazi %d.", temp->broj);

head->next = temp->next;

if (zadnji == NULL && x > 1)
{
while (head->next != temp)
head = head->next;
zadnji = head;
}

zadnji->next = temp->next;

free(temp);
x--;
if (x == 0)
zadnji = NULL;
}
else
printf("\n\nLista je prazna!");

return x;
}

void Ispis(Position prvi, int x)
{
printf("\n\nU listi se nalazi %d elemenata:\n", x);
while (x > 0)
{
printf(" %d",prvi->broj);
prvi = prvi->next;
x--;
}
}
