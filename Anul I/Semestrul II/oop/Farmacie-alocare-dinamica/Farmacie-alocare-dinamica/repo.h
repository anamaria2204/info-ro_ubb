#pragma once
#include "domeniu.h"

typedef void* ElemType;

typedef void(*destroy_fct)(ElemType);

typedef ElemType(*copy_fct)(ElemType);

typedef int(*egale_coduri)(ElemType, ElemType);

typedef int(*egale_fct)(ElemType, ElemType);

typedef int(*egal_modify)(ElemType, ElemType);

typedef void(*cantitate_fct)(ElemType, ElemType);

typedef int(*return_cod)(ElemType);

typedef void(*sterge_cant)(ElemType);

typedef void(*print_fct)(ElemType);

typedef struct {
	ElemType* medicament;
	int lungime;
	int capacitate;
	destroy_fct dest;
} MedList;

/*
Cream o lista goala
Parametrii: f - pointer la functia de distrugere

Return:
Pointer la noua structura MedList sau NULL daca alocarea a esuat
*/

MedList* creazaGol(destroy_fct f);

/*
Functia distruge o lista
Parametrii:
lista care trebuie distrusa
*/
void distrugeLista(MedList* lista);

/*
Functia extinde capacitatea listei dubland-o
Parametrii:
- list : pointer catre lista a carei capacitate trebuie dublata
*/

void extinde(MedList* list);


/*
Adauga un medicament in lista de medicamente sau actualizeaza cantitatea unui medicament existent
Parametrii:
- list : pointer catre lista de medicamente
- medicament: medicamentul de adaugat in lista de medicamente
- ec - functie ce verifica daca doua medicamente au acelasi cod
- em - functie ce verifica daca doua medicamente sunt egale
- ac - functie ce modifica cantitatea unui medicament cu cantitatea unui alt medicament

Return:
- 1 daca medicamentul a fost adaugat cu succes in lista
- 0 daca exista deja un medicament in lista cu nume diferit

*/

int adauga(MedList* lista, ElemType* medicament, egale_fct eq, egale_coduri ec, cantitate_fct cant);

/*
functia modifica un medicament cu un alt medicament dat
Parametrii:
- lista : pointer catre lista de medicamente
- medicament: elementul cu care va fi modificat medicamentul dorit

Return:
 0 daca modificarea a fost realizata 1 altfel
*/

int modifica(MedList* lista, ElemType* medicament, egal_modify eg, cantitate_fct cant);

/*
  Sterge stocul pentru un medicament din lista data, pe baza codului medicamentului.
 
  Parametri:
      list: pointer catre structura MedList ce reprezinta lista de medicamente.
      cod: Codul unic al medicamentului pentru care sa fie sters stocul.
  Returneaza:
      0 daca stergerea a fost efectuata cu succes, altfel 1.
 */
int stergeStoc(MedList* lista, int cod, return_cod cd, sterge_cant sterge);

/*
 Facem o copie listei
 returneaza MedList care contine aceleasi elemente ca si list
*/
MedList* copieLista(MedList* lista, copy_fct cpy);
