#pragma once

#include "medicament.h"
typedef Medicament ElemType;

typedef struct {
	ElemType medicament[50];
	int lg;
} MedList;

/*
Cream o lista goala
*/

MedList creazaGol();

/*
Distrugem lista
*/
void distrugeLista(MedList* l);

/*
Functia care returneaza elemente din lista
poz - pozitia elementului dorit, trebuie sa fie valid
return: elementul de pe pozitia dorita
*/

ElemType get(MedList* l, int poz);

/*
Functia seteaza un medicament modificand unii parametrii
*/
void set(MedList* l, int index, ElemType medicament);

/*
Functia returneaza numarul de elemente al listei de medicamente
*/

int size(MedList* l);


/*
Functia face o copie a listei de medicamente
*/
MedList copy(MedList* l);

/*
Functia cauta un medicament in lista farmaciei
*/
int cauta(MedList* l, ElemType medicament);

/*
cauta un medicament dupa un parametru dat: cod
*/

int cautaCod(MedList* l, int cod);

/*
Functia adauga medicamente in lista de medicamente
post: medicamentul este adaugat la finalul listei
*/
void adauga(MedList* l, ElemType medicament);

/*
Functia modifica cantitatea unui medicament dat
*/
void modificaCantitate(MedList* l, ElemType medicament, int poz, int cantitateNoua);

/*
Functia modifica numele si concentratia unui medicament
*/

void modifica(MedList* l, ElemType medicament, int poz, char* numeNou, int concentratieNoua);


/*
Functia sterge stocul unui medicament dat
*/

void sterge(MedList* l, ElemType medicament, int poz);

/*
teste
*/

void testCreazaLista();
void testAdaugaLista();
void testModificaCantitateLista();
void testModificaLista();
void testCautaLista();
void testCautaCodLista();
void testStergeLista();
void testCopyLista();