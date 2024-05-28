#include "wishlist.h"
#include <sstream>
#include <iostream>
#include <random>

using std::ostream;
using std::stringstream;


void Wishlist::wishlist_gol() noexcept {
	this->list.clear();
}

const vector<Oferta>& Wishlist::get_oferta() {
	return this->list;
}

void Wishlist::adauga_wishlist(const Oferta& oferta) {
	const string& denumire = oferta.get_denumire();
	const string& destinatie = oferta.get_destinatie();

	if (cauta_wishlist(denumire, destinatie) != -1) {
		throw OfertaWishlistException("Oferta deja exista!");
	}
	else {
		this->list.push_back(oferta);
	}
}

int Wishlist::cauta_wishlist(const string& denumire, const string& destinatie) {
	auto iterator = find_if(this->list.begin(),
		this->list.end(), [denumire, destinatie](const Oferta& oferta) noexcept {
			if (oferta.get_denumire() == denumire && oferta.get_destinatie() == destinatie)
				return true;
			return false;
		});
	for (int i = 0; i < list.size(); i++) {
		if (list[i].get_denumire() == denumire &&
			list[i].get_destinatie() == destinatie)
			return i;
	}
	return -1;
}

void Wishlist::genereza_wishlist(int nr_oferte, const vector<Oferta>& of) {
	if (nr_oferte > of.size()) {
		throw OfertaWishlistException("Nu exista suficiente oferte in memorie!");
	}
	std::random_device rd;
	std::mt19937 gen(rd());

	wishlist_gol();
	auto to_list = of;
	shuffle(to_list.begin(), to_list.end(), gen);

	while (nr_oferte && !to_list.empty()) {
		adauga_wishlist(to_list.back());
		to_list.pop_back();
		nr_oferte--;
	}
}

void Wishlist::exporta_wishlist(const string& nume_fisier) {
	string filename = nume_fisier;
	auto poz = filename.find_first_of(".");

	if (poz < filename.size()) {
		auto file_extension = nume_fisier.substr(poz);
		if (file_extension != ".html") {
			filename = filename + ".html";
		}
	}
	else {
		filename += ".html";
	}
	std::ofstream fout(filename);
	fout << "<html>\n"
		"<body>\n"
		"<head>\n"
		"	<h3 style=\"serif; \">Wishlist oferte</h3>\n"
		"	</head>\n"
		"<style>\n"
		"	p {\n"
		"		color: #D7BDE2 ;\n"
		"		border: 1px solid black; }\n"
		"	table,th,td{\n"
		"		border: 1px solid black;\n"
		"       font-size: 20px;\n" // Set the font size to 20px
		"	}\n"
		"	th{\n"
		"		color: black;\n"
		"	}\n"
		"	body{\n"
		"   }\n"
		"</style>\n";

	fout << "<table>\n"
		"\n"
		"		<th>Denumire</th>\n"
		"		<th>Destinatie</th>\n"
		"       <th>Tip</th>\n"
		"		<th>Pret</th>\n";

	for (const Oferta& oferta : get_oferta()) {
		fout << "<tr>\n";
		fout << "<th>" << oferta.get_denumire() << "</th>\n"
			<< "<th>" << oferta.get_destinatie() << "</th>\n"
			<< "<th>" << oferta.get_tip() << "</th>\n"
			<< "<th>" << oferta.get_pret() << "</th>\n"
			<< "</tr>\n";
	}

	fout << "</table>\n"
		"\n"
		"\n"
		"</body>\n"
		"</html>";
}