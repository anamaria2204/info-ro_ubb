#include "Matrice.h"

#include <exception>
#include <tuple>

using namespace std;
int poz = 0;

//{theta(1)}

Matrice::Matrice(int m, int n){	
	if (n <= 0 || m <= 0)
		throw exception();
	this->n = n;
	this->m = m;
	capacitate = m * n;
	lungime = 0;
	vector = new TPair[capacitate];
}

//{theta(1)}
int Matrice::nrLinii() const { 
	return n;
}

//{theta(1)}
int Matrice::nrColoane() const { 
	return m;
}

//{
// worst: theta(log2(n)), 
// best: theta(1)
// average: O(log2(n)
// }
TElem Matrice::element(int i, int j) const { 
	if (i < 0 || j < 0 || i >= n || j >= n)
		throw exception();
	int mij, st = 0, dr = lungime - 1, pi, pj;
	while (st <= dr) {
		mij = (st + dr) / 2;
		pi = get<0>(vector[mij]);
		pj = get<1>(vector[mij]);
		if (pi < 0 || pj < 0 || pi >= n || pj >= m)
			throw exception();
		if (pi == i && pj == j)
			return get<2>(vector[mij]);
		if (i < pi || i == pi && j < pj)
			dr = mij - 1;
		else
			st = mij + 1;
	}
	return NULL_TELEMENT;
}

//{
// complexitatea: O(n)
// }
TElem Matrice::modifica(int i, int j, TElem e) { 
	if (i < 0 || j < 0 || i >= n || j >= m)
		throw exception();
	TElem vechi = element(i,j);
	int mij, pi, pj, dr = lungime, st = 0, lastst = 0;
	while (st < dr) {
		mij = (st + dr) / 2;
		if(mij < 0 || mij >= lungime)
			throw exception();
		pi = get<0>(vector[mij]);
		pj = get<1>(vector[mij]);
		if (pi == i && pj == j) {
			get<2>(vector[mij]) = e;
			return vechi;
		}
		if (i < pi || i == pi && j < pj) {
			dr = mij;
		}
		else {
			st = mij + 1;
			lastst = st;
		}
	}
		
	TPair pereche = make_tuple(i, j, e);
	int poz = lastst;
	for (int k = lungime-1; k >= poz; k--) {
		vector[k+1] = vector[k];
	}
	vector[poz] = pereche;
	lungime++;
	return NULL_TELEMENT;
}

//complexitate:
//theta(n*m)
Matrice Matrice::transpusa() const { 
	Matrice Mattranspusa = Matrice::Matrice(m,n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			TElem x = element(j, i);
			Mattranspusa.modifica(i, j, x);
		}
	}
	return Mattranspusa;

}