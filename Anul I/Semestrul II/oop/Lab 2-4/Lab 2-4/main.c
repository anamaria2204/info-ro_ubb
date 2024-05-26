#include "medicament.h"
#include "Medlist.h"
#include "servicemed.h"
#include <stdio.h>

void testAll() {
	testCreazaDistruge();
	testCreazaLista();
	testAdaugaLista();
	testAdaugaMedicament();
	testModificaCantitateLista();
	testCautaLista();
	testModificaLista();
	testModificaMedicament();
	testCautaCodLista();
	testStergeLista();
	testStergeMedicament();
	testCopyLista();
	testSorteazaMedicament();
	testFiltrezaMedicamente();
}


/*
Elibereaza elementele nedorite si clarifica transmiterea
*/
void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {
		// scapam de input-ul nedorit
	}
}

/*
Citeste medicamentul de la tasatura si il adauga in farmacie
*/
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

void sorteazaStocMedicamente(MedList* l) {
	printf("Daca doriti sortarea crescatoare tastati 1, pentru sortarea descrescatoare apasati 0: ");
	int crescator;
	scanf_s("%d", &crescator);
	clearInputBuffer();
	if (crescator == 1 || crescator == 0) {
		printf("\nMedicamentele sortate sunt: \n");
		MedList rez = sorteaza(l, crescator);
		for (int i = 0; i < size(&rez); i++) {
			printf("Cod: %d\n", rez.medicament[i].cod);
			printf("Nume: %s\n", rez.medicament[i].nume);
			printf("Concentratie: %d\n", rez.medicament[i].concentratie);
			printf("Canetitate: %d\n", rez.medicament[i].cantitate);
		}
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
	if(optiune == 1){
		printf("Litera dorita: ");
		char litera;
		scanf_s("%c", &litera, 1);
		clearInputBuffer();
		printf("Medicamentele filtrate sunt: \n");
		MedList res = filtreazaMedicamenteLitera(l, litera);
		if (size(&res) != 0) {
			for (int i = 0; i < size(&res); i++) {
				Medicament m = get(&res, i);
				printf("Cod: %d\n", m.cod);
				printf("Nume: %s\n", m.nume);
				printf("Concentratie: %d\n", m.concentratie);
				printf("Canetitate: %d\n", m.cantitate);
			}
		}
	}
	else {
		printf("Cantiatea dorita: ");
		int cant;
		scanf_s("%d", &cant);
		clearInputBuffer();
		printf("Medicamentele filtrate sunt: \n");
		MedList res = filtreazaMedicamenteCantitate(l, cant);
		if (size(&res) != 0) {
			for (int i = 0; i < size(&res); i++) {
				Medicament m = get(&res, i);
				printf("Cod: %d\n", m.cod);
				printf("Nume: %s\n", m.nume);
				printf("Concentratie: %d\n", m.concentratie);
				printf("Canetitate: %d\n", m.cantitate);
			}
		}
	}

}
void print_meniu() {
	printf("Aplicatia permite:\n"
			"1. Adauga medicament in farmacie\n"
			"2. Modifica un medicament din farmacie\n"
			"3. Sterge stocul unui medicament din farmacie\n"	
			"4. Vizualizare medicamente ordonate duoa nume si cantitate\n"
			"5. Filtreaza medicamente\n"
			"0. Exit\n"
		);
}

void run() {
	MedList toateMedicamentele = creazaGol();
	int ruleaza = 1;
	while (ruleaza) {
		print_meniu();
		int optiune;
		printf("Optiunea dorita este: ");
		scanf_s("%d/n", &optiune);
		clearInputBuffer();
		if (optiune == 0) {
			ruleaza = 0;
			printf("La revedere!");
			break;
		}
		else if (optiune == 1) {
			citesteMedicament(&toateMedicamentele);
		}
		else if (optiune == 2) {
			modificaMedicamentulDorit(&toateMedicamentele);
		}
		else if (optiune == 3) {
			stergeStocMedicament(&toateMedicamentele);
		}
		else if (optiune == 4) {
			sorteazaStocMedicamente(&toateMedicamentele);
		}
		else if (optiune == 5) {
			filtrezaMedicamenteStoc(&toateMedicamentele);
		}
		else{
			printf("Comanda invalida!\n");
		}
		printf("Medicamentele din stoc sunt: \n");
		for (int i = 0; i < size(&toateMedicamentele); i++) {
			printf("Cod: %d Nume: %s Concentratie: %d Cantitate: %d\n", toateMedicamentele.medicament[i].cod,
				toateMedicamentele.medicament[i].nume,
				toateMedicamentele.medicament[i].concentratie,
				toateMedicamentele.medicament[i].cantitate);
		}
	}
}

int main() {
	testAll();
	//run();
	return 0;

}