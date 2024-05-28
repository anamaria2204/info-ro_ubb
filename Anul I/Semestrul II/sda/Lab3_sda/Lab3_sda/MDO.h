#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

#define NULL_TVALUE -111111
#define NULL_TELEM pair<TCheie, TValoare>(-111111, -111111);

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

typedef struct Nod {
	TElem elem = NULL_TELEM;
	Nod* precedent = nullptr;
	Nod* urmator = nullptr;
} Nod;

class MDO {
	friend class IteratorMDO;
private:
	Nod* prim;
	Nod* ultim;
	Relatie r;
	int lungime;
public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);
	void adaugaprim(TCheie c, TValoare v);
	void adaugaultim(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	Nod* getNod(TCheie, TValoare) const;

	// destructorul 	
	~MDO();

};
