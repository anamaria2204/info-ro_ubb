#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "service.h"
#include "repo.h"
#include "domeniu.h"
#include "teste.h"

void testAll() {
	testCreazaMedicament();
	testAdaugaCantitate();
	testCompCantitate();
	testCompNume();
	testDistrugeMedicament();
	testEgalCod();
	testEgalMedicamente();
	testEgalModify();
	testFiltreazaCantitate();
	testFiltreazaNume();
	testReturnCod();
	testStergeCantitate();
	testValideazaMedicament();
	testVerifStoc();


	//test repo
	testCreazaGol();
	testDistruge();
	testExtinde();
	testAdauga();
	testModifica();
	testStergeStoc();
	testCopieLista();

	//test service
	testAdaugaMedicament();
	testModificaMedicament();
	testStergeMedicament();
	testGetAllMedicamente();
	testSort();
	testCopieListaCantitate();
	testCopieListaNume();
}