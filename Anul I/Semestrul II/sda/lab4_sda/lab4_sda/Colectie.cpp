#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

#define inf 999999

using namespace std;

bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}
//theta(1)
Colectie::Colectie() {
	this->r = r;
	this->capacitate = 70000;
	this->lungime = 0;

	this->elemente = new TElem[capacitate];
	this->urmator = new int[capacitate];
	this->precendet = new int[capacitate];

	this->prim = 0;
	this->ultim = 0;
	this->primLiber = 0;

	initSpatiuLiber();
}

//theta(1)
int Colectie::aloca() {
	//se sterge primul element din lista spatiului liber
	int i = primLiber;
	primLiber = urmator[primLiber];
	precendet[primLiber] = 0;
	return i;
}

//theta(1)
void Colectie::dealoca(int i) {
	//se trece pozitia i in lista spatiului liber
	precendet[primLiber] = i;
	urmator[i] = primLiber;
	primLiber = i;
	precendet[primLiber] = 0;

	elemente[primLiber] = -1;
	
}

//theta(capacitate)
void Colectie::initSpatiuLiber() {
	for (int i = 0; i < capacitate - 1; i++) {
		urmator[i] = i + 1;
	}
	urmator[capacitate] = 0;
	primLiber = 1;
}

//theta(n)
int Colectie::creeazaNod(TElem v) {
	if (primLiber == 0) {
		redim();
	}
	int i = aloca();
	elemente[i] = v;
	urmator[i] = 0;
	precendet[i] = 0;
	return i;
}

//theta(n)
void Colectie::redim() {
	TElem* enou = new TElem[2 * capacitate];
	int* unou = new int[2 * capacitate];
	int* pnou = new int[2 * capacitate];

	for (int i = 0; i <= lungime; i++) {
		enou[i] = elemente[i];
		unou[i] = urmator[i];
		pnou[i] = precendet[i];
	}

	capacitate *= 2;
	delete[] elemente;
	delete[] urmator;
	delete[] precendet;

	elemente = enou;
	urmator = unou;
	precendet = pnou;
	primLiber = lungime + 1;

	for (int i = lungime + 1; i < capacitate; i++) {
		urmator[i] = i + 1;
		precendet[i] = i - 1;
	}
	urmator[capacitate] = 0;
	precendet[capacitate] = capacitate - 1;
	precendet[primLiber] = 0;
}

//theta(n)
void Colectie::adauga(TElem e) {
	int nou = creeazaNod(e);

	int crt = prim;
	while (crt != 0) {
		if (!rel(elemente[crt], e)) {
			break;
		}
		crt = urmator[crt];
	}
	if (crt == prim && crt == ultim && prim == 0) {
		//primul element din lista
		urmator[nou] = 0;
		precendet[nou] = 0;
		prim = nou;
		ultim = nou;
	}
	else if (crt == prim) {
		precendet[prim] = nou;
		urmator[nou] = prim;
		prim = nou;
		precendet[prim] = 0;
	}
	else if (crt == 0) {
		//se adauga dupa ultimul
		urmator[ultim] = nou;
		precendet[nou] = ultim;
		urmator[nou] = 0;
		ultim = nou;
	}
	else {
		//daca e la mijloc
		urmator[precendet[crt]] = nou;
		precendet[nou] = precendet[crt];

		precendet[crt] = nou;
		urmator[nou] = crt;
	}
	lungime++;
}

//O(n)
bool Colectie::sterge(TElem e) {
	if (vida()) {
		return false;
	}
	if (cauta(e) == false) {
		return false;
	}

	int p = prim;
	while (p != 0) {
		if (elemente[p] == e) {
			break;
		}
		p = urmator[p];
	}

	if (elemente[p] != e)
		return false;

	if (p == prim) {
		prim = urmator[p];
		precendet[prim] = 0;
	}
	else if (p == ultim) {
		ultim = precendet[p];
		urmator[ultim] = 0;
	}
	else {
		int q = precendet[p];
		urmator[q] = urmator[p];
		precendet[urmator[p]] = q;
	}
	dealoca(p);
	lungime--;
	return true;
}

//O(n)
bool Colectie::cauta(TElem elem) const {
	int crt = prim;
	while (crt != 0) {
		if (elemente[crt] == elem) {
			return true;
		}
		if (!rel(elemente[crt], elem)) {
			break;
		}
		crt = urmator[crt];
	}
	return false;
}

//theta(n)
int Colectie::nrAparitii(TElem elem) const {
	int n = 0;
	int crt = prim;
	while (crt != 0) {
		if (elemente[crt] == elem) {
			n++;
		}
		if (!rel(elemente[crt], elem)) {
			break;
		}
		crt = urmator[crt];
	}
	return n;
}


//theta(1)
int Colectie::dim() const {
	return lungime;
}

//theta(1)
bool Colectie::vida() const {
	return prim == 0;
}


IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

//theta(n)
Colectie::~Colectie() {
	/*
	delete[] e;
	delete[] urmator;
	delete[] precendet;
	*/
}

//complexitate
//best case: theta(n)
//worst case: theta(n^2)
//average case: O(n^2)

int Colectie::transformaInMultime() {
	IteratorColectie it = iterator();
	int nr = 0;
	it.prim();
	while (it.valid()) {
		TElem el = it.element();
		int nr_ap = nrAparitii(it.element());
		if (nr_ap > 1) {
			it.urmator();
			sterge(el);
			nr++;
		}
		else {
			it.urmator();
		}
	}
	return nr;
}
