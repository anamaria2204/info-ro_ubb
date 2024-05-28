#pragma once

#include "domeniu.h"
#include <string>
#include <ostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <random>
#include <iterator>

#include <exception>
#include <string>
#include <utility>

using std::string;
using std::exception;

using std::find_if;
using std::vector;
using std::string;
using std::ostream;
using std::make_pair;

class RepoAbs {
public:
	virtual void store(const Oferta& o) = 0;

	virtual void modifica(const Oferta& o, const string& denumire_noua, const string& destinatie_noua,
		const string& tip_nou, const float pret_nou) = 0;

	virtual void sterge(const Oferta& o) = 0;

	virtual int cauta(const string& denumire, const string& destinatie) = 0;

	virtual vector<Oferta>& getAll() noexcept = 0;

	virtual ~RepoAbs() = default;
};
class OfertaRepo {
	vector<Oferta> lista_oferte;

public:
	OfertaRepo() = default;

	explicit OfertaRepo(const vector<Oferta>& lista_oferte) : lista_oferte{ lista_oferte } {};

	virtual ~OfertaRepo() = default;
	/*
	Salvare oferta
	arunca exceptie daca mai exista o oferta cu aceasi denumire
	si destinatie
	*/
	virtual void store(const Oferta& o);

	/*
	sterge o oferta
	sterge o oferta daca aceasta exista in lista
	*/

	virtual void sterge(const Oferta& o);

	/*
	modifica o oferta din lista de oferte
	*/
	virtual void modifica(const Oferta& o, const string& denumire_noua, const string& destinatie_noua,
		const string& tip_nou, const float pret_nou);

	/*
	cauta o oferta in lista de oferte cu denumirea si destinatia data
	arunca exceptie daca oferta cautata nu este in lista
	*/
	virtual int cauta(const string& denumire_data, const string& destinatie_data);

	/*
	returneaza toate ofertele salvate
	*/
	virtual vector<Oferta>& getAll() noexcept;

};


/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class OfertaRepoException : public exception{
	string mesaj;
public:
	OfertaRepoException(string mesaj) :mesaj(move(mesaj)) {}
	string get_mesaj() { return this->mesaj; }
};


class RepoFile : public OfertaRepo {
private:
	string file_name;
	void load_from_file();
	void write_to_file();

public:
	RepoFile(string file_name) : OfertaRepo(), file_name{ file_name } {
		load_from_file(); //incarcam date din fisier
	}

	void store(const Oferta& o) override {
		OfertaRepo::store(o);
		write_to_file();
	}

	void sterge(const Oferta& o) override {
		OfertaRepo::sterge(o);
		write_to_file();
	}

	void modifica(const Oferta& o, const string& denumire_noua, const string& destinatie_noua,
		const string& tip_nou, const float pret_nou) override {
		OfertaRepo::modifica(o, denumire_noua, destinatie_noua, tip_nou, pret_nou);
		write_to_file();
	}
};