#pragma once

#pragma once
#include "service.h"
#include "domeniu.h"
class UI {
	OfertaService& srv;
	/*
	Citeste datele de la tastatura si adauga Pet
	arunca exceptie daca: nu se poate salva, nu e valid
	*/
	void adaugaOferta();

	/*
	Tipareste o lista de animale la consola
	*/
	void tipareste(const vector<Oferta>& oferte);
public:
	UI(OfertaService& srv) :srv{ srv } {
	}
	//nu permitem copierea obiectelor
	UI(const UI& ot) = delete;

	void start();

	void adauga_oferte();
};

void testAll();
void print_meniu();