#pragma once
#include <string>
#include "repo.h"
#include "domeniu.h"
#include "validator.h"
#include <vector>
#include <functional>

using std::string;
using std::vector;
using std::function;


class OfertaService {

	OfertaRepo& repo;
	OfertaValidator& val;

	/*
	Sorteaza lista de oferte
	 maiMareF - functie care compara 2 oferte, verifica daca are loc relatia mai mare
			  - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Pet)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	VectorDinamic<Oferta> generalSort(bool (*maiMicF)(const Oferta&, const Oferta&));


	/*
	Filtreaza lista de oferte oferind o copie a lisei cu elementele dorite
	@param - fct functie
	@return - lista noua cu ofertele filtrate
	*/
	VectorDinamic<Oferta> filtreaza(function<bool(const Oferta&)> fct);

public:
	OfertaService(OfertaRepo& repo, OfertaValidator& val) :repo{ repo }, val{ val } {
	}
	//nu permitem copierea de obiecte PetStore
	OfertaService(const OfertaService& ot) = delete;

	OfertaService() = default;
	/*
	 returneaza toate ofertele in ordinea in care au fost adaugate
	*/
	VectorDinamic<Oferta> getAll(){
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
	VectorDinamic<Oferta> filtreaza_destinatie(string destinatie);

	/*
	Filtreaza lista de oferte dupa pret
	@param - pret
	@return - lista de oferte filtrate
	*/
	VectorDinamic<Oferta> filtreaza_pret(float pret);

	/*
	Sorteaza lista de oferte dupa denumire
	@return - lista sortata
	*/
	VectorDinamic<Oferta> sorteaza_denumire();

	/*
	Sorteaza lista de oferte dupa destinatie
	@return - lista sortata
	*/
	VectorDinamic<Oferta> sorteaza_destinatie();

	/*
	Sorteaza lista de oferte dupa pret si tip
	@return - lista sortata
	*/
	VectorDinamic<Oferta> sorteaza_tip_pret();

	~OfertaService() = default;
};

class OfertaServiceException {
	string msg;
public:
	OfertaServiceException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const OfertaServiceException& ex);
};

ostream& operator<<(ostream& out, const OfertaServiceException& ex);
