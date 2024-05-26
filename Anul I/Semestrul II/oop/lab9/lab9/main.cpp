#include "domeniu.h"
#include "teste.h"
#include "ui.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

void mainSec() {
	//testAll();
	//cout << "Teste realizate cu succes!\n";
	///*
	vector<Oferta> vect;
	RepoFile rep_file ("oferte.txt");
	OfertaRepo rep(vect);
	//RepoProb repo(0.67);
	OfertaValidator valid;
	Wishlist list;
	OfertaService serv{ rep_file, valid, list };
	UI ui{ serv };
	ui.adauga_oferte();
	ui.start();
	//*/
}

int main() {

	mainSec();
	if (_CrtDumpMemoryLeaks()) {
		cout << "\nMemory leak\n";
	}
	return 0;
}