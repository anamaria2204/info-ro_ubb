#include "service.h"
#include "repo.h"
#include "domain.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

Srv createService() {
	Srv srvprod = {
		.actual = NULL,
		.undo = NULL
	};
	srvprod.actual = create_list((destroy_fct)(destroy_produs));
	srvprod.undo = create_list((destroy_fct)(destroy));
	return srvprod;
}

void destroySrv(Srv* srvprod) {
	destroy(srvprod->actual);
	for (int i = 0; i < srvprod->undo->lg; i++) {
		destroy(srvprod->undo->elems[i]);
	}
	free(srvprod->undo->elems);
	free(srvprod->undo);
}

int addProduct(Srv* l, int id, char* tip, char* producator, char* model, float pret, int cantitate) {
	for (int i = 0; i < size(l->actual); ++i) {
		Produs* existing_product = get(l->actual, i);
		if (existing_product->id == id)
			if (strcmp(existing_product->tip, tip) == 0 && strcmp(existing_product->model, model) == 0 && strcmp(existing_product->producator, producator) == 0) {
				existing_product->cantitate += cantitate;
				MyList* toUndo = copyList(l->actual, (copy_fct)copieProdus);
				add(l->undo, (TElem*)toUndo);
				set(l->actual, i, existing_product);
				return 0;
			}
			else {
				return 1;
			}
	}

	int succ = validate(id, tip, producator, model, pret, cantitate);
	if (succ != 0) 
		return succ;
	if (succ == 0) {
		MyList* toUndo = copyList(l->actual, (copy_fct)copieProdus);
		Produs* p = create_produs(id, tip, producator, model, pret, cantitate);
		add(l->actual, (TElem*)p);
		add(l->undo, (TElem*)toUndo);
	}
	return 0;
}

int updateProduct(Srv* l, int id, float new_price, int new_quantity) {
	for (int i = 0; i < size(l->actual); ++i) {
		Produs* current_product = get(l->actual, i);
		MyList* toUndo = copyList(l->actual, (copy_fct)copieProdus);
		if (current_product->id == id) 
			if (new_price > 0) {
				current_product->pret = new_price;
				current_product->cantitate = new_quantity;
				set(l->actual, i, current_product);
				add(l->undo, (TElem*)toUndo);
			return 1;
			}
		destroy(toUndo);
	}
	return 0;
}

int stergeProdus(Srv* l, int id) {
	for (int i = 0; i < size(l->actual); ++i) {
		Produs* current_product = get(l->actual, i);
		MyList* toUndo = copyList(l->actual, (copy_fct)copieProdus);
		if (current_product->id == id) {
			remove_at(l->actual, i);
			add(l->undo, (TElem*)toUndo);
			return 1;
		}
		destroy(toUndo);
	}
	return 0;
}

MyList* getAllProduct(MyList* l, char* typeSubstring, cauta_sir cs) {
	MyList* rez = create_list(l->destructor);
	for (int i = 0; i < size(l); i++) {
		Produs* p = get(l, i);
		if (cs(p, typeSubstring) == 1) {
			add(rez, (TElem*)copieProdus(p));
		}
	}
	return rez;
}

MyList* getAllProductPret(MyList* l, float pret, compara_pret cp) {
	MyList* rez = create_list(l->destructor);
	for (int i = 0; i < size(l); i++) {
		Produs* p = get(l, i);
		if (cp(p, pret) == 1) {
			add(rez, (TElem*)copieProdus(p));
		}
	}
	return rez;
}


MyList* getAllProductbyquantite(MyList* l, int cantitate, compara_cantitate cc) {
	MyList* rez = create_list(l->destructor);
	for (int i = 0; i < size(l); i++) {
		Produs* p = get(l, i);
		if (cc(p, cantitate) == 1) {
			add(rez, (TElem*)copieProdus(p));
		}
	}
	return rez;
}

MyList* sortare(MyList* lista, int crescator, sorteaza cmp1, sorteaza cmp2) {
	MyList* copie = copyList(lista, (copy_fct)copieProdus);

	for (int i = 0; i < copie->lg - 1; i++) {
		for (int j = i + 1; j < copie->lg; j++) {
			int cmp_result;
			if (crescator) {
				cmp_result = cmp1(copie->elems[i], copie->elems[j]);
				if (cmp_result == 1 || (cmp_result == 2 &&
					cmp2(copie->elems[i], copie->elems[j]) == 1)) {
					TElem* temporar = copie->elems[i];
					copie->elems[i] = copie->elems[j];
					copie->elems[j] = temporar;
				}
			}
			else {
				cmp_result = cmp1(copie->elems[i], copie->elems[j]);
				if (cmp_result == 0 || (cmp_result == 2 &&
					cmp2(copie->elems[i], copie->elems[j]) == 1)) {
					TElem* temporar = copie->elems[i];
					copie->elems[i] = copie->elems[j];
					copie->elems[j] = temporar;
				}
			}
		}
	}
	return copie;
}

int undo(Srv* srv) {
	if (srv->undo->lg <= 0) {
		return 0;
	}
	MyList* new_lst = removeLast(srv->undo);
	destroy(srv->actual);
	srv->actual = new_lst;

	return 1;
}

MyList* getAllProductbyproducator(MyList* l, char litera, compara_litera cl) {
	MyList* rez = create_list(l->destructor);
	for (int i = 0; i < size(l); i++) {
		Produs* p = get(l, i);
		if (cl(p, litera) == 1) {
			add(rez, (TElem*)copieProdus(p));
		}
	}
	return rez;
}