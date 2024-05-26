#define _CRTDBG_MAP_ALLOC

#include <stdio.h>
#include "domeniu.h"
#include "repo.h"
#include "service.h"
#include "ui.h"
#include <crtdbg.h> 

void printMedicament(Medicament* m) {
	printf("Cod: %d  ", m->cod);
	printf("Nume: %s  ", m->nume);
	printf("Concentratie: %d  ", m->concentratie);
	printf("Cantitate: %d\n", m->cantitate);
}

void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {
		// scapam de input-ul nedorit
	}
}

void printAllMedicament(MedList* list) {

	printf("\nMedicamentele din farmacie sunt: \n");
	for (int i = 0; i < list->lungime; i++) {

		printMedicament(list->medicament[i]);

	}
	printf("\n");
}

void citesteMedicament(MedList* l) {
	printf("Cod: ");
	int cod;
	scanf_s("%d", &cod);
	clearInputBuffer();
	printf("Nume: ");
	char nume[50];
	scanf_s("%s", &nume, 50);
	clearInputBuffer();
	printf("Concentratie: ");
	int concentratie;
	scanf_s("%d", &concentratie);
	clearInputBuffer();
	printf("Cantitate: ");
	int cantitate;
	scanf_s("%d", &cantitate);
	clearInputBuffer();
	int error = adaugaMedicament(l, cod, nume, concentratie, cantitate);
	if (error != 0) {
		printf("Medicament invalid!\n");
	}
	else {
		printf("Medicament adaugat cu succes!\n");
	}

}

void stergeStocMedicament(MedList* l) {
	printf("Codul medicamentului a carui stoc va fi sters: ");
	int cod;
	scanf_s("%d", &cod);
	clearInputBuffer();
	int error = stergeMedicament(l, cod);
	if (error != 0) {
		printf("Nu exista medicamentul dorit!\n");
	}
	else {
		printf("Stocul medicamentului a fost sters!\n");
	}
}

void modificaMedicamentulDorit(MedList* l) {
	printf("Noul nume: ");
	char numeNou[50];
	scanf_s("%s", &numeNou, 50);
	clearInputBuffer();
	printf("Noua concentratie: ");
	int concentratieNoua;
	scanf_s("%d", &concentratieNoua);
	clearInputBuffer();
	printf("Codul medicamentului de modificat: ");
	int cod;
	scanf_s("%d", &cod);
	clearInputBuffer();
	int error = modificaMedicament(l, cod, numeNou, concentratieNoua);
	if (error != 0) {
		printf("Nu exista medicamenul de modificat!\n");
	}
	else {
		printf("Medicament modificat cu succes!\n");
	}
}

void sorteazaStocMedicamente(MedList* l) {
	printf("Daca doriti sortarea crescatoare tastati 1, pentru sortarea descrescatoare apasati 0: ");
	int crescator;
	scanf_s("%d", &crescator);
	clearInputBuffer();
	if (crescator == 1 || crescator == 0) {
		printf("\nMedicamentele sortate sunt: \n");
		MedList* rez = sort(l, crescator, (sort_fct)compNume, (sort_fct)compCantitate);
		for (int i = 0; i < rez->lungime; i++) {
			if (verifStoc(rez->medicament[i])) {
				printMedicament(rez->medicament[i]);
			}
		}
		distrugeLista(rez);
	}
	else {
		printf("Nu exista optiunea data!\n");
	}
}

void filtrezaMedicamenteStoc(MedList* l) {
	printf("Medicamentele vor fi filtrate dupa: 1 - nume, 0-cantiate: ");
	int optiune = -1;
	scanf_s("%d", &optiune);
	clearInputBuffer();
	if (optiune == 1) {
		printf("Litera dorita: ");
		char litera;
		scanf_s("%c", &litera, 1);
		clearInputBuffer();
		printf("Medicamentele filtrate sunt: \n");
		MedList* res = copieListaNume(l, litera, (filter_fct_nume)filtreazaNume);
		if (res->lungime != 0) {
			for (int i = 0; i < res->lungime; i++) {
				printMedicament(res->medicament[i]);
			}
		}
		distrugeLista(res);
	}
	else {
		printf("Cantiatea dorita: ");
		int cant;
		scanf_s("%d", &cant);
		clearInputBuffer();
		printf("Medicamentele filtrate sunt: \n");
		MedList* res = copieListaCantitate(l, cant, (filter_fct_cantitate)filtrezaCantitate);
		if (res->lungime != 0) {
			for (int i = 0; i < res->lungime; i++) {
				printMedicament(res->medicament[i]);
			}
		}
		distrugeLista(res);
	}
}


void print_meniu() {
	printf("Aplicatia permite:\n"
		"1. Adauga medicament in farmacie\n"
		"2. Modifica un medicament din farmacie\n"
		"3. Sterge stocul unui medicament din farmacie\n"
		"4. Vizualizare medicamente ordonate dupa nume si cantitate\n"
		"5. Filtreaza medicamente\n"
		"0. Exit\n"
	);
}

void run() {
	MedList* totateMedicamentele = creazaGol((destroy_fct)distruge);
	printf("Bine ati venit la farmacie!");
	printAllMedicament(totateMedicamentele);
	print_meniu();
	int optiune = 0, ok = 1;
	printf("Optiunea dorita este: ");
	scanf_s("%d/n", &optiune);
	clearInputBuffer();
	while (ok == 1) {
		if (optiune == 0) {
			ok = 0;
			printf("La revedere!");
			break;
		}
		else if (optiune == 1) {
			citesteMedicament(totateMedicamentele);
		}
		else if (optiune == 2) {
			modificaMedicamentulDorit(totateMedicamentele);
		}
		else if (optiune == 3) {
			stergeStocMedicament(totateMedicamentele);
		}
		else if (optiune == 4) {
			sorteazaStocMedicamente(totateMedicamentele);
		}
		else if (optiune == 5) {
			filtrezaMedicamenteStoc(totateMedicamentele);
		}
		printAllMedicament(totateMedicamentele);
		print_meniu();
		printf("Optiunea dorita este: ");
		scanf_s("%d/n", &optiune);
		clearInputBuffer();
	}
	distrugeLista(totateMedicamentele);
}

int main() {
	testAll();
	
	run();

	if (_CrtDumpMemoryLeaks())
		printf("\nMEMORY LEAKS\n");
	return 0;
}