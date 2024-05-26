#include "repo.h"
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void OfertaRepo::store(const Oferta& o)
{
	if (exist(o)) {
		throw OfertaRepoException("Exista deja oferta!");
	}
	else {
		lista_oferte.push_back(o);
	}
}

bool OfertaRepo::exist(const Oferta& o) const {
	for (const auto& of : lista_oferte) {
		if (of.get_denumire() == o.get_denumire() &&
			of.get_destinatie() == o.get_destinatie())
			return true;
	}
	return false;
}

void OfertaRepo::sterge(const Oferta& o) {
	if (exist(o)) {
		auto it = std::find(lista_oferte.begin(), lista_oferte.end(), o);

		if (it != lista_oferte.end())
			lista_oferte.erase(it);
	}
	else
		throw OfertaRepoException("Nu exista oferta dorita!");

}

void OfertaRepo::modifica(const Oferta& o, const string& denumire_noua, const string& destinatie_noua,
	const string& tip_nou, const float pret_nou) {
	int ok = 0;
	for (int i = 0; i < lista_oferte.size(); i++) {
		if (lista_oferte[i].get_denumire() == o.get_denumire() &&
			lista_oferte[i].get_destinatie() == o.get_destinatie() &&
			lista_oferte[i].get_tip() == o.get_tip() &&
			lista_oferte[i].get_pret() == o.get_pret()) {
			lista_oferte[i].set_denumire(denumire_noua);
			lista_oferte[i].set_destinatie(destinatie_noua);
			lista_oferte[i].set_tip(tip_nou);
			lista_oferte[i].set_pret(pret_nou);
			ok = 1;
		}
	}
	if (ok == 0) {
		throw OfertaRepoException("Nu exista oferta dorita!");
	}
}

const Oferta& OfertaRepo::cauta(const string& denumire_data, const string& destinatie_data) const {
	for (const auto& o : lista_oferte) {
		if (o.get_denumire() == denumire_data && o.get_destinatie() == destinatie_data)
			return o;
	}
	throw OfertaRepoException("Nu exista oferta cautat!");
}

const vector<Oferta>& OfertaRepo::getAll() const noexcept {
	return lista_oferte;
}


ostream& operator<<(ostream& out, const OfertaRepoException& ex) {
	out << ex.msg;
	return out;
}