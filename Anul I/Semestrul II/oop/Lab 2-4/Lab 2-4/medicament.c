# include "medicament.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

/*
Creaza un nou medicament
*/

Medicament creazaMedicament(int cod, char* nume, int concentratie, int cantitate) {
	Medicament rez;
	rez.cod = cod;
	strcpy_s(rez.nume, sizeof(rez.nume), nume);
	rez.concentratie = concentratie;
	rez.cantitate = cantitate;
	return rez;
}

/*
Dealocam memoria ocupata de medicament
*/

void distrugeMedicament(Medicament* m) {
	m->cod = -1;
	m->nume[0] = '\0';
	m->concentratie = -1;
	m->cantitate = -1;
}

int valideaza(Medicament m) {
	if (m.cod < 0) {
		return 1;
	}
	if (strlen(m.nume) == 0) {
		return 2;
	}
	if (m.concentratie < 0) {
		return 3;
	}
	if (m.cantitate < 0) {
		return 4;
	}
	return 0;
}


/*
Testam functiile de creare si distrugere
*/

void testCreazaDistruge() {
	Medicament m = creazaMedicament(12, "algocalmin", 10, 20);
	assert(m.cod == 12);
	assert(strcmp(m.nume, "algocalim"));
	assert(m.concentratie == 10);
	assert(m.cantitate == 20);

	distrugeMedicament(&m);
	assert(m.cod == -1);
	assert(strlen(m.nume) == 0);
	assert(m.concentratie == -1);
	assert(m.cantitate == -1);
}