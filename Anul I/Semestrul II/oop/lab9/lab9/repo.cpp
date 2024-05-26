#include "repo.h"
#include <iostream>
#include <sstream>
#include <fstream>

using std::ostream;
using std::stringstream;
using std::ifstream;
using std::ofstream;

void OfertaRepo::store(const Oferta& o)
{
	auto found = find_if(lista_oferte.begin(), lista_oferte.end(), [o](const Oferta& oo) {
		return oo.get_denumire() == o.get_denumire() && oo.get_destinatie() == o.get_destinatie();
		});
	if (found != lista_oferte.end()) {
		throw OfertaRepoException{ "Oferta existenta!" };
	}
	lista_oferte.push_back(o);
}

void OfertaRepo::sterge(const Oferta& o) {
	auto found = find_if(lista_oferte.begin(), lista_oferte.end(), [o](const Oferta& oo) {
		return oo.get_denumire() == o.get_denumire() && oo.get_destinatie() == o.get_destinatie();
		});
	if (found == lista_oferte.end())
		throw OfertaRepoException("Nu exista oferta dorita!");
	auto rez = lista_oferte.erase(found);

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

int OfertaRepo::cauta(const string& denumire_data, const string& destinatie_data) {
	auto found = find_if(lista_oferte.begin(), lista_oferte.end(), [&](const Oferta& oo) {
		return (oo.get_denumire() == denumire_data && oo.get_destinatie() == destinatie_data);
		});

	if (found == lista_oferte.end()) {
		throw OfertaRepoException("Nu exista oferta cautat!");
	}

	int poz = static_cast<int>(std::distance(lista_oferte.begin(), found)); // Ensure poz is of type int

	return poz; // Return poz if it's a valid integer representing the index
}

vector<Oferta>& OfertaRepo::getAll() noexcept {
	return lista_oferte;
}


ostream& operator<<(ostream& out, const OfertaRepoException& ex) {
	out << ex.msg;
	return out;
}

void RepoFile::load_from_file() {
	ifstream in(file_name);
	if (!in.is_open()) {
		throw OfertaRepoException("Nu a fost deschis fisierul!\n");
	}
	while (!in.eof()) {
		string denumire;
		in >> denumire;
		string destinatie;
		in >> destinatie;
		string tip;
		in >> tip;
		float pret;
		in >> pret;
		if (in.eof()) {
			break;
		}
		Oferta o{ denumire.c_str(), destinatie.c_str(), tip.c_str(), pret };
		OfertaRepo::store(o);
	}
	in.close();
}

void RepoFile::write_to_file() {
	ofstream out(file_name);

	if (!out.is_open()) {
		throw OfertaRepoException("Nu se poate deschide fisierul!\n");
	}

	for (auto& p : getAll()) {
		out << p.get_denumire() << " ";
		out << p.get_destinatie() << " ";
		out << p.get_tip() << " ";
		out << p.get_pret();
		out << std::endl;
	}
	out.close();
}