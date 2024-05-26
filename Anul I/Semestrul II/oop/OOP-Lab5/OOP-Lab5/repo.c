#include "repo.h"
#include <assert.h>
#include <string.h>
#include <malloc.h>

MyList* create_list(destroy_fct f) {
	MyList* nou = malloc(sizeof(MyList));

	if (nou == NULL)
		return NULL;

	nou->capacitate = 2;
	nou->lg = 0;
	nou->elems = malloc(sizeof(TElem) * nou->capacitate);
	nou->destructor = f;
	return nou;
}

void destroy(MyList* l) {
	for (int i = 0; i < l->lg; i++)
		l->destructor(l->elems[i]);
	free(l->elems);
	free(l);
}

void set(MyList* l, int index, Produs* new_value) {
	l->elems[index] = new_value;
}


TElem get(MyList* l, int poz) {
	return l->elems[poz];
}


int size(MyList* l) {
	return l->lg;
}


void resize(MyList* l) {
	l->capacitate *= 2;
	TElem* newElem = malloc(l->capacitate * sizeof(TElem));

	if (newElem == NULL) {
		return;
	}

	for (int i = 0; i < l->lg; i++)
		newElem[i] = l->elems[i];

	free(l->elems);
	l->elems = newElem;


}

void add(MyList* l, TElem* el) {
	if (l->lg == l->capacitate)
		resize(l);
	l->elems[l->lg++] = el;
}



void remove_at(MyList* l, int index) {
	l->destructor(l->elems[index]);
	for (int i = index; i < size(l) - 1; ++i) {
		l->elems[i] = l->elems[i + 1];
	}

	l->lg--;
}

MyList* copyList(MyList* l, copy_fct cpy) {
	MyList* rez = create_list(l->destructor);
	for (int i = 0; i < size(l); i++) {
		add(rez, cpy(l->elems[i]));
	}
	return rez;
}

TElem removeLast(MyList* lst) {
	TElem e = lst->elems[lst->lg - 1];
	--lst->lg;
	return e;
}