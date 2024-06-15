#pragma once
#include <string>
#include "repo.h"
#include "domeniu.h"
#include "validator.h"
#include <vector>
#include <functional>
#include "wishlist.h"
#include <map>
#include <random>
#include <algorithm>
#include "undo.h"
#include <exception>
#include <string>
#include <utility>
#include "observer.h"

using std::string;
using std::exception;

using std::string;
using std::vector;
using std::function;
using std::map;
using std::copy_if;
using std::shuffle;
using std::unique_ptr;


class OfertaService: public Observable {

	OfertaRepo& repo;
	OfertaValidator& val;
	Wishlist lista;

	//tinem pointeri la ActiuneUndo pentru ca vrem apel polimorfic
	//punem unique_ptr pentru ca avem responsabilitatea de a elibera memoria pentru 
	std::vector<unique_ptr<ActiuneUndo>> undoActions;

	/*
	Sorteaza lista de oferte
	 maiMareF - functie care compara 2 oferte, verifica daca are loc relatia mai mare
			  - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Pet)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	vector<Oferta> generalSort(bool (*maiMicF)(const Oferta&, const Oferta&));


	/*
	Filtreaza lista de oferte oferind o copie a lisei cu elementele dorite
	@param - fct functie
	@return - lista noua cu ofertele filtrate
	*/
	vector<Oferta> filtreaza(function<bool(const Oferta&)> fct);

public:
	OfertaService(OfertaRepo& repo, OfertaValidator& val, Wishlist& lista) :repo{ repo }, val{ val }, lista{ lista } {
	}
	//nu permitem copierea de obiecte PetStore
	OfertaService(const OfertaService& ot) = delete;

	//destructor
	~OfertaService();

	void operator=(const OfertaService& ot) = delete;

	/*
	 returneaza toate ofertele in ordinea in care au fost adaugate
	*/
	const vector<Oferta>& getAll() noexcept {
		return repo.getAll();
	}
	/*
	Adauga o noua oferta
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void adauga(const string& denumire, const string& destinatie, const string& tip, float pret);

	/*
	Sterge o oferta din lista
	arunca exceptie daca oferta nu este in lista
	*/

	void stergere(const int pozitie);

	/*
	Modifica o oferta din lista de oferte
	arunca exceptie daca oferta nu este in lista
	*/
	void modificare(int pozitie, const string& denumire_noua, const string& destinatie_noua,
		const string& tip_nou, const float pret_nou);

	/*
	Cauta o oferta in lista de oferte
	arunca exceptie daca oferta nu este in lista
	*/
	const Oferta& cautare(const string& denumire_data, const string& destinatie_data) const;


	/*
	Filtreaza lista de oferte dupa destinatie
	@param - destinatie
	@return - lista de oferte filtrate
	*/
	vector<Oferta> filtreaza_destinatie(string destinatie);

	/*
	Filtreaza lista de oferte dupa pret
	@param - pret
	@return - lista de oferte filtrate
	*/
	vector<Oferta> filtreaza_pret(float pret);

	/*
	Sorteaza lista de oferte dupa denumire
	@return - lista sortata
	*/
	vector<Oferta> sorteaza_denumire();

	/*
	Sorteaza lista de oferte dupa destinatie
	@return - lista sortata
	*/
	vector<Oferta> sorteaza_destinatie();

	/*
	Sorteaza lista de oferte dupa pret si tip
	@return - lista sortata
	*/
	vector<Oferta> sorteaza_tip_pret();

	/*
	returneaza numarul de oferte din cos
	*/
	int nr_oferte_in_cos();

	/*
	Adauga in cos o oferta data
	*/
	void adauga_in_cos(const string& denumire, const string& destinatie);

	/*
	Sterge continutul cosului
	*/
	void sterge_oferte_cos();
	/*
	Genereaza un cos cu oferte din memorie
	@param - nr de oferte dorite
	*/
	void genereaza_cos(int nr_oferte);

	/*
	Exporta ofertele intr-un fisier de tip html
	*/
	void exporta_cos(const string& nume);

	/*
	raport dto
	*/
	map<string, DTO> raport() noexcept;

	/*
	functia de undo
	*/
	void undo();

	/*
	returneaza ofertele din cos
	*/
	const vector<Oferta>& getAllOferte() noexcept {
		return lista.get_oferta();
	}
};

class OfertaServiceException : public exception {
	string mesaj;
public:
	OfertaServiceException(string mesaj) :mesaj(move(mesaj)) {}
	string get_mesaj() { return this->mesaj; }
};
