#include "AB.h"
#include "IteratorAB.h"
#include <exception>
#include <string>

//complexitate
//theta(1)
Nod::Nod(TElem e, PNod st, PNod dr) {
	this->e = e;
	this->st = st;
	this->dr = dr;
}

//complexitate
//theta(1)
AB::AB() {
	this->rad = NULL;
}

//complexitate
// best case: theta(1)
// worst case: theta(n)
// average case: O(n)
AB::AB(const AB& ab) {
	this->rad = copiere(ab.rad);
}

//complexitate
//theta(1)
AB::AB(TElem e) {
	this->rad = new Nod(e, NULL, NULL);
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
AB::AB(const AB& st, TElem e, const AB& dr) {
	this->rad = new Nod(e, copiere(st.rad), copiere(dr.rad));
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
PNod AB::copiere(PNod p) const {
	if (p != NULL) {
		//creez radacina
		PNod pNew = new Nod(p->e, NULL, NULL);
		pNew->st = copiere(p->st);
		pNew->dr = copiere(p->dr);
		return pNew;
	}
	return NULL;
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
void AB::distrugeSubarbori(PNod p) {
	if (p != NULL) {
		distruge(p->st);
		distruge(p->dr);
	}
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
void AB::distruge(PNod p) {
	if (p != NULL) {
		distruge(p->st);
		distruge(p->dr);
		delete p;
	}
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
void AB::adaugaSubSt(const AB& st) {
	if (this->vid())
		throw exception();
	
	//distrug vechii subarbori ai subarborelui stang
	distrugeSubarbori(this->rad->st);
	
	//copiez noul subarbore
	this->rad->st = copiere(st.rad);
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
void AB::adaugaSubDr(const AB& dr) {
	if (this->vid())
		throw exception();
	
	//distrug vechii subarbori ai subarborelui drept
	distrugeSubarbori(this->rad->dr);
	
	//copiez noul subarbore
	this->rad->dr = copiere(dr.rad);
}

//complexitate
//theta(1)
TElem AB::element() const {
	if (vid())
		throw exception();
	else
		return rad->e;
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
AB AB::stang() const {
	if (vid())
		throw exception();
	AB ab;
	ab.rad = copiere(rad->st);
	return ab;
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
AB AB::drept() const {
	if (vid())
		throw exception();
	AB ab;
	ab.rad = copiere(rad->dr);
	return ab;
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
AB::~AB() {
	distruge(rad);
}

//complexitate
//theta(1)
bool AB::vid() const {
	if (this->rad == NULL)
		return true;
	return false;
}


IteratorAB* AB::iterator(string s) const {
	if (s == "preordine")
		return new IteratorPreordine(*this);
	if (s == "inordine")
		return new IteratorInordine(*this);
	if (s == "postordine")
		return new IteratorPostordine(*this);
	if (s == "latime")
		return new IteratorLatime(*this);
	return nullptr;
};

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
PNod AB::minim(PNod e) {
	while (e != NULL && e->st != nullptr)
		e = e->st;
	return e;
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
PNod AB::sterge(PNod e, TElem elem, int& removed, int& count, int x) {
	if (e == nullptr)
		return e;

	if (elem < e->e) {
		e->st = sterge(e->st, elem, removed, count, x);
	}
	else if (elem > e->e) {
		e->dr = sterge(e->dr, elem, removed, count, x);
	}
	else {
		// Element gasit
		count++;
		if (count <= x) {
			removed++;
			if (e->st == nullptr) {
				PNod temp = e->dr;
				delete e;
				return temp;
			}
			else if (e->dr == nullptr) {
				PNod temp = e->st;
				delete e;
				return temp;
			}

			// Nod cu doi copii
			PNod temp = minim(e->dr);
			e->e = temp->e;
			e->dr = sterge(e->dr, temp->e, removed, count, x);
		}
	}
	return e;
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
int AB::eliminaAparitii(int x, TElem e) {
	if (vid())
		throw exception();
	int removed = 0;
	int count = 0;
	auto radacina = rad;
	sterge(radacina, e, removed, count, x);

	return removed;;

}