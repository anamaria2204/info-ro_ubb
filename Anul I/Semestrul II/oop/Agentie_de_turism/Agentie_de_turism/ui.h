#pragma once

#pragma once
#include "service.h"
#include "domeniu.h"
class UI {
	OfertaService& srv;

	//tipareste lista de oferte
	void tipareste(VectorDinamic<Oferta> oferte);

	//tipareste lista de oferte inversata
	void tipareste_invers(VectorDinamic<Oferta> oferte);

public:
	/*
	Citeste datele de la tastatura si adauga Pet
	arunca exceptie daca: nu se poate salva, nu e valid
	*/
	void adaugaOferta();
	UI(OfertaService& srv) :srv{ srv } {
	}
	//nu permitem copierea obiectelor
	UI(const UI& ot) = delete;

	void adauga_oferte();
	void start();
};

void testAll();
void print_meniu();