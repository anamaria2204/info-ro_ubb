#include "domeniu.h"
#include <cassert>
#include <string.h>

const string Oferta::get_denumire() const {
	return denumire;
}

const string Oferta::get_destinatie() const {
	return destinatie;
}

const string Oferta::get_tip() const {
	return tip;
}

const float Oferta::get_pret() const {
	return pret;
}

void Oferta::set_denumire(const string valoare) {
	denumire = valoare;
}

void Oferta::set_destinatie(const string valoare) {
	destinatie = valoare;
}

void Oferta::set_tip(const string valoare) {
	tip = valoare;
}

void Oferta::set_pret(const float valoare) noexcept {
	pret = valoare;
}

string Oferta::to_string_print() const {
	return "Denumire:" + this->denumire + "; Destinatie: " + this->destinatie +
		"; Tip: " + this->tip + "; Pret: " + std::to_string(this->pret) + ".";
}

bool comp_denumire(const Oferta& o1, const Oferta& o2) {
	return o1.get_denumire() < o2.get_denumire();
}

bool comp_destinatie(const Oferta& o1, const Oferta& o2) {
	return o1.get_destinatie() < o2.get_destinatie();
}
