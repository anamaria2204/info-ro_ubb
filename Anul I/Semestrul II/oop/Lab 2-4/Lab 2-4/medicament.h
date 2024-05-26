#pragma once

typedef struct {
	int cod;
	char nume[50];
	int concentratie;
	int cantitate;
} Medicament;

/*
Creaza un nou medicament
*/

Medicament creazaMedicament(int cod, char* nume, int concentratie, int cantitate);

/*
Dealocam memoria ocupata de medicament
*/

void distrugeMedicament(Medicament* m);

void testCreazaDistruge();

int valideaza(Medicament);