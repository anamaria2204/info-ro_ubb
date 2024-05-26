#pragma once

#include "domeniu.h"

#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>
#include <ostream>

using std::ostream;
using std::string;
using std::shuffle;
using std::vector;

class Wishlist {
private:
	vector<Oferta> list;

public:
	void wishlist_gol() noexcept;
	
	void adauga_wishlist(const Oferta& oferta);

	void genereza_wishlist(int nr_oferte, const vector<Oferta>& of);

	void exporta_wishlist(const string& nume_fisier);

	const vector<Oferta>& get_oferta();

	int cauta_wishlist(const string& denumire, const string& destinatie);
};

class OfertaWishlistException {
	string msg;
public:
	OfertaWishlistException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const OfertaWishlistException& ex);
};

ostream& operator<<(ostream& out, const OfertaWishlistException& ex);

