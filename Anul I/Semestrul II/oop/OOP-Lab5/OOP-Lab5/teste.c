#include <assert.h>
#include <string.h>
#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <stdlib.h>
#include <stdio.h>

void testCreateProdus() {
    Produs* p = create_produs(1, "a", "b", "c", 20, 10);
    assert(p->id == 1);
    assert(strcmp(p->tip, "a") == 0);
    assert(strcmp(p->producator, "b") == 0);
    assert(strcmp(p->model, "c") == 0);
    assert(p->pret == 20);
    assert(p->cantitate == 10);
    destroy_produs(p);
}

void testCreateList() {
    MyList* l = create_list(&destroy_produs);
    assert(l != NULL);
    assert(l->capacitate == 2);
    assert(l->lg == 0);
    destroy(l);

}

void testIterateList() {
    MyList* l = create_list(&destroy_produs);
    Produs* p1, * p2;
    p1 = create_produs(1, "a", "b", "c", 20, 10);
    p2 = create_produs(2, "a2", "b2", "c2", 40, 20);

    add(l, (TElem*)p1);
    add(l, (TElem*)p2);

    assert(size(l) == 2);
    Produs* p = get(l, 0);

    assert(strcmp(p->tip, "a") == 0);
    p = get(l, 1);
    assert(strcmp(p->producator, "b2") == 0);
    destroy(l);
}

void testCopyList() {
    MyList* l = create_list(destroy_produs);
    Produs* p1, * p2;
    p1 = create_produs(1, "a", "b", "c", 20, 10);
    p2 = create_produs(2, "a2", "b2", "c2", 40, 20);

    add(l, (TElem*)p1);
    add(l, (TElem*)p2);
    MyList* copie = copyList(l, copieProdus);
    assert(size(copie) == 2);

    Produs* p = get(copie, 0);
    assert(strcmp(p->tip, "a") == 0);

    destroy(l);
    destroy(copie);
}

void testCreateDestroy() {
    Produs* p = create_produs(1, "laptop", "asus", "tuf15", 100.0, 10);
    assert(strcmp(p->tip, "laptop") == 0);
    assert(strcmp(p->producator, "asus") == 0);
    assert(strcmp(p->model, "tuf15") == 0);
    assert(p->pret == 100.0);
    assert(p->cantitate == 10);
    assert(p->id == 1);

    destroy_produs(p);
}

void testAddProduct() {
    Srv srvtest = createService(&destroy_produs);

    int error = addProduct(&srvtest, -3, "a", "b", "c", 20, 10);
    assert(error != 0);
    assert(srvtest.actual->lg == 0);

    error = addProduct(&srvtest, 1, "", "b", "c", 20, 10);
    assert(error != 0);
    assert(srvtest.actual->lg == 0);

    error = addProduct(&srvtest, 2, "a", "", "c", 20, 10);
    assert(error != 0);
    assert(srvtest.actual->lg == 0);


    error = addProduct(&srvtest, 3, "a", "b", "", 20, 10);
    assert(error != 0);
    assert(srvtest.actual->lg == 0);

    error = addProduct(&srvtest, 3, "a", "b", "c", -20, 10);
    assert(error != 0);
    assert(srvtest.actual->lg == 0);

    error = addProduct(&srvtest, 3, "a", "b", "c", 20, -10);
    assert(error != 0);
    assert(srvtest.actual->lg == 0);

    addProduct(&srvtest, 1, "a", "b", "c", 20, 10);
    addProduct(&srvtest, 2, "a2", "b2", "c2", 40, 20);

    error = addProduct(&srvtest, 2, "e", "e", "e", 20, 10);
    assert(error != 0);
    assert(srvtest.actual->lg == 2);

    destroySrv(&srvtest);
}


void testCreateSrv() {
    Srv srvtest;
    srvtest = createService();

    assert(srvtest.actual->lg == 0);
    assert(srvtest.actual->capacitate == 2);

    destroySrv(&srvtest);

}

void test_addProduct() {
    Srv srvtest = createService();

    assert(srvtest.actual->lg == 0);

    assert(addProduct(&srvtest, 1, "Laptop", "Dell", "Inspiron", 2500.0, 10) == 0);
    assert(srvtest.actual->lg == 1);

    assert(addProduct(&srvtest, 1, "Laptop", "Dell", "Inspiron", 2500.0, 5) == 0);
    assert(srvtest.actual->lg == 1);


    destroySrv(&srvtest);
}

void test_updateProduct() {
    Srv srvtest = createService();
    addProduct(&srvtest, 1, "Laptop", "Dell", "Inspiron", 2500.0, 10);
    addProduct(&srvtest, 2, "Telefon", "Samsung", "Galaxy S10", 3000.0, 8);

    assert(updateProduct(&srvtest, 1, 2700.0, 12) == 1);
    assert(updateProduct(&srvtest, 3, 2700.0, 12) == 0);
    destroySrv(&srvtest);
}

void test_stergeProdus() {
    Srv srvtest = createService();
    addProduct(&srvtest, 1, "Laptop", "Dell", "Inspiron", 2500.0, 10);
    addProduct(&srvtest, 2, "Telefon", "Samsung", "Galaxy S10", 3000.0, 8);

    assert(stergeProdus(&srvtest, 1) == 1);
    assert(srvtest.actual->lg == 1);
    assert(stergeProdus(&srvtest, 3) == 0);
    destroySrv(&srvtest);
}

void test_getAllProduct_by_producator() {
    Srv service = createService();

    addProduct(&service, 1, "Laptop", "Dell", "Inspiron", 2500.0, 10);
    addProduct(&service, 2, "Telefon", "Samsung", "Galaxy S10", 3000.0, 8);
    addProduct(&service, 3, "laptop", "lenovo", "yoga", 75, 3);

    MyList* filtered = getAllProduct(service.actual, "Dell", (cauta_sir)cautaSir);
    assert(size(filtered) == 1);
    Produs* p = get(filtered, 0);
    assert(strcmp(p->producator, "Dell") == 0);

    destroy(filtered);
    destroySrv(&service);
}

void test_getAllProduct_by_price() {
    Srv service = createService();

    addProduct(&service, 1, "Laptop", "Dell", "Inspiron", 2500.0, 10);
    addProduct(&service, 2, "Telefon", "Samsung", "Galaxy S10", 3000.0, 8);
    addProduct(&service, 3, "laptop", "lenovo", "yoga", 75, 3);

    MyList* filtered = getAllProductPret(service.actual, 2500.0, (compara_pret)comparaPretul);
    assert(size(filtered) == 1);
    Produs* p = get(filtered, 0);
    assert(p->pret == 75);

    destroy(filtered);
    destroySrv(&service);
}

void test_getAllProduct_by_quantity() {
    Srv service = createService();

    addProduct(&service, 1, "Laptop", "Dell", "Inspiron", 2500.0, 10);
    addProduct(&service, 2, "Telefon", "Samsung", "Galaxy S10", 3000.0, 8);
    addProduct(&service, 3, "laptop", "lenovo", "yoga", 75, 3);

    MyList* filtered = getAllProductbyquantite(service.actual, 8, (compara_cantitate)comparaCantitatea);
    assert(size(filtered) == 1);
    Produs* p = get(filtered, 0);
    assert(p->cantitate == 3);

    destroy(filtered);
    destroySrv(&service);
}


void test_compara_pret() {
    Produs* p1 = create_produs(1, "laptop", "asus", "tuf15", 100.0, 10);
    Produs* p2 = create_produs(1, "laptop", "lenovo", "yoga", 300.0, 20);
    assert(comparaPret(p1, p2) == 0);
    assert(comparaPret(p2, p1) == 1);
    destroy_produs(p1);
    destroy_produs(p2);
}

void test_compara_cantitate() {
    Produs* p1 = create_produs(1, "laptop", "asus", "tuf15", 100.0, 30);
    Produs* p2 = create_produs(1, "laptop", "lenovo", "yoga", 300.0, 20);
    assert(comparaCantitate(p1, p2) == 1);
    assert(comparaCantitate(p2, p1) == 0);
    destroy_produs(p1);
    destroy_produs(p2);
}

void test_sortare_produse() {
    Srv service = createService();

    addProduct(&service, 1, "camera", "polaroid", "10", 100, 5);
    addProduct(&service, 2, "tableta", "samsung", "tab9", 50, 10);
    addProduct(&service, 3, "laptop", "lenovo", "yoga", 75, 3);

    MyList* sortate = sortare(service.actual, 1, (sorteaza)comparaCantitate, (sorteaza)comparaPret);
    assert(sortate->lg == 3);
    assert(((Produs*)sortate->elems[0])->id == 3);
    assert(((Produs*)sortate->elems[1])->id == 1);
    assert(((Produs*)sortate->elems[2])->id == 2);

    MyList* sortatedesc = sortare(service.actual, 0, (sorteaza)comparaCantitate, (sorteaza)comparaPret);
    assert(sortatedesc->lg == 3);
    assert(((Produs*)sortatedesc->elems[0])->id == 2);
    assert(((Produs*)sortatedesc->elems[1])->id == 1);
    assert(((Produs*)sortatedesc->elems[2])->id == 3);

    destroy(sortatedesc);
    destroy(sortate);
    destroySrv(&service);
}

void test_compara_egale() {
    Produs* p1 = create_produs(1, "laptop", "asus", "tuf15", 100.0, 10);
    Produs* p2 = create_produs(1, "laptop", "lenovo", "yoga", 300.0, 20);
    assert(produseEgale(p1, p2) == 0);
    Produs* p3 = create_produs(1, "laptop", "asus", "tuf15", 100.0, 100);
    assert(produseEgale(p1, p3) == 1);
    destroy_produs(p3);
    destroy_produs(p2);
    destroy_produs(p1);

}

void test_filtrare_litera() {
    Srv service = createService();

    addProduct(&service, 1, "Laptop", "Dell", "Inspiron", 2500.0, 10);
    addProduct(&service, 2, "Telefon", "Samsung", "Galaxy S10", 3000.0, 8);
    addProduct(&service, 3, "laptop", "lenovo", "yoga", 75, 3);

    MyList* filtered = getAllProductbyproducator(service.actual, 'D', (compara_litera)comparaProducator);
    assert(size(filtered) == 1);
    Produs* p = get(filtered, 0);
    assert(p->id == 1);

    destroy(filtered);
    destroySrv(&service);
}


void test_undo() {
    Srv service = createService();

    addProduct(&service, 1, "camera", "polaroid", "10", 100, 5);
    addProduct(&service, 2, "tableta", "samsung", "tab9", 50, 10);
    addProduct(&service, 3, "laptop", "lenovo", "yoga", 75, 3);
    
    assert(undo(&service) == 1);
    assert(service.actual->lg == 2);
    assert(service.undo->lg == 2);
    assert(undo(&service) == 1);
    assert(undo(&service) == 1);
    assert(undo(&service) == 0);

    addProduct(&service, 1, "camera", "polaroid", "10", 100, 5);
    addProduct(&service, 2, "tableta", "samsung", "tab9", 50, 10);
    addProduct(&service, 3, "laptop", "lenovo", "yoga", 75, 3);
    stergeProdus(&service, 1);
    assert(undo(&service) == 1);
    
    updateProduct(&service, 2, 200, 80);
    assert(undo(&service) == 1);

    destroySrv(&service);
}
