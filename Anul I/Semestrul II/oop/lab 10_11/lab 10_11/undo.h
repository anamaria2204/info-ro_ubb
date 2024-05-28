#pragma once

#include "domeniu.h"
#include "repo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;

	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Oferta oferta_adaugata;
	OfertaRepo& rep;

public:
	UndoAdauga(OfertaRepo& rep, const Oferta& o) : rep{ rep }, oferta_adaugata{ o } {};

	void doUndo() override {
		rep.sterge(oferta_adaugata);
	}
};

class UndoSterge : public ActiuneUndo {
	Oferta oferta_stearsa;
	OfertaRepo& rep;

public:
	UndoSterge(OfertaRepo& rep, const Oferta& o) : rep{ rep }, oferta_stearsa{ o } {};

	void doUndo() override {
		rep.store(oferta_stearsa);
	}
};

class UndoModifica : public ActiuneUndo {
	Oferta oferta_modificata;
	OfertaRepo& rep;
	string denumire;
	string destinatie;
	string tip;
	float pret;

public:
	UndoModifica(OfertaRepo& rep, const Oferta& o, const string& denumire,
		const string& destinatie, const string& tip, float pret) : rep{ rep },
		oferta_modificata{ o }, denumire{ denumire }, destinatie{ destinatie },
		tip{ tip }, pret{ pret } {};

	void doUndo() override {
		rep.modifica(oferta_modificata, denumire, destinatie, tip, pret);
	}
};
