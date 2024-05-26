#pragma once
#pragma once
//#ifndef TESTS_H
#define TESTS_H

#include "domain.h"

//test creeare produs
void testCreateProdus();

//Teste adaugare produse
void testAddProduct();

//Test creaza lista
void testCreateList();

//Teste pentru lista
void testIterateList();

//Test copie lista
void testCopyList();

// Test pentru crearea si stergerea unui produs
void testCreateDestroy();

//test pentru creearea unui service
void testCreateSrv();


// Test pentru ad?ugarea unui produs
void test_addProduct();


// Test pentru actualizarea unui produs
void test_updateProduct();

// Test pentru ?tergerea unui produs
void test_stergeProdus();


// Test pentru filtrarea produselor dupa producator
void test_getAllProduct_by_producator();

// Test pentru filtrarea produselor dup? pre?
void test_getAllProduct_by_price();

// Test pentru filtrarea produselor dup? cantitate
void test_getAllProduct_by_quantity();

//test compara pret
void test_compara_pret();

//test compara cantitate
void test_compara_cantitate();

//test sortare produse
void test_sortare_produse();

//test compara egale
void test_compara_egale();


//test compara litera
void test_filtrare_litera();

//test undo
void test_undo();