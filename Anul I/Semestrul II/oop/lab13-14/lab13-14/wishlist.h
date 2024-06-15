#pragma once

#include "domeniu.h"

#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>
#include <ostream>
#include <exception>
#include <string>
#include <utility>

using std::string;
using std::exception;

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

class OfertaWishlistException : public exception {
	string mesaj;
public:
	OfertaWishlistException(string mesaj) :mesaj(move(mesaj)) {}
	string get_mesaj() { return this->mesaj; }
};
