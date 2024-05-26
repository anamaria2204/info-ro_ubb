#include "service.h"
#include "repo.h"
#include "domeniu.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int adaugaMedicament(MedList* lista, int cod, char* nume, int concentratie, int cantitate) {
	Medicament* m = creaza(cod, nume, concentratie, cantitate);

	int succes = valideaza(m);
	if (succes != 0) {
		free(m->nume);
		free(m);
		return succes;
	}

	return adauga (lista, (ElemType*)m, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);
}

int modificaMedicament(MedList* list, int cod, char* nume_nou, int concentratie_noua) {

	Medicament* m = creaza(cod, nume_nou, concentratie_noua, 1);

	int succes = valideaza(m);
	if (succes != 0) {
		free(m->nume);
		free(m);
		return succes;
	}

	return modifica(list, (ElemType*)m, (egal_modify)egalModifica, (cantitate_fct)adaugaCantitate);

}

int stergeMedicament(MedList* list, int cod) {
	if (cod <= 0)
		return 1;
	return stergeStoc(list, cod, (return_cod) returnCod, (sterge_cant) stergeCantitate);
}

MedList* getAllMedicamente(MedList* lista) {

	return copieLista(lista, (copy_fct)copiazaMedicamente);

}

MedList* sort(MedList* lista, int crescator, sort_fct cmp1, sort_fct cmp2){
	MedList* list = copieLista(lista, (copy_fct)copiazaMedicamente);

	for (int i = 0; i < list->lungime - 1; i++) {
		for (int j = i + 1; j < list->lungime; j++) {
			if ((crescator && cmp1(list->medicament[i], list->medicament[j]) > 0) ||
				(!crescator && cmp1(list->medicament[i], list->medicament[j]) < 0)) {
				ElemType* temporar = list->medicament[i];
				list->medicament[i] = list->medicament[j];
				list->medicament[j] = (ElemType*)temporar;
			}
			else if ((crescator && cmp2(list->medicament[i], list->medicament[j]) == 1) ||
				(!crescator && cmp1(list->medicament[i], list->medicament[j]) == 0)) {
				ElemType* temporar = list->medicament[i];
				list->medicament[i] = list->medicament[j];
				list->medicament[j] = (ElemType*)temporar;
			}
		}
	}
	return list;
}

MedList* copieListaCantitate(MedList* lista, int cantitate, filter_fct_cantitate filtreaza){
	MedList* copie = creazaGol(lista->dest);

	for (int i = 0; i < lista->lungime; i++) {
		if (filtreaza(lista->medicament[i], cantitate)) {
			adauga(copie, (ElemType*)copiazaMedicamente(lista->medicament[i]), (egale_fct)egalMedicamente,
				(egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);
		}
	}
	return copie;
}

MedList* copieListaNume(MedList* lista, char litera, filter_fct_nume filtreaza){
	MedList* copie = creazaGol(lista->dest);

	for (int i = 0; i < lista->lungime; i++) {
		if (filtreaza(lista->medicament[i], litera)) {
			adauga(copie, (ElemType*)copiazaMedicamente(lista->medicament[i]), (egale_fct)egalMedicamente,
				(egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);
		}
	}
	return copie;
}