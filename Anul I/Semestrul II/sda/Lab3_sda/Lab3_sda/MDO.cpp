#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;


//complexitate: theta(1)
MDO::MDO(Relatie r) {
	this->prim = new Nod;
	this->r = r;
	this->lungime = 0;
	this->ultim = new Nod;
}

//complexitate: 
// best case: theta(1) 
// worst case: theta(n)
// average case: theta(n)
void MDO::adaugaprim(TCheie c, TValoare v) {

	Nod* newnod = new Nod;
	if (this->prim->precedent == nullptr) {
		this->prim->urmator = newnod;
		newnod->precedent = this->prim;
		newnod->urmator = this->ultim;
		this->ultim->precedent = newnod;
	}
	else {
		Nod* curent = this->prim->urmator;
		Nod* precedent = this->prim;
		while (curent != nullptr && this->r(curent->elem.first, c)) {
			precedent = curent;
			curent = curent->urmator;
		}
		if (curent == nullptr) {
			curent = precedent;
			curent->urmator = newnod;
			newnod->precedent = curent;
			this->ultim->precedent = newnod;
		}
		else {
			newnod->urmator = curent;
			newnod->precedent = curent->precedent;
			curent->precedent->urmator = newnod;
			curent->precedent = newnod;
		}
	}
}

//complexitate: 
// best case: theta(1) 
// worst case: theta(n)
// average case: theta(n)
void MDO::adaugaultim(TCheie c, TValoare v) {
	Nod* newnod = new Nod;
	newnod->elem = TElem(c, v);
	if (this->ultim->precedent == nullptr) {
		this->ultim->precedent = newnod;
		newnod->urmator = this->ultim;
		newnod->precedent = this->prim;
		this->prim->urmator = newnod;
	}
	else {
		Nod* curent = this->ultim->precedent;
		while (curent != this->prim && this->r(c, curent->elem.first))
			curent = curent->precedent;
		curent->urmator->precedent = newnod;
		newnod->urmator = curent->urmator;
		curent->urmator = newnod;
		newnod->precedent = curent;
	}
}

//complexitate: 
// best case: theta(1) 
// worst case: theta(n)
// average case: theta(n)
void MDO::adauga(TCheie c, TValoare v) {
	if (this->ultim->elem.first <= c) {
		this->adaugaultim(c, v);
	}
	else {
		this->adaugaprim(c, v);
	}
	++this->lungime;
}

//complexitate: 
// best case: theta(1) 
// worst case: theta(n)
// average case: theta(n)
vector<TValoare> MDO::cauta(TCheie c) const {
	vector<TValoare> valori;
	Nod* curent = this->prim->urmator;
	while (curent != nullptr && this->r(curent->elem.first, c)) {
		if (curent->elem.first == c)
			valori.push_back(curent->elem.second);
		curent = curent->urmator;
	}
	return valori;
}

//complexitate: 
// best case: theta(1) 
// worst case: theta(n)
// average case: theta(n)
bool MDO::sterge(TCheie c, TValoare v) {
	Nod* curent = this->prim->urmator;
	while (curent != this->ultim && this->r(curent->elem.first, c)) {
		if (curent->elem.first == c && curent->elem.second == v) {
			Nod* precedent = curent->precedent, * urmator = curent->urmator;
			precedent->urmator = urmator;
			urmator->precedent = precedent;
			--this->lungime;
			return true;
		}
		curent = curent->urmator;
	}
	return false;
}

//complexitate: theta(1)
int MDO::dim() const {
	return lungime;
}

//complexitate: theta(1)
bool MDO::vid() const {
	return lungime == 0;
}

//complexitate: theta(1)
IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

//complexitate: 
// best case: theta(1) 
// worst case: theta(n)
// average case: theta(n)
MDO::~MDO() {
	Nod* curent = this->prim->urmator;
	while (curent != nullptr) {
		Nod* urmator = curent->urmator;
		delete curent;
		curent = urmator;
	}
	if (this->prim != nullptr)
		delete this->prim;
}
