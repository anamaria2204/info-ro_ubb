#include "AB.h"
#include "IteratorAB.h"

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
IteratorInordine::IteratorInordine(const AB& _ab) :ab(_ab) {
	actual = NULL;
	actual = _ab.rad;
	prim();
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
void IteratorInordine::prim() {
	//creem stiva
	while (!s.empty())
		s.pop();
	actual = ab.rad;

	while (actual != NULL)
	{
		//se adauga in stiva ramura stanga a elementului curent
		s.push(actual);
		actual = actual->st;
	}
	//se acceseaza nodul din varful stivei
	if (!s.empty())
		actual = s.top();
}

//complexitate
//theta(1)
bool IteratorInordine::valid() {
	return actual != NULL;
}

//complexitate
//theta(1)
TElem IteratorInordine::element() {
	if (!valid())
		throw exception();
	else
		return actual->e;
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
void IteratorInordine::urmator() {
	if (!valid())
		throw exception();
	PNod aux = s.top();
	s.pop();
	if (actual->dr != NULL) {
		actual = actual->dr;
		while (actual != NULL) {
			s.push(actual);
			actual = actual->st;
		}
	}
	if (!s.empty()) {
		actual = s.top();
	}
	else {
		actual = NULL;
	}
}

IteratorPreordine::IteratorPreordine(const AB& _ab) :ab(_ab) {
	actual = NULL;
	prim();
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
void IteratorPreordine::prim() {
	while (!s.empty()) {
		s.pop();
	}
	actual = ab.rad;
	s.push(ab.rad);
}

//complexitate
//theta(1)
bool IteratorPreordine::valid() {
	return actual != NULL;
}

//complexitate
//theta(1)
TElem IteratorPreordine::element() {
	if (!valid())
		throw exception();
	return actual->e;
}

//complexitate
//theta(1)
void IteratorPreordine::urmator() {
	if (!valid())
		throw exception();
	PNod aux = s.top();
	s.pop();
	if (aux->dr != NULL)
		s.push(aux->dr);
	if (aux->st != NULL) {
		s.push(aux->st);
	}
	if ((!s.empty()))
		actual = s.top();
	else
		actual = NULL;
}

//complexitate
//theta(1)
IteratorPostordine::IteratorPostordine(const AB& _ab) :ab(_ab) {
	actual.p = _ab.rad;
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//average case: O(n)
void IteratorPostordine::prim() {
	while (!s.empty())
		s.pop();
	actual.k = 0;
	actual.p = ab.rad;
	s.push(actual);
	while (actual.p != NULL) {
		el x;
		x.k = 0;
		x.p = actual.p;
		s.push(x);
		actual.p = actual.p->st;
	}
}

//complexitate
//theta(1)
bool IteratorPostordine::valid() {
	return actual.p != NULL && !s.empty();
}

//complexitate
//theta(1)
TElem IteratorPostordine::element() {
	if (!valid())
		throw exception();
	else
		return actual.p->e;
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//best case: O(n)
void IteratorPostordine::urmator() {
	if (!valid())
		throw exception();
	while (actual.p != NULL) {
		el x;
		x.k = 0;
		x.p = actual.p;
		s.push(x);
		actual.p = actual.p->st;
	}

	el x = s.top();
	s.pop();
	if (x.k == 0) {
		//nu s-a traversat subarborele drept
		x.k = 1;
		s.push(x);
		actual.p = x.p->dr;
	}
}

//theta(1)
IteratorLatime::IteratorLatime(const AB& _ab) :ab(_ab) {
	actual = NULL;
	prim();
}

//complexitate
//best case: theta(1)
//worst case: theta(n)
//best case: O(n)
void IteratorLatime::prim() {
	while (!q.empty())
		q.pop();
	actual = ab.rad;
	q.push(ab.rad);
}

//complexitate
//theta(1)
bool IteratorLatime::valid() {
	return actual != NULL;
}

//complexitate
//theta(1)
TElem IteratorLatime::element() {
	if (!valid())
		throw exception();
	return actual->e;
}

//complexitate
//theta(1)
void IteratorLatime::urmator() {
	if (!valid())
		throw exception();

	PNod aux = q.front();
	q.pop();
	if (aux->st != NULL)
		q.push(aux->st);
	if (aux->dr != NULL)
		q.push(aux->dr);
	if (!q.empty()) 
		actual = q.front();
	else
		actual = NULL;
}
