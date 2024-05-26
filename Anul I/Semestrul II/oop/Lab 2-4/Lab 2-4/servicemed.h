#pragma once

#include "Medlist.h"

/*
Adaugam un medicament in farmacie
*/
int adaugaMedicament(MedList* l, int cod, char* nume, int concentratie, int cantitate);

/*
Modifca un medicament din farmacie
*/
int modificaMedicament(MedList* l,int cod, char* numeNou, int concentratieNoua);


/*
Sterge stocul unui medicament din farmacie
*/

int stergeMedicament(MedList* l, int cod);


/*
Sorteaza lista de medicamente dupa nume si cantitate
*/

MedList sorteaza(MedList* l, int crescator);

/*
filtreaza lista de medicamente care au stoc mai mic 
decat o valoare data si numele incepe cu o litera data
*/

MedList filtreazaMedicamenteCantitate(MedList* l, int cantitateData);
MedList filtreazaMedicamenteLitera(MedList* l, char* literaData);

/*
teste
*/
void testAdaugaMedicament();
void testModificaMedicament();
void testStergeMedicament();
void testSorteazaMedicament();
void testFiltrezaMedicamente();
