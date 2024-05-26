#include "domeniu.h"
#include "teste.h"
#include "ui.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

void mainSec() {
	testAll();
	cout << "Teste realizate cu succes!\n";
	///*
	OfertaRepo rep;
	OfertaValidator valid;
	OfertaService serv{ rep, valid };
	UI ui{ serv };
	ui.start();
	//*/
}

int main() {
	
	mainSec();
	if (_CrtDumpMemoryLeaks()) {
		cout << "\n Memory leak\n";
	}
	return 0;
}