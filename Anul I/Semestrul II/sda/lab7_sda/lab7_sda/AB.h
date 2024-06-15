#pragma once

/*
TAD Arbore binar (cu iteratori in preordine, inordine, postordine si latime)
- reprezentare inlantuita cu alocare dinamica
*/
#include <string>
using namespace std;

class Nod;

typedef Nod* PNod;

typedef int TElem;


class Nod {
private:
	TElem e;
	PNod st, dr;

public:
	friend class AB;
	friend class IteratorAB;
	friend class IteratorPreordine;
	friend class IteratorInordine;
	friend class IteratorPostordine;
	friend class IteratorLatime;

	Nod(TElem e, PNod st, PNod dr);

};


typedef void(*PFunctie)(TElem);

class AB;

class IteratorAB;

class AB {

private:

	//rad este adresa radacinii arborelui
	PNod rad;
	//functia recursiva pentru distrugerea arborelui
	void distruge(PNod);
	//functia recursiva pentru distrugerea subarborilor unui arbore
	void distrugeSubarbori(PNod);
	//copiere subarbore
	PNod copiere(PNod) const;

	//functie ce sterge un element din arbore
	PNod sterge(PNod e, TElem elem, int& removed, int& count, int x);

	//functie ce cauta minimul intr-un arbore
	PNod minim(PNod e);

public:
	friend class IteratorAB;
	friend class IteratorPreordine;
	friend class IteratorInordine;
	friend class IteratorPostordine;
	friend class IteratorLatime;

	//constructorul implicit
	AB();

	//contructor de copiere
	AB(const AB& ab);

	//creeaza un arbore binar care se reduce la o frunza
	AB(TElem elem);

	//constructor arbore binar
	AB(const AB& st, TElem elem, const AB& dr);

	//adauga unui arbore binar subarborele stang
	//arunca exceptie daca arborele este vid
	void adaugaSubSt(const AB& st);

	//adauga unui arbore binar subarborele drept
	//arunca exceptie daca arborele este vid
	void adaugaSubDr(const AB& dr);

	//verifica daca arborele este vid
	bool vid() const;

	//accesare element din radacina
	//arunca exceptie daca arborele este vid
	TElem element() const;

	//accesare subarbore stang
	//arunca exceptie daca arborele este vid
	AB stang() const;

	//accesare subarbore drept
	//arunca exceptie daca arborele este vid
	AB drept() const;

	//iteratori pe arborele binar (ordine="preordine", "postordine", "inordine", "latime")
	IteratorAB* iterator(string ordine) const;

	//functie ce sterge un element din arbore
	void sterge_elem(TElem e);

	//eliminii x aparitii ale lui e
	int eliminaAparitii(int x, TElem e);

	// destructorul arborelui binar
	~AB();
};



