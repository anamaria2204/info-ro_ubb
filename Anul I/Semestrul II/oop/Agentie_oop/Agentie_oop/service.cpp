#include <functional>
#include <algorithm>
#include <assert.h>
#include "service.h"
#include <sstream>

using std::ostream;
using std::stringstream;


void OfertaService::adauga(const string& denumire, const string& destinatie, const string& tip, float pret) {
	Oferta o{ denumire, destinatie, tip, pret };
	val.valideaza(o);
	repo.store(o);
}

void OfertaService::stergere(const int pozitie) {
	const auto& oferte = repo.getAll();
	int ok = 0;
	for (int i = 0; i < oferte.size(); i++) {
		if (i == pozitie) {
			repo.sterge(oferte[i]);
			ok = 1;
		}
	}
	if (ok == 0)
		throw(OfertaServiceException("Oferta dorita nu exista in lista ofertelor existente"));

}

void OfertaService::modificare(int pozitie, const string& denumire_noua, const string& destinatie_noua,
	const string& tip_nou, const float pret_nou) {
	const auto& oferte = repo.getAll();
	int ok = 0;
	for (int i = 0; i < oferte.size(); i++) {
		if (i == pozitie) {
			repo.modifica(oferte[i], denumire_noua, destinatie_noua, tip_nou, pret_nou);
			ok = 1;
		}
	}
	if (ok == 0)
		throw(OfertaServiceException("Oferta dorita nu exista in lista ofertelor existente"));

}

const Oferta& OfertaService::cautare(const string& denumire_data,
	const string& destinatie_data) const {
	return repo.cauta(denumire_data, destinatie_data);
}

vector<Oferta> OfertaService::filtreaza(function<bool(const Oferta&)> fct) {
	vector<Oferta> rez;
	for (const auto& pet : repo.getAll()) {
		if (fct(pet)) {
			rez.push_back(pet);
		}
	}
	return rez;
}

vector<Oferta> OfertaService::filtreaza_destinatie(string destinatie) {
	return filtreaza([destinatie](const Oferta& o) {
		return o.get_destinatie() == destinatie;
		});
}

vector<Oferta> OfertaService::filtreaza_pret(float pret) {
	return filtreaza([pret](const Oferta& o) {
		return o.get_pret() > pret;
		});
}

vector<Oferta> OfertaService::generalSort(bool (*maiMicF)(const Oferta&, const Oferta&)) {
	vector<Oferta> copie{ repo.getAll() };
	for (size_t i = 0; i < copie.size(); i++) {
		for (size_t j = i + 1; j < copie.size(); j++) {
			if (maiMicF(copie[i], copie[j]) == 1) {
				Oferta aux = copie[i];
				copie[i] = copie[j];
				copie[j] = aux;
			}
		}
	}
	return copie;
}

vector<Oferta> OfertaService::sorteaza_denumire() {
	auto copie = repo.getAll();
	std::sort(copie.begin(), copie.end(), comp_denumire);
	return copie;
}

vector<Oferta> OfertaService::sorteaza_destinatie() {
	auto copie = repo.getAll();
	std::sort(copie.begin(), copie.end(), comp_destinatie);
	return copie;
}

vector<Oferta> OfertaService::sorteaza_tip_pret() {
	return generalSort([](const Oferta& o1, const Oferta& o2) {
		if (o1.get_tip() == o2.get_tip()) {
			return o1.get_pret() > o2.get_pret();
		}
		return o1.get_tip() > o2.get_tip();
		});
}

ostream& operator<<(ostream& out, const OfertaServiceException& ex) {
	out << ex.msg;
	return out;
}
