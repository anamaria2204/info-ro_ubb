#pragma once
#include <string>
#include <iostream>
#include <map>

using std::string;
using std::cout;
using std::map;

class DTO {
	string entity_type;
	int count;

public:
	DTO(const string& entity_type, int count) : entity_type{ entity_type }, count{ count } {};

	DTO(const string& entity_type) : entity_type{ entity_type }, count{ 0 } {};

	DTO() : entity_type{ "" }, count{ 0 } {};

	const string get_entity_type() const noexcept {
		return entity_type;
	}

	int get_count() const noexcept {
		return count;
	}
};


class Oferta {

private:
	string denumire;
	string destinatie;
	string tip;
	float pret;
public:
	// functie get denumire
	const string get_denumire() const;

	//functie get destinatie
	const string get_destinatie() const;

	//functie get tip
	const string get_tip() const;

	//functie get pret
	const float get_pret() const;

	//functie set denumire
	void set_denumire(const string valoare);

	//functie set destinatie
	void set_destinatie(const string valoare);

	//functie set tip
	void set_tip(const string valoare);

	//functie set pret
	void set_pret(const float valoare) noexcept;

	//functie de printare
	string to_string_print() const;

	//constructor
	Oferta(const string denumire, const string destinatie, const string tip, float pret) :
		denumire{ denumire }, destinatie{ destinatie }, tip{ tip }, pret{ pret } {

	}
	//constructor de copiere
	Oferta(const Oferta& o) = default;

	/*
	Oferta(const Oferta& ot) : denumire{ot.denumire}, destinatie{ot.destinatie}, tip{ot.tip}, pret{ot.pret} {
		cout << "Hi" << '\n';
	}
	*/

	bool operator==(const Oferta& other) const noexcept {
		return (denumire == other.denumire &&
			destinatie == other.destinatie &&
			tip == other.tip &&
			pret == other.pret);
	}
	Oferta() = default;
	~Oferta() = default;

};

/*
Compara doua oferte
@return - 1 daca o1.denumire > o2.denumire, 0 altfel
*/
bool comp_denumire(const Oferta& o1, const Oferta& o2);

/*
Compara doua oferte
@return - 1 daca o1.destinatie > o2.destinatie, 0 altfel
*/
bool comp_destinatie(const Oferta& o1, const Oferta& o2);

