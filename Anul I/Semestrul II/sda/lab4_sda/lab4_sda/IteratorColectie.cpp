#include "IteratorColectie.h"
#include "Colectie.h"

//tehta(1)
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	curent = c.prim;
}

//theta(1)
TElem IteratorColectie::element() const {
	if (valid())
		return col.elemente[curent];
	throw 1;
}

//theta(n)
bool IteratorColectie::valid() const {
	int i = col.prim;
	while (i != 0) {
		if (i == curent) {
			return true;
		}
		i = col.urmator[i];
	}
	return false;
}

//theta(1)
void IteratorColectie::urmator() {
	if (valid())
		curent = col.urmator[curent];
	else
		throw 1;
}

//theta(1)
void IteratorColectie::precendent() {
	if (valid())
		curent = col.precendet[curent];
	else
		throw 1;
}

void IteratorColectie::prim() {
	curent = col.prim;
}

