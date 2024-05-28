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
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, o));
}

void OfertaService::undo() {
	if (undoActions.empty()) {
		throw OfertaServiceException{ "Nu mai exista operatii!\n" };
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

OfertaService::~OfertaService() {

}

void OfertaService::stergere(const int pozitie) {
	const auto& oferte = repo.getAll();
	int ok = 0;
	for (int i = 0; i < oferte.size(); i++) {
		if (i == pozitie) {
			Oferta copie = oferte[i];
			repo.sterge(oferte[i]);
			undoActions.push_back(std::make_unique<UndoSterge>(repo, copie));
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
			Oferta of_veche = oferte[i];
			repo.modifica(oferte[i], denumire_noua, destinatie_noua, tip_nou, pret_nou);
			undoActions.push_back(std::make_unique<UndoModifica>(repo, oferte[i],
				of_veche.get_denumire(), of_veche.get_destinatie(), of_veche.get_tip(),
				of_veche.get_pret()));
			ok = 1;
		}
	}
	if (ok == 0)
		throw(OfertaServiceException("Oferta dorita nu exista in lista ofertelor existente"));

}

const Oferta& OfertaService::cautare(const string& denumire_data,
	const string& destinatie_data) const {
	int poz = repo.cauta(denumire_data, destinatie_data);
	if (poz != -1) {
		return repo.getAll()[poz];
	}
	else {
		throw(OfertaServiceException("Oferta cautata nu exista!\n"));
	}
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

int OfertaService::nr_oferte_in_cos() {
	return int(lista.get_oferta().size());
}

void OfertaService::adauga_in_cos(const string& denumire, const string& destinatie) {
	try {
		int poz = repo.cauta(denumire, destinatie);
		if (poz != -1)
			lista.adauga_wishlist(repo.getAll()[poz]);
	}
	catch (OfertaRepoException& ex) {
		std::cerr << "Error: " << ex.get_mesaj() << "\n";
		// Rethrow the exception if necessary, or handle it accordingly
		throw; // Rethrow the exception to propagate it up the call stack
	}
}

void OfertaService::sterge_oferte_cos() {
	lista.wishlist_gol();
}

void OfertaService::genereaza_cos(int nr_oferte) {
	lista.genereza_wishlist(nr_oferte, repo.getAll());
}

void OfertaService::exporta_cos(const string& nume) {
	lista.exporta_wishlist(nume);
}

map<string, DTO> OfertaService::raport() noexcept {
	map<string, DTO> rap;
	auto oferte = repo.getAll();

	for (const auto& oferta : oferte) {
		DTO denumire(oferta.get_tip());
		rap[oferta.get_tip()] = denumire;
	}

	for (const auto& oferta : oferte) {
		int nr = rap[oferta.get_tip()].get_count() + 1;
		DTO valoare(oferta.get_tip(), nr);
		rap[oferta.get_tip()] = valoare;
	}
	return rap;
}