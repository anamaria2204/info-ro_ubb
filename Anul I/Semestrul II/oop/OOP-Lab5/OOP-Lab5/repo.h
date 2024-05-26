#pragma once
#include "domain.h"

typedef void* TElem;
typedef void (*destroy_fct)(TElem);
typedef TElem(*copy_fct)(TElem);

typedef struct {
	TElem* elems;
	int capacitate;
	int lg;
	destroy_fct destructor;
}MyList;

/*
 Creeaza o noua lista de tip MyList
 @return un element de tip MyList
 */
MyList* create_list(destroy_fct f);

/*
 Destroy list
 @param l - lista
*/
void destroy(MyList* l);

/*
* Redimensioneaza spatiul de memorare
*/
void resize(MyList* l);

/*
 Inlocuieste produsul de pe poz index din lista cu un nou produs
 @param l		 - lista
 @param index     - indexul prodului de actualizat
 @param new_value - produsul nou
*/
void set(MyList* l, int index, Produs* new_value);

/*
  Ia elementul de pe o poz din lista
  @param l   - lista
  @param poz - pozitia elementului, care trebuie sa fie valida
  @return element on the given position
*/
TElem get(MyList* l, int poz);

/*
  Returneza dimensiunea liste
  @param l -lista
  @return numarul de elemente din lista
*/
int size(MyList* l);

/*
  Adauga un element in lista
  @param l  - lista
  @param el - elementul de adaugat
*/
void add(MyList* l, TElem* el);

/*
  Make a shallow copy of the list
  return Mylist containing the same elements as l
*/
MyList* copyList(MyList* l, copy_fct cpy);


/**
  Sterge elementul de pe poz index din lista
  @param l     - lista
  @param index - indexul elementului de sters
*/
void remove_at(MyList* l, int index);

/**
 * Extrage ultimul element din lista
 * @param lst lista din care se extrage
 * @return Elementul extras
 */
TElem removeLast(MyList* lst);

/**
 * Functia este facuta ca sa functioneze adaugara la elemente de tip lista
 */
void inc_lst(MyList* lst);