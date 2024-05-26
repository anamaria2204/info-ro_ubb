#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "service.h"
#include "repo.h"
#include "domain.h"
#include "teste.h"

void testAll() {
	testCreateProdus();
	testCreateDestroy();
	testCreateList();
	testIterateList();
	testCopyList();
	testAddProduct();
	testCreateSrv();
	test_addProduct();
	test_getAllProduct_by_price();
	test_getAllProduct_by_producator();
	test_getAllProduct_by_quantity();
	test_stergeProdus();
	test_updateProduct();
	test_compara_pret();
	test_compara_cantitate();
	test_sortare_produse();
	test_compara_egale();
	test_filtrare_litera();
	test_undo();
}

void printAllProduct(MyList* l) {
	printf("Produse:\n");
	for (int i = 0; i < size(l); i++) {
		Produs* p = get(l, i);
		printf("ID:%d Tip:%s Producator:%s Model:%s Pret:%0.2f Cantitate:%d\n", p->id, p->tip, p->producator, p->model, p->pret, p->cantitate);
	}
}

void readProdus(Srv srvproduse) {
	int id;
	printf("Id:");
	scanf_s("%d", &id);

	char tip[30];
	printf("Tip:");
	scanf_s("%s", tip, 30);

	char producator[30];
	printf("Producator:");
	scanf_s("%s", producator, 30);

	char model[30];
	printf("Model:");
	scanf_s("%s", model, 30);

	float pret;
	printf("Pret:");
	scanf_s("%f", &pret);

	int cantitate;
	printf("Cantitate:");
	scanf_s("%d", &cantitate);

	int error = addProduct(&srvproduse, id, tip, producator, model, pret, cantitate);
	if (error != 0) {
		printf("\033[1;31m");
		printf("Invalid product.\n");
		printf("\033[0m");
	}
	else {
		printf("\033[1;36m");
		printf("Product added.\n");
		printf("\033[0m");
	}
}

void deteleProd(Srv srvprod) {
	int id_sterg;
	printf("Introduce-ti id-ul produsului pe care doriti sa il stergeti: ");
	scanf_s("%d", &id_sterg);
	if (stergeProdus(&srvprod, id_sterg) == 0) {
		printf("\033[1;31m");
		printf("Ceva a mers prost! Te rog incearca din nou!\n");
		printf("\033[0m");
	}
	else
		printf("Produs sters cu succes!\n");
}

void modifyProd(Srv srvprod) {
	int id;
	float nou;
	int nou_c;
	printf("Introduce-ti id-ul produsului pe care doriti sa il modificati: ");
	scanf_s("%d", &id);
	printf("Introduce-ti noul pret al produsului: ");
	scanf_s("%f", &nou);
	printf("Introduce-ti noua cantitate a produsului: ");
	scanf_s("%d", &nou_c);
	if (updateProduct(&srvprod, id, nou, nou_c) == 1)
		printf("Produs actualizat cu succes!\n");
	else {
		printf("\033[1;31m");
		printf("Ceva a mers prost! Te rog incearca din nou!\n");
		printf("\033[0m");
	}
}


void filterProd(MyList* l) {
	printf("Type filter substring:");
	char filterStr[30];
	scanf_s("%s", filterStr, 30);

	MyList* filteredL = getAllProduct(l, filterStr, (cauta_sir)cautaSir);
	printf("\n\n");
	printAllProduct(filteredL);
	destroy(filteredL);
}

void do_undo(Srv* srv) {
	if (undo(srv) == 1) {
		printf("Undo efectuat cu succes!\n");
	}
	else {
		printf("Nu se mai poate face undo!\n");
	}
}

void run() {

	Srv allProd = createService();
	int ruleaza = 1;
	while (ruleaza) {
		printf("\033[1;33m");
		printf("---------------------- BINE ATI VENIT ---------------------------\n\n\n");
		printf("\033[0m");

		printf("\033[1;36m");
		printAllProduct(allProd.actual);
		printf("\n\n\n");
		printf("\033[0m");

		printf("\033[1;33m");
		printf("1 Adauga produs nou\n2 Actualizare produse(pret sau cantitate)\n3 Sterge produs dupa id\n4 Vizualizare produse din stoc");
		printf("\n5 Vizualizare lista produse filtrate dupa un criteriu\n6 Undo\n0 Exit\n Command:");
		printf("\033[0m");
		int cmd = 0;
		scanf_s("%d", &cmd);
		if (cmd == 1) {

			readProdus(allProd);
		}
		else
			if (cmd == 2) {
				modifyProd(allProd);
			}
			else
				if (cmd == 3) {

					deteleProd(allProd);
				}
				else
					if (cmd == 4) {

						MyList* filteredL;
						int cresc;
						printf("Introduce-ti 1 daca doriti ordonare crescatoare sau 0 altfel: ");
						scanf_s("%d", &cresc);

						if (cresc == 1 || cresc == 0) {

							filteredL = sortare(allProd.actual, 1, (sorteaza)comparaCantitate, (sorteaza)comparaPret);
							printAllProduct(filteredL);
							destroy(filteredL);

						}
						else {
							printf("\033[1;31m");
							printf("Optiune invalida! Va rugam incercati din nou!\n\n\n");
							printf("\033[0m");
						}
					}
					else
						if (cmd == 5) {

							MyList* filteredL;
							int cantitate;
							printf("Introduce-ti cantitatea dupa care se filtreaza: ");
							scanf_s("%d", &cantitate);
							filteredL = getAllProductbyquantite(allProd.actual, cantitate, (compara_cantitate)comparaCantitatea);
							printf("\n\n");
							printf("\033[1;36m");
							printAllProduct(filteredL);
							printf("\033[0m");
							destroy(filteredL);
						}
						else 
							if (cmd == 6) {
								do_undo(&allProd);
							}

						else
							if (cmd == 0) {
								ruleaza = 0;
							}
							else {
								printf("\033[1;31m");
								printf("Optiune invalida! Va rugam incercati din nou!\n\n\n");
								printf("\033[0m");
							}

	}
	destroySrv(&allProd);
}
