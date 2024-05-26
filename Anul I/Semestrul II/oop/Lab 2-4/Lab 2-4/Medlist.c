#define _CRT_SECURE_NO_WARNINGS

#include "Medlist.h"

#include <assert.h>
#include <string.h>


/*
Functia creaza o lista goala
*/
MedList creazaGol() {
	MedList rez;
	rez.lg = 0;
	return rez;
}

/*
Functia distruge lista creata
*/
void distrugeLista(MedList* l) {
	l->lg = 0;
}

/*
Functia returneaza numarul de medicamente al listei
*/
int size(MedList* l) {
	return l->lg;
}

/*
Functia reurneaza un medicament din lista de medicamente 
de pe o pozitie data
poz - pozitia dorita
return: medicamentul de pe pozitia poz
*/
ElemType get(MedList* l, int poz) {
	return l->medicament[poz];
}


/*
Functia creeaza o lista a medicamentelor din farmacie
*/
MedList copy(MedList* l) {
	MedList rez = creazaGol();
	for (int i = 0; i < size(l); i++) {
		ElemType m = get(l, i);
		adauga(&rez, m);
	}
	return rez;
}

int cauta(MedList* l, ElemType medicament) {
	for (int i = 0; i < size(l); i++) {
		if (l->medicament[i].cod == medicament.cod && 
			(strcmp(l->medicament[i].nume, medicament.nume) == 0) &&
			l->medicament[i].concentratie == medicament.concentratie)
			return i;
	}
	return -1;
}

int cautaCod(MedList* l, int cod) {
	for (int i = 0; i < size(l); i++) {
		if (l->medicament[i].cod == cod)
			return i;
	}
	return -1;
}

/*
Functia adauga un medicament in lista
*/
void adauga(MedList* l, ElemType medicamentDeAdaugat) {
	l->medicament[l->lg] = medicamentDeAdaugat;
	l->lg++;
}

/*
Functia modfica un medicament in lista de medicament 
*/
void modificaCantitate(MedList* l, ElemType medicament, int poz, int cantitateNoua) {
	medicament.cantitate = cantitateNoua;
	l->medicament[poz] = medicament;
}

/*
Functia modifica un medicament din lista de medicamente ale farmaciei
*/
void modifica(MedList* l, ElemType medicament, int poz, char* numeNou, int concentratieNoua) {
	medicament.concentratie = concentratieNoua;
	strcpy(medicament.nume, numeNou);
	l->medicament[poz] = medicament;
}

/*
functia sterge stocul unui medicament
*/
void sterge(MedList* l, ElemType medicament, int poz) {
	medicament.cantitate = 0;
	l->medicament[poz] = medicament;
}

/*
Teste
*/

void testCreazaLista() {
	MedList l = creazaGol();
	assert(size(&l) == 0);
}

void testAdaugaLista() {
	MedList l = creazaGol();
	adauga(&l, creazaMedicament(12, "paracetamol", 10, 40));
	adauga(&l, creazaMedicament(13, "ibuprofen", 15, 70));
	assert(size(&l) == 2);
	Medicament m = get(&l, 0);


	assert(m.cod == 12);
	assert(strcmp(m.nume, "paracetamol") == 0);
	distrugeLista(&l);
	assert(size(&l) == 0);

}

void testModificaCantitateLista() {
	MedList l = creazaGol();
	adauga(&l, creazaMedicament(12, "paracetamol", 10, 40));
	adauga(&l, creazaMedicament(13, "ibuprofen", 15, 70));
	Medicament m = creazaMedicament(12, "paracetamol", 10, 40);
	modificaCantitate(&l, m, 0, 70);

	Medicament mNou = get(&l, 0);
	assert(mNou.cantitate == 70);
}

void testCautaLista() {
	MedList l = creazaGol();
	adauga(&l, creazaMedicament(12, "paracetamol", 10, 40));
	adauga(&l, creazaMedicament(13, "ibuprofen", 15, 70));
	
	Medicament m = creazaMedicament(12, "paracetamol", 10, 40);
	
	assert(cauta(&l, m) == 0);

	Medicament mAltul = creazaMedicament(23, "parasinus", 19, 48);

	assert(cauta(&l, mAltul) == -1);
}

void testModificaLista() {
	MedList l = creazaGol();
	adauga(&l, creazaMedicament(12, "paracetamol", 10, 40));
	adauga(&l, creazaMedicament(13, "ibuprofen", 15, 70));

	Medicament m = get(&l, 0);

	modifica(&l, m, 0, "parasinus", 20);

	Medicament mNou = get(&l, 0);

	assert(mNou.concentratie == 20);
	assert(strcmp(mNou.nume, "parasinus") == 0);

}


void testCautaCodLista() {
	MedList l = creazaGol();
	adauga(&l, creazaMedicament(12, "paracetamol", 10, 40));
	adauga(&l, creazaMedicament(13, "ibuprofen", 15, 70));
	assert(cautaCod(&l, 12) == 0);
	assert(cautaCod(&l, 10) == -1);
}

void testStergeLista() {
	MedList l = creazaGol();
	adauga(&l, creazaMedicament(12, "paracetamol", 10, 40));
	adauga(&l, creazaMedicament(13, "ibuprofen", 15, 70));
	Medicament m = get(&l, 0);
	sterge(&l, m, 0);
	Medicament mNou = get(&l, 0);
	assert(mNou.cantitate == 0);
}

void testCopyLista() {
	MedList l = creazaGol();
	adauga(&l, creazaMedicament(12, "paracetamol", 10, 40));
	adauga(&l, creazaMedicament(13, "ibuprofen", 15, 70));
	MedList rez = copy(&l);
	assert(size(&rez) == 2);
}