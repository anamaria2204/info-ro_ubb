#pragma once
#include "repo.h"
#include "service.h"

/*
* ruleaza toate testele
*/
void testAll();
/*
* adauga un produs
*/
void readProdus(Srv srvproduse);

/*
sterge un produs
*/
void deteleProd(Srv srvprod);

/*
modifica un produs
*/
void modifyProd(Srv srvprod);


/*
* printeaza produsele
*/
void printAllProduct(MyList* l);

/*
filtreaza
*/
void filterProd(MyList* l);

/*
* undo 
*/

void do_undo(Srv* srv);

/**
* interfata cu utilizatorul
*/
void run();