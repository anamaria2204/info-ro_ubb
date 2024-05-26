#include "repo.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

MedList* creazaGol(destroy_fct f) {
	MedList* lista = malloc(sizeof(MedList));

	if (lista == NULL) {
		return NULL;
	}

	lista->capacitate = 2;
	lista->lungime = 0;
	lista->medicament = malloc(lista->capacitate * sizeof(ElemType));

	if (lista->medicament == NULL) {
		free(lista);
		return NULL;
	}

	lista->dest = f;

	return lista;
}

void distrugeLista(MedList* lista) {
	for (int i = 0; i < lista->lungime; ++i) {
		lista->dest(lista->medicament[i]);
	}
	free(lista->medicament);
	free(lista);
}

void extinde(MedList* lista) {
	if (lista->lungime == lista->capacitate) {
		lista->capacitate *= 2;
		ElemType* temporar = malloc(lista->capacitate * sizeof(ElemType));
		for (int i = 0; i < lista->lungime; ++i) {
			temporar[i] = lista->medicament[i];
		}
		free(lista->medicament);
		lista->medicament = temporar;
	}
}

int adauga(MedList* lista, ElemType* medicament, egale_fct eq, egale_coduri ec, cantitate_fct cant) {

	int succes = 0;
	for (int i = 0; i < lista->lungime; ++i) {
		if (eq(lista->medicament[i], medicament)) {
			cant(lista->medicament[i], medicament);
			succes = 1;
		}
		else if (ec(lista->medicament[i], medicament)) {
			succes = -1;
		}
	}
	if (succes == 1) {
		lista->dest(medicament);
		return 0;
	}
	else if (succes == -1) {
		lista->dest(medicament);
		return 1;
	}

	extinde(lista);
	lista->medicament[lista->lungime++] = medicament;

	return 0;

}

int modifica(MedList* lista, ElemType* medicament, egal_modify eg, cantitate_fct cant) {
	for (int i = 0; i < lista->lungime; ++i) {
		if (eg(lista->medicament[i], medicament)) {

			cant(medicament, lista->medicament[i]);
			lista->dest(lista->medicament[i]);
			lista->medicament[i] = medicament;
			return 0;
		}
	}
	lista->dest(medicament);
	return 1;
}

int stergeStoc(MedList* lista, int cod, return_cod cd, sterge_cant sterge) {

	for (int i = 0; i < lista->lungime; ++i) {

		if (cd(lista->medicament[i]) == cod) {
			sterge(lista->medicament[i]);
			return 0;
		}
	}
	return 1;
}


MedList* copieLista(MedList* lista, copy_fct cpy) {

	MedList* lista_noua = creazaGol(lista->dest);

	for (int i = 0; i < lista->lungime; ++i) {
		adauga(lista_noua, cpy(lista->medicament[i]), (egale_fct)egalMedicamente, (egale_coduri)egalCod,
			(cantitate_fct)adaugaCantitate);
	}
	return lista_noua;
}

