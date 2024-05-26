#include "servicemed.h"

#include <string.h>
#include <assert.h>

/*
Adauga un medicament in farmacie
*/
int adaugaMedicament(MedList* l, int cod, char* nume, int concentratie, int cantitate) {
	Medicament m = creazaMedicament(cod, nume, concentratie, cantitate);
	int ok = 0;
	if (valideaza(m) != 0)
		return valideaza(m);
	int i = cauta(l, m);
	if (i >= 0 && i <= size(l)) {
		ok = 1;
		Medicament med = get(l, i);
		modificaCantitate(l, med, i, cantitate);
	}
	if (ok == 0) {
		adauga(l, m);
	}
	return 0;
}

/*
Modifica un medicament dat, schimband numele si concentratia
aceste modificari se relizeaza doar daca medicamentul este in stoc
*/
int modificaMedicament(MedList* l, int cod, char* numeNou, int concentratieNoua) {
	//verificam daca medicamentul se afla in stocul farmaciei
	int i = cautaCod(l, cod);
	if (i >= 0 && i <= size(l)) {
		Medicament medicament = get(l, i);
		modifica(l, medicament, i, numeNou, concentratieNoua);
	}
	else {
		return 1;
	}
	return 0;
}

/*
Functia sterge un medicament din farmacie daca acesta exista
*/
int stergeMedicament(MedList* l, int cod) {
	//verificam daca medicamentul este in stocul farmaciei
	int i = cautaCod(l, cod);
	if (i >= 0 && i <= size(l)) {
		Medicament medicament = get(l, i);
		sterge(l, medicament, i);
	}
	else {
		return 1;
	}
	return 0;
}

/*
Functia sorteaza medicamentele farmaciei dupa nume si cantitate
*/

MedList sorteaza(MedList* l, int crescator) {
	MedList list = copy(l);
	Medicament temporar;

	int lungime = size(&list);
	for (int i = 0; i < lungime - 1; ++i) {
		for (int j = i + 1; j < lungime; ++j) {
			if ((crescator && strcmp(list.medicament[i].nume, list.medicament[j].nume) > 0) ||
				(!crescator && strcmp(list.medicament[i].nume, list.medicament[j].nume) < 0)) {
				temporar = list.medicament[i];
				list.medicament[i] = list.medicament[j];
				list.medicament[j] = temporar;
			}
			else if (strcmp(list.medicament[i].nume, list.medicament[j].nume) == 0) {
				if ((crescator && list.medicament[i].cantitate > list.medicament[j].cantitate) ||
					(!crescator && list.medicament[i].cantitate < list.medicament[j].cantitate)) {
					temporar = list.medicament[i];
					list.medicament[i] = list.medicament[j];
					list.medicament[j] = temporar;
				}
			}
		}
	}
	return list;
}

/*
Functia filtreaza medicamentele dupa citeriile date
cantitate < nr dat
nume cu prima litera data
*/

MedList filtreazaMedicamenteCantitate(MedList* l, int cantitateData) {
	MedList result = creazaGol();
	int lungime = size(&l);
	for (int i = 0; i < size(l); i++) {
		Medicament m = get(l, i);
		int cantitate_curent = m.cantitate;
		if (cantitate_curent < cantitateData && cantitate_curent != 0) {
				adauga(&result, m);
		}
	}
	return result;
}

MedList filtreazaMedicamenteLitera(MedList* l, char* literaData) {
	MedList result = creazaGol();
	int lungime = size(&l);
	for (int i = 0; i < size(l); i++) {
		Medicament m = get(l, i);
		char litera_curenta = m.nume[0];
		if (literaData == litera_curenta) {
			adauga(&result, m);
		}
	}
	return result;
}

/*
teste
*/

void testAdaugaMedicament() {
	MedList l = creazaGol();
	//incercam sa adaugam medicamente invalide
	int error = adaugaMedicament(&l, -3, "paracetamol", 23, 12);
	assert(error != 0);
	assert(size(&l) == 0);

	error = adaugaMedicament(&l, 12, "", 23, 90);
	assert(error != 0);
	assert(size(&l) == 0);

	error = adaugaMedicament(&l, 19, "paracetamol", -34, 56);
	assert(error != 0);
	assert(size(&l) == 0);

	error = adaugaMedicament(&l, 23, "paracetamol", 34, -90);
	assert(error != 0);
	assert(size(&l) == 0);

	//incercam sa adaugam medicamente valide
	adaugaMedicament(&l, 12, "paracetamol", 15, 40);
	adaugaMedicament(&l, 13, "ibuprofen", 10, 50);
	assert(size(&l) == 2);
	adaugaMedicament(&l, 12, "paracetamol", 15, 70);
	Medicament m = get(&l, 0);
	assert(m.cantitate == 70);
	assert(size(&l) == 2);


}

void testModificaMedicament() {
	MedList l = creazaGol();
	adaugaMedicament(&l, 12, "paracetamol", 15, 40);
	adaugaMedicament(&l, 13, "ibuprofen", 10, 50);
	assert(size(&l) == 2);
	if (modificaMedicament(&l, 12, "parasinus", 60) == 0) {
		Medicament m = get(&l, 0);
		assert(strcmp(m.nume, "parasinus") == 0);
		assert(m.concentratie == 60);
	}
	assert(modificaMedicament(&l, 10, "parasinus", 60) == 1);
}

void testStergeMedicament() {
	MedList l = creazaGol();
	adaugaMedicament(&l, 12, "paracetamol", 15, 40);
	adaugaMedicament(&l, 13, "ibuprofen", 10, 50);
	if (stergeMedicament(&l, 12) == 0) {
		Medicament m = get(&l, 0);
		assert(m.cantitate == 0);
	}
	assert(stergeMedicament(&l, 10) == 1);
}

void testSorteazaMedicament() {
	MedList l = creazaGol();
	adaugaMedicament(&l, 12, "paracetamol", 15, 40);
	adaugaMedicament(&l, 13, "ibuprofen", 10, 50);
	adaugaMedicament(&l, 14, "paracetamol", 20, 50);
	MedList rez = sorteaza(&l, 1);
	Medicament m0 = get(&rez, 0);
	Medicament m1 = get(&rez, 1);
	Medicament m2 = get(&rez, 2);
	assert(m0.cod == 13);
	assert(m1.cod == 12);
	assert(m2.cod == 14);
	MedList rezd = sorteaza(&l, 0);
	Medicament m3 = get(&rezd, 0);
	assert(m3.cod == 14);
}

void testFiltrezaMedicamente() {
	MedList l = creazaGol();
	adaugaMedicament(&l, 12, "paracetamol", 15, 40);
	adaugaMedicament(&l, 13, "ibuprofen", 10, 50);
	adaugaMedicament(&l, 14, "paracetamol", 20, 50);
	char litera = 'p';
	int cantitate = 45;
	MedList res = filtreazaMedicamenteCantitate(&l, cantitate);
	assert(res.medicament[0].cod == 12);
	assert(size(&res) == 1);
	MedList resl = filtreazaMedicamenteLitera(&l, litera);
	assert(res.medicament[0].cod == 12);
	assert(size(&res) == 1);

}


