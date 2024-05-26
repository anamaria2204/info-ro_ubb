#pragma once
#pragma once

#include "repo.h"

typedef int(*sorteaza)(TElem m1, TElem m2);
typedef int(*cauta_sir)(TElem p, char* sir);
typedef int(*compara_pret)(TElem p, float pret);
typedef int(*compara_cantitate)(TElem p, int cantitate);
typedef int(*compara_litera)(TElem p, char litera);

typedef struct {
	MyList* actual;
	MyList* undo;
}Srv;

/*
* Creeaza un service pentru produse
*/
Srv createService();

/*
* Destrucor pentru service
* @param srvprod service-ul de distrus
*/
void destroySrv(Srv* srvprod);

/*
Add a product to the store
*/
int addProduct(Srv* l, int id, char* tip, char* producator, char* model, float pret, int cantitate);

/*
  Filter products in the store
  typeSubstring - cstring
  return all products where typeSubstring is a substring of the type
*/
MyList* getAllProduct(MyList* l, char* typeSubstring, cauta_sir);

/*
Returneaza o lista cu produsele filtrate dupa un anummit pret
@param l -lista
@param pret - pretul dupa care se filtreaza
@return noua lista filtrata
*/

MyList* getAllProductPret(MyList* l, float pret, compara_pret);


/*
Returneaza o lista cu produsele filtrate dupa o anumita cantitate
@param l -lista
@param pret - cantitatea dupa care se filtreaza
@return noua lista filtrata
*/
MyList* getAllProductbyquantite(MyList* l, int cantitate, compara_cantitate);

/*
Sterge un produs dupa id
@param id - id produsului de sters
@param l - lista
@return 1 - daca stergerea a fost efectuata
@retrun 0 -daca stergerea nu a putut fi efectuata
*/
int stergeProdus(Srv* l, int id);

/*
Actualizeaza pretul si/sau cantitatea unui produs din lista dupa id
@param l -lista
@param id - id produsului de actualizat
@param new_price - noul pret al produsului
@param new_quantity - noua cantitate a produsului
@return 1 - daca actualizarea a fost efectuata
@retrun 0 -daca actualizarea nu a putut fi efectuata
*/
int updateProduct(Srv* l, int id, float new_price, int new_quantity);


/*
Functia sorteaza crescator/descrescator produsele din magazin
@param list - lista de produse
@param crescator - indice ce indica sortarea cresc, desc
@ functiile de sortare dupa pret si cantitate
@return - lista sortata
*/

MyList* sortare(MyList* list, int crescator, sorteaza cmp1, sorteaza cmp2);

/**
 * Realizeaza un undo al ultimei operatii
 * @param ms service-ul de sters
 * @return 0 sau 1 in functie de reusita operatiei
 */
int undo(Srv* srv);

/*
Returneaza o lista cu produsele filtrate dupa o anumita cantitate
@param l -lista
@param pret - cantitatea dupa care se filtreaza
@return noua lista filtrata
*/
MyList* getAllProductbyproducator(MyList* l, char litera, compara_litera);