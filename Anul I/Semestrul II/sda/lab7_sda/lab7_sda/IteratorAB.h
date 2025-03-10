#pragma once
#include "AB.h"
#include <stack>
#include <queue>


using std::stack;
using std::queue;

class IteratorAB {
public:

	friend class AB;

	//operatii pe iterator
	virtual void prim() = 0;

	virtual void urmator() = 0;

	virtual TElem element() = 0;

	virtual bool valid() = 0;
};

class IteratorPreordine : public IteratorAB {
	friend class AB;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorPreordine(const AB& _ab);

	//contine o referinta catre containerul pe care il itereaza

	const AB& ab;

	stack<PNod> s;
	PNod actual;


public:

	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid();

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element();
};


#include <exception>
class IteratorInordine : public IteratorAB {
	friend class AB;
private:
	//constructorul primeste o referinta catre Container
	  //iteratorul va referi primul element din container
	IteratorInordine(const AB& ab);

	//contine o referinta catre containerul pe care il itereaza

	const AB& ab;
	/* aici e reprezentarea specifica a iteratorului*/

	stack<PNod> s;
	PNod actual;



public:

	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid();

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element();
};


class IteratorPostordine : public IteratorAB {
	friend class AB;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorPostordine(const AB& _ab);
	//contine o referinta catre containerul pe care il itereaza

	const AB& ab;
	/* aici e reprezentarea specifica a itertorului*/

	struct el {
		PNod p;
		int k = 0;
	};

	stack<el> s;
	el actual;


public:

	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid();

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element();
};

class IteratorLatime : public IteratorAB {
	friend class AB;
private:

	//constructorul primeste o referinta catre Container
	 //iteratorul va referi primul element din container
	IteratorLatime(const AB& _ab);
	//contine o referinta catre containerul pe care il itereaza

	const AB& ab;
	/* aici e reprezentarea specifica a itratorului*/

	queue<PNod> q;
	PNod actual;


public:

	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid();

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element();
};
