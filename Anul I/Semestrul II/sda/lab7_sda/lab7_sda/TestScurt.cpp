#include "TestScurt.h"
#include <assert.h>
#include <string.h>
#include <iostream>
#include "AB.h"
#include "IteratorAB.h"

void tiparesteABPreordine(AB ab) {
    if (!ab.vid()) {
        cout << ab.element() << " ";
        tiparesteABPreordine(ab.stang());
        tiparesteABPreordine(ab.drept());
    }
}


void testAll() { //apelam fiecare functie sa vedem daca exista
    string ordine[] = { "preordine","postordine","inordine","latime" };
    AB ab;
    assert(ab.vid() == true);
    //adaug niste elemente
    //arborele este
    //       4
    //        \
    //         3
    //        / \
    //       1   2
    AB a1(1), a2(2), a3(3);
    a3.adaugaSubSt(a1);
    a3.adaugaSubDr(a2);
    AB a4(ab, 4, a3);
    assert(a4.element() == 4);
    assert(a4.stang().vid() == true);
    assert(!(a4.drept().vid()) == true);
    assert(a4.drept().element() == 3);
    assert(a4.drept().stang().element() == 1);
    assert(a4.drept().drept().element() == 2);
    for (int i = 0; i < 4; i++) {
        IteratorAB* iab = a4.iterator(ordine[i]);
        iab->prim();
        while (iab->valid()) {
            TElem e = iab->element();
            iab->urmator();
        }
    }
}

    //arborele este
    //       1
    //      /  \
    //     2    3
    //    / \    \
    //   4   5    5
    //    \      /
    //    6     7
    //   /     / \
    //  8     9   10
    //  \    /   /
    //   11 5   12

void test_sterge_aparitii() {
    AB a11(11), a12(12), a10(10), a8(8), a9(9), a5_2(5);
    a8.adaugaSubDr(a11);
    a10.adaugaSubSt(a12);
    a9.adaugaSubSt(a5_2);
    AB a, a6(a8, 6, a), a7(a9, 7, a10), a4(a, 4, a6), a5(a7, 5, a), a5_1(a7, 5, a), a2(a4, 2, a5), a3(a, 3, a5_1), ab(a2, 1, a3);
    assert(ab.eliminaAparitii(3, 5) == 1);
}
