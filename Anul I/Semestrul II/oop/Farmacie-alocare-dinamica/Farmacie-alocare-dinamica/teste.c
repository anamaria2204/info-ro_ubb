#include <assert.h>
#include <string.h>
#include "teste.h"
#include "domeniu.h"
#include "repo.h"
#include "service.h"
#include <stdlib.h>
#include <stdio.h>

//teste domeniu//

void testCreazaMedicament() {
	Medicament* m = creaza(1, "nurofen", 200, 600);
	assert(m->cod == 1);
	assert(strcmp(m->nume, "nurofen") == 0);
	assert(m->concentratie == 200);
	assert(m->cantitate == 600);
    distruge(m);
}

void testDistrugeMedicament() {
    Medicament* m = creaza(1, "Paracetamol", 500, 20);
    distruge(m);
    // Asserting that m is NULL after destruction
    assert(m->cod != 1);
    assert(m->concentratie != 500);
    assert(m->cantitate != 20);
}

void testValideazaMedicament() {
    Medicament* m = creaza(1, "Paracetamol", 500, 20);
    assert(valideaza(m) == 0);
    
    m->cod = 0;
    assert(valideaza(m) == 1);
    m->cod = 1; 
    free(m->nume);
    m->nume = "";
    assert(valideaza(m) == 2);
    free(m);

    m = creaza(1, "Paracetamol", 500, 20);
    m->concentratie = -500;
    assert(valideaza(m) == 3);
    m->concentratie = 500;
    m->cantitate = -20;
    assert(valideaza(m) == 4);
    distruge(m);
}

void testEgalCod() {
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m2 = creaza(1, "Aspirin", 300, 15);
    Medicament* m3 = creaza(2, "Ibuprofen", 400, 30);
    assert(egalCod(m1, m2) == 1);
    assert(egalCod(m1, m3) == 0);
    distruge(m1);
    distruge(m2);
    distruge(m3);
}

void testEgalMedicamente() {
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m2 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m3 = creaza(2, "Ibuprofen", 400, 30);
    assert(egalMedicamente(m1, m2) == 1);
    assert(egalMedicamente(m1, m3) == 0);
    distruge(m1);
    distruge(m2);
    distruge(m3);
}

void testEgalModify() {
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m2 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m3 = creaza(2, "Ibuprofen", 400, -30);
    assert(egalModifica(m1, m2) == 1);
    assert(egalModifica(m1, m3) == 0);
    distruge(m1);
    distruge(m2);
    distruge(m3);
}

void testAdaugaCantitate() {
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m2 = creaza(2, "Ibuprofen", 400, 30);
    adaugaCantitate(m1, m2);
    assert(m1->cantitate == 50);
    distruge(m1);
    distruge(m2);
}

void testReturnCod() {
    Medicament* m = creaza(1, "Paracetamol", 500, 20);
    assert(returnCod(m) == 1);
    distruge(m);
}

void testVerifStoc() {
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m2 = creaza(2, "Ibuprofen", 400, -30);
    assert(verifStoc(m1) == 1);
    assert(verifStoc(m2) == 0);
    distruge(m1);
    distruge(m2);
}

void testStergeCantitate() {
    Medicament* m = creaza(1, "Paracetamol", 500, 20);
    stergeCantitate(m);
    assert(m->cantitate == 0);
    distruge(m);
}

void testCompNume() {
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m2 = creaza(2, "Ibuprofen", 400, 30);
    assert(compNume(m1, m2) > 0);
    assert(compNume(m2, m1) < 0);
    distruge(m1);
    distruge(m2);
}

void testCompCantitate() {
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m2 = creaza(2, "Ibuprofen", 400, 30);
    assert(compCantitate(m1, m2) == 0);
    assert(compCantitate(m2, m1) == 1);
    distruge(m1);
    distruge(m2);
}

void testFiltreazaNume() {
    Medicament* m = creaza(1, "Paracetamol", 500, 20);
    assert(filtreazaNume(m, 'P') == 1);
    assert(filtreazaNume(m, 'I') == 0);
    distruge(m);
}

void testFiltreazaCantitate() {
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m2 = creaza(2, "Ibuprofen", 400, -30);
    assert(filtrezaCantitate(m1, 30) == 1);
    assert(filtrezaCantitate(m2, 0) == 0);
    distruge(m1);
    distruge(m2);
}

//teste repo

void testCreazaGol() {
    MedList* lista = creazaGol(&distruge);
    assert(lista != NULL);
    assert(lista->capacitate == 2);
    assert(lista->lungime == 0);
    distrugeLista(lista);
}

void testDistruge() {
    MedList* lista = creazaGol(&distruge);
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m2 = creaza(2, "Ibuprofen", 400, 30);
    adauga(lista, (ElemType*) m1, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);
    adauga(lista, (ElemType*) m2, (egale_fct) egalMedicamente, (egale_coduri) egalCod, (cantitate_fct) adaugaCantitate);

    distrugeLista(lista);

    assert(lista->lungime != 2);
    assert(lista->capacitate != 2);
}

void testExtinde() {
    MedList* lista = creazaGol(&distruge);
    assert(lista->capacitate == 2);

    for (int i = 0; i < 3; ++i) {
        Medicament* m = creaza(i + 1, "Med", 100, 10);
        adauga(lista, (ElemType*) m, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);
    }

    assert(lista->capacitate == 4);

    distrugeLista(lista);

}

void testAdauga() {
    MedList* lista = creazaGol(&distruge);
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m2 = creaza(2, "Ibuprofen", 400, 30);
    assert(adauga(lista, (ElemType*) m1, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate) == 0);
    assert(adauga(lista, (ElemType*) m2, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate) == 0);

    Medicament* m3 = creaza(1, "Paracetamol", 500, 10);
    assert(adauga(lista, (ElemType*) m3, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate) == 0);
    Medicament* m4 = creaza(1, "Paracetamol", 400, 10);
    assert(adauga(lista, (ElemType*) m4, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate) == 1);
    assert(returnCod(lista->medicament[0]) == 1);
    assert(lista->lungime == 2);

    distrugeLista(lista);
}

void testModifica() {
    MedList* lista = creazaGol(&distruge);
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    adauga(lista, (ElemType*) m1, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);

    Medicament* m2 = creaza(1, "Paracetamol", 500, 10);
    assert(modifica(lista, (ElemType*) m2, (egal_modify)egalModifica, (cantitate_fct)adaugaCantitate) == 0);

    Medicament* m3 = creaza(2, "Paracetamol", 500, 10);
    assert(modifica(lista, (ElemType*) m3, (egal_modify)egalModifica, (cantitate_fct)adaugaCantitate) == 1);

    distrugeLista(lista);
}

void testStergeStoc() {
    MedList* lista = creazaGol(&distruge);
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m2 = creaza(2, "Ibuprofen", 400, 30);
    adauga(lista, (ElemType*) m1, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);
    adauga(lista, (ElemType*) m2, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);

    assert(stergeStoc(lista, 1, (return_cod)returnCod, (sterge_cant)stergeCantitate) == 0);
    assert(lista->lungime == 2);

    assert(stergeStoc(lista, 3, (return_cod)returnCod, (sterge_cant)stergeCantitate) == 1);

    distrugeLista(lista);
}

void testCopieLista() {
    MedList* lista = creazaGol(&distruge);
    Medicament* m1 = creaza(1, "Paracetamol", 500, 20);
    Medicament* m2 = creaza(2, "Ibuprofen", 400, 30);
    adauga(lista, (ElemType*) m1, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);
    adauga(lista, (ElemType*) m2, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);

    MedList* listaCopiata = copieLista(lista, (copy_fct)copiazaMedicamente);
    assert(listaCopiata->lungime == 2);

    distrugeLista(lista);
    distrugeLista(listaCopiata);

}

//teste service
void testAdaugaMedicament() {
    MedList* lista = creazaGol(&distruge);

    assert(adaugaMedicament(lista, 1, "Paracetamol", 500, 20) == 0);

    assert(adaugaMedicament(lista, 2, "Ibuprofen", -400, 30) == 3);

    distrugeLista(lista);
}

void testModificaMedicament() {
    MedList* lista = creazaGol(&distruge);
    adaugaMedicament(lista, 1, "Paracetamol", 500, 20);

    assert(modificaMedicament(lista, 1, "Aspirin", 300) == 0);

    assert(modificaMedicament(lista, 1, "Paracetamol", -500) == 3);

    distrugeLista(lista);
}

void testStergeMedicament() {
    MedList* lista = creazaGol(&distruge);
    adaugaMedicament(lista, 1, "Paracetamol", 500, 20);

    assert(stergeMedicament(lista, 1) == 0);

    assert(stergeMedicament(lista, -1) == 1);

    distrugeLista(lista);
}

void testGetAllMedicamente() {
    MedList* lista = creazaGol(&distruge);
    adaugaMedicament(lista, 1, "Paracetamol", 500, 20);
    adaugaMedicament(lista, 2, "Ibuprofen", 400, 30);

    MedList* allMedicaments = getAllMedicamente(lista);
    assert(allMedicaments->lungime == 2);

    distrugeLista(lista);
    distrugeLista(allMedicaments);
}

void testSort() {
    MedList* lista = creazaGol(&distruge);
    adaugaMedicament(lista, 1, "Paracetamol", 500, 20);
    adaugaMedicament(lista, 2, "Ibuprofen", 400, 30);

    MedList* sortedAsc = sort(lista, 1, (sort_fct)compNume, (sort_fct)compCantitate);
    assert(((Medicament*)sortedAsc->medicament[0])->cantitate == 30);

    MedList* sortedDesc = sort(lista, 0, (sort_fct)compNume, (sort_fct)compCantitate);
    assert(((Medicament*)sortedDesc->medicament[0])->cantitate == 20);

    distrugeLista(sortedAsc);
    distrugeLista(sortedDesc);

    distrugeLista(lista);
}

void testCopieListaCantitate() {
    MedList* lista = creazaGol(&distruge);
    adaugaMedicament(lista, 1, "Paracetamol", 500, 20);
    adaugaMedicament(lista, 2, "Ibuprofen", 400, 30);

    MedList* copiedList = copieListaCantitate(lista, 20, (filter_fct_cantitate)filtrezaCantitate);
    assert(copiedList->lungime == 0);

    distrugeLista(copiedList);
    copiedList = copieListaCantitate(lista, 30, (filter_fct_cantitate)filtrezaCantitate);
    assert(copiedList->lungime == 1);

    distrugeLista(lista);
    distrugeLista(copiedList);
}

void testCopieListaNume() {
    MedList* lista = creazaGol(&distruge);
    adaugaMedicament(lista, 1, "Paracetamol", 500, 20);
    adaugaMedicament(lista, 2, "Ibuprofen", 400, 30);

    MedList* copiedList = copieListaNume(lista, 'P', (filter_fct_nume)filtreazaNume);
    assert(copiedList->lungime == 1);

    distrugeLista(lista);
    distrugeLista(copiedList);
}