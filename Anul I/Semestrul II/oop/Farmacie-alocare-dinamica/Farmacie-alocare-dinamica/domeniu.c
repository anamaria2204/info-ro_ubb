#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "domeniu.h"

Medicament* creaza(int cod, char* nume, int concentratie, int cantitate) {
    int lung_nume;
    Medicament* rez = malloc(sizeof(Medicament));

    if (rez == NULL) {
        return NULL;
    }

    rez->cod = cod;

    lung_nume = (int)strlen(nume) + 1;
    rez->nume = malloc(lung_nume * sizeof(char));

    if (rez->nume == NULL) {
        free(rez);
        return NULL;
    }

    strcpy_s(rez->nume, lung_nume, nume);

    rez->concentratie = concentratie;
    rez->cantitate = cantitate;

    return rez;
}

void distruge(Medicament* m) {

    free(m->nume);
    free(m);
}

int valideaza(Medicament* m) {

    if (m->cod <= 0) {
        return 1;
    }

    if (strlen(m->nume) == 0) {
        return 2;
    }

    if (m->concentratie < 0) {
        return 3;
    }

    if (m->cantitate < 0) {
        return 4;
    }

    return 0;
}
int egalCod(Medicament* m1, Medicament* m2) {
    if (m1->cod == m2->cod) {
        return 1;
    }
    return 0;
}
int egalMedicamente(Medicament* m1, Medicament* m2) {
    if (m1->cod == m2->cod && strcmp(m1->nume, m2->nume) == 0 &&
        m1->concentratie == m2->concentratie) {
        return 1;
    }
    return 0;

}

int egalModifica(Medicament* m1, Medicament* m2) {
    if (m1->cod == m2->cod && m1->cantitate > 0) {
        return 1;
    }
    return 0;

}

void adaugaCantitate(Medicament* m1, Medicament* m2) {
    m1->cantitate += m2->cantitate;

}

int returnCod(Medicament* m) {
    return m->cod;
}

int verifStoc(Medicament* m) {
    if (m->cantitate > 0) {
        return 1;
    }
    return 0;
}

void stergeCantitate(Medicament* m) {
    m->cantitate = 0;
}

int compNume(Medicament* m1, Medicament* m2) {
    return strcmp(m1->nume, m2->nume);
}

int compCantitate(Medicament* m1, Medicament* m2) {
    if (m1->cantitate > m2->cantitate) {
        return 1;
    }
    return 0;
}

int filtreazaNume(Medicament* m, char nume) {
    if (m->nume[0] == nume) {
        return 1;
    }
    return 0;
}

int filtrezaCantitate(Medicament* m, int cantitate) {
    if (m->cantitate > 0 && m->cantitate < cantitate) {
        return 1;
    }
    return 0;
}

Medicament* copiazaMedicamente(Medicament* m) {
    return creaza(m->cod, m->nume, m->concentratie, m->cantitate);

}