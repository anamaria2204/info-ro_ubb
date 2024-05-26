#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "domain.h"

Produs* create_produs(int id, char* tip, char* producator, char* model, float pret, int cantitate) {
    Produs* nou = malloc(sizeof(Produs));
    if (nou == NULL)
        return NULL;
    int nrC;

    nrC = (int)strlen(tip) + 1;
    nou->tip = malloc(nrC * sizeof(char));
    if (nou->tip == NULL) {
        free(nou);
        return NULL;
    }
    strcpy_s(nou->tip, nrC, tip);

    nrC = (int)strlen(producator) + 1;
    nou->producator = malloc(nrC * sizeof(char));
    if (nou->producator == NULL) {
        free(nou);
        return NULL;
    }
    strcpy_s(nou->producator, nrC, producator);

    nrC = (int)strlen(model) + 1;
    nou->model = malloc(nrC * sizeof(char));
    if (nou->model == NULL) {
        free(nou);
        return NULL;
    }
    strcpy_s(nou->model, nrC, model);

    nou->id = id;
    nou->pret = pret;
    nou->cantitate = cantitate;
    return nou;
}



void destroy_produs(Produs* p) {

    free(p->tip);
    free(p->model);
    free(p->producator);
    free(p);
}


int validate(int id, char* tip, char* producator, char* model, float pret, int cantitate) {
    if (strlen(tip) == 0)
        return 2;

    if (strlen(model) == 0)
        return 3;

    if (id < 0)
        return 1;

    if (strlen(producator) == 0)
        return 4;

    if (pret < 0)
        return 5;

    if (cantitate < 0)
        return 6;

    return 0;
}
Produs* copieProdus(Produs* p) {
    return create_produs(p->id, p->tip, p->producator, p->model, p->pret, p->cantitate);
}

int comparaPret(Produs* p1, Produs* p2) {
    if (p1->pret > p2->pret)
        return 1;
    else
        return 0;
}

int comparaCantitate(Produs* p1, Produs* p2) {
    if (p1->cantitate > p2->cantitate)
        return 1;
    else
        return 0;
}

int cautaSir(Produs* p, char* sir) {
    if (strstr(p->producator, sir) != NULL)
        return 1;
    else
        return 0;
}

int comparaPretul(Produs* p, float pret) {
    if (p->pret < pret)
        return 1;
    else
        return 0;
}

int comparaCantitatea(Produs* p, int cantitate) {
    if (p->cantitate < cantitate)
        return 1;
    else
        return 0;
}

int produseEgale(Produs* p1, Produs* p2) {
    if (p1->id == p2->id) {
        if (strcmp(p1->tip, p2->tip) == 0) {
            if (strcmp(p1->producator, p2->producator) == 0) {
                if (strcmp(p1->model, p2->model) == 0) {
                    if (p1->pret == p2->pret)
                        return 1;
                }
            }
        }
    }
    return 0;
}

int comparaProducator(Produs* p, char s) {
    if (p->producator[0] == s)
        return 1;
    else
        return 0;
}