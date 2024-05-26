#pragma once

#include "domeniu.h"
#include "VectorDinamic.h"
#include <string>
#include <ostream>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class OfertaRepo {
	VectorDinamic<Oferta> lista_oferte;
	/*
	metoda privata verifica daca exista deja p in repository
	*/
	bool exist(const Oferta& o) const;

public:
	OfertaRepo() = default;
	OfertaRepo(const OfertaRepo& of) = delete;

	/*
	Salvare oferta
	arunca exceptie daca mai exista o oferta cu aceasi denumire
	si destinatie
	*/
	void store(const Oferta& o);

	/*
	sterge o oferta
	sterge o oferta daca aceasta exista in lista
	*/

	void sterge(const int& pozitia);

	/*
	modifica o oferta din lista de oferte
	*/
	void modifica(const Oferta& o, const string& denumire_noua, const string& destinatie_noua,
		const string& tip_nou, const float pret_nou);

	/*
	cauta o oferta in lista de oferte cu denumirea si destinatia data
	arunca exceptie daca oferta cautata nu este in lista
	*/
	const Oferta& cauta(const string& denumire_data, const string& destinatie_data) const;

	/*
	returneaza toate ofertele salvate
	*/
	VectorDinamic<Oferta> getAll() const;

	~OfertaRepo() = default;
};


/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class OfertaRepoException {
	string msg;
public:
	OfertaRepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const OfertaRepoException& ex);
};

ostream& operator<<(ostream& out, const OfertaRepoException& ex);
