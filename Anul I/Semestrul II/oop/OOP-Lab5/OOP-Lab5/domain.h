#pragma once
#pragma once

typedef struct {
	int id;
	char* tip;
	char* producator;
	char* model;
	float pret;
	int cantitate;

} Produs;

/**
 * Functia creeaza un element de tip produs
 * @param id		  - id-ul produsului
 * @param  producator - producatorul produsului
 * @param  model      - modelul produsului
 * @param  pret		  - pretul produsului
 * @param  cantitate  - cantitatea de produse
 * @return produsul cu caracteristicile de mai sus
 * */
Produs* create_produs(int id, char* tip, char* producator, char* model, float pret, int cantitate);

/**
 * Functia valideaza o posibila materie
 * @return 0 sau 1, in functie de validitatea intrarii
 */
int validate(int id, char* tip, char* producator, char* model, float pret, int cantitate);

/**
 * Functia distruge un element de tip produs
 * @param produs - produsul de distrus
 */
void destroy_produs(Produs* produs);


/*
* Copiaza un element de tip produs
* @param produs - de copiat
*/
Produs* copieProdus(Produs* p);

/*
* Compara pretul a doua produse
* return: 1 daca p1->pret > p2->pret 0 altfel
*/

int comparaPret(Produs* p1, Produs* p2);

/*
* Compara cantitatea a doua produse
* return: 1 daca p1->cantitate > p2->cantitate 0 altfel
*/

int comparaCantitate(Produs* p1, Produs* p2);

/*
*Functia returneaza 1 daca un sir se afla in producator
*
*/

int cautaSir(Produs* p, char* sir);

/*
*Functia returneaza 1 pretul produsului p este egal cu pret
*/

int comparaPretul(Produs* p, float pret);

/*
*Functia returneaza 1 cantitatea produsului p este egal cu cantitatea
*/
int comparaCantitatea(Produs* p, int cantitate);

/*
* Functia verifica daca doua produse sunt identice
* @param - doua produse
* @return- 1 daca cele doua sunt identice, 0 altfel
*/

int produseEgale(Produs* p1, Produs* p2);

/*
* Functia compara prima litera din p->producator cu o litera data
* @return: 1 - daca litera este egala, 0 altfel
* 
*/
int comparaProducator(Produs* p, char s);
