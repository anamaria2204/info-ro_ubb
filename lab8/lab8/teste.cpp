#include "teste.h"
#include "domeniu.h"
#include "repo.h"
#include "assert.h"
#include "validator.h"
#include "service.h"
#include <sstream>
#include "wishlist.h"

void test_domeniu() {
	Oferta o{ "calatorie", "Maldive", "sejur", 2000 };
	assert(o.get_denumire() == "calatorie");
	assert(o.get_destinatie() == "Maldive");
	assert(o.get_tip() == "sejur");
	assert(o.get_pret() == 2000);
	o.set_denumire("vacanta");
	assert(o.get_denumire() == "vacanta");
	o.set_destinatie("Mamaia");
	assert(o.get_destinatie() == "Mamaia");
	o.set_tip("voiaj");
	assert(o.get_tip() == "voiaj");
	o.set_pret(1500);
	assert(o.get_pret() == 1500);
}

void test_cmp_denumire() {
	Oferta o1{ "calatorie", "Maldive", "sejur", 2000 };
	Oferta o2{ "vacanta", "Mamaia", "mare", 1500 };
	assert(comp_denumire(o1, o2) == 1);
	assert(comp_denumire(o2, o1) == 0);
}

void test_cmp_destinatie() {
	Oferta o1{ "calatorie", "Maldive", "sejur", 2000 };
	Oferta o2{ "vacanta", "Mamaia", "mare", 1500 };
	assert(comp_destinatie(o1, o2) == 1);
	assert(comp_destinatie(o2, o1) == 0);
}


void test_validator() {
	Oferta o{ "", "", "", -2000 };
	OfertaValidator v;
	try {
		v.valideaza(o);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("vida") >= 0);
	}
}


void test_adauga_repo() {
	OfertaRepo repo;
	repo.store(Oferta{ "calatorie", "Maldive", "sejur", 2000 });

	assert(repo.getAll().size() == 1);
	try {
		repo.store(Oferta{ "calatorie", "Maldive", "vacanta", 2000 });
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}
	assert(repo.getAll().size() == 1);

}

void test_sterge_repo() {
	OfertaRepo repo;
	repo.store(Oferta{ "calatorie", "Maldive", "sejur", 2000 });
	assert(repo.getAll().size() == 1);
	repo.sterge(Oferta{ "calatorie", "Maldive", "sejur", 2000 });
	assert(repo.getAll().size() == 0);
	try {
		repo.sterge(Oferta{ "calatorie", "Maldive", "vacanta", 2000 });
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}
}

void test_modifica_repo() {
	OfertaRepo repo;
	repo.store(Oferta{ "calatorie", "Maldive", "sejur", 2000 });
	repo.store(Oferta{ "vacanta", "Timisoara", "sejur", 1200 });
	assert(repo.getAll().size() == 2);
	Oferta o{ "vacanta", "Timisoara", "sejur", 1200 };
	repo.modifica(o, "calatorie", "Sibiu", "vacanta", 1000);
	assert(repo.getAll()[1].get_denumire() == "calatorie");
	try {
		repo.modifica(o, "calatorie", "Sibiu", "vacanta", 1000);
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}
}

void test_cauta_repo() {
	OfertaRepo repo;
	repo.store(Oferta{ "calatorie", "Maldive", "sejur", 2000 });
	repo.store(Oferta{ "vacanta", "Timisoara", "sejur", 1200 });
	assert(repo.getAll().size() == 2);
	Oferta o1{ "vacanta", "Timisoara", "sejur", 1200 };
	assert(repo.cauta("vacanta", "Timisoara") == o1);
	try {
		repo.cauta("vacanta", "Maldive");
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}

}

void test_adauga_service() {
	OfertaRepo rep;
	OfertaValidator val;
	Wishlist list;
	OfertaService ctr{ rep, val, list };
	ctr.adauga("calatorie", "Maldive", "vacanta", 2000);
	assert(ctr.getAll().size() == 1);

	//adaug ceva invalid
	try {
		ctr.adauga("", "", "", -2000);
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	try {
		ctr.adauga("calatorie", "Maldive", "vacanta", 2000);
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}

}

void test_sterge_service() {
	OfertaRepo rep;
	OfertaValidator val;
	Wishlist list;
	OfertaService ctr{ rep, val, list };
	ctr.adauga("calatorie", "Maldive", "vacanta", 2000);
	ctr.adauga("vacanta", "Mamaia", "sejur", 2100);

	ctr.stergere(0);
	assert(ctr.getAll().size() == 1);

	try {
		ctr.stergere(2);
		assert(false);
	}
	catch (const OfertaServiceException&) {
		assert(true);
	}
}

void test_modifica_service() {
	OfertaRepo rep;
	OfertaValidator val;
	Wishlist list;
	OfertaService ctr{ rep, val, list };
	ctr.adauga("calatorie", "Maldive", "vacanta", 2000);
	ctr.adauga("vacanta", "Mamaia", "sejur", 2100);

	ctr.modificare(0, "vacanta", "Timisoara", "sejur", 1200);
	assert(ctr.getAll()[0].get_denumire() == "vacanta");
	assert(ctr.getAll()[0].get_destinatie() == "Timisoara");
	try {
		ctr.modificare(3, "vacanta", "Timisoara", "sejur", 1200);
		assert(false);
	}
	catch (const OfertaServiceException&) {
		assert(true);
	}
}

void test_cauta_service() {
	OfertaRepo rep;
	OfertaValidator val;
	Wishlist list;
	OfertaService ctr{ rep, val, list };
	ctr.adauga("calatorie", "Maldive", "vacanta", 2000);
	ctr.adauga("vacanta", "Mamaia", "sejur", 2100);
	Oferta o1{ "calatorie", "Maldive", "vacanta", 2000 };
	assert(ctr.cautare("calatorie", "Maldive") == o1);

	try {
		ctr.cautare("calatorie", "Mamaia");
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}
}

void test_filtreaza_service() {
	OfertaRepo rep;
	OfertaValidator val;
	Wishlist list;
	OfertaService serv{ rep, val, list };
	serv.adauga("vacanta", "Mamaia", "sejur", 1000);
	serv.adauga("vacanta", "Mangalia", "sejur", 1200);
	serv.adauga("calatorie", "Maldive", "sejur", 2000);
	assert(serv.filtreaza_destinatie("Mamaia").size() == 1);
	assert(serv.filtreaza_pret(1100).size() == 2);
	assert(serv.filtreaza_pret(1500).size() == 1);
}

void test_sorteza_seervice() {
	OfertaRepo rep;
	OfertaValidator val;
	Wishlist list;
	OfertaService serv{ rep, val, list };
	serv.adauga("vacanta", "Brasov", "munte", 1000);
	serv.adauga("calatorie", "Mamaia", "mare", 1000);
	serv.adauga("vacanta", "Mangalia", "mare", 900);
	serv.adauga("calatorie", "Timisoara", "oras", 2000);
	auto list_den = serv.sorteaza_denumire()[0];
	assert(list_den.get_denumire() == "calatorie");

	auto list_dest = serv.sorteaza_destinatie()[0];
	assert(list_dest.get_destinatie() == "Brasov");

	auto list_pret_tip = serv.sorteaza_tip_pret()[0];
	assert(list_pret_tip.get_destinatie() == "Mangalia");

}

void test_serv_adauga_in_cos() {
	OfertaRepo rep;
	OfertaValidator val;
	Wishlist list;
	OfertaService serv{ rep, val, list };
	serv.adauga("vacanta", "Brasov", "munte", 1000);
	serv.adauga("calatorie", "Mamaia", "mare", 1000);
	serv.adauga("vacanta", "Mangalia", "mare", 900);
	serv.adauga("calatorie", "Timisoara", "oras", 2000);
	serv.adauga_in_cos("vacanta", "Brasov");
	assert(serv.nr_oferte_in_cos() == 1);
	try {
		serv.adauga_in_cos("vacanta", "Timisoara");
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}
}

void test_serv_sterge_cos() {
	OfertaRepo rep;
	OfertaValidator val;
	Wishlist list;
	OfertaService serv{ rep, val, list };
	serv.adauga("vacanta", "Brasov", "munte", 1000);
	serv.adauga("calatorie", "Mamaia", "mare", 1000);
	serv.adauga("vacanta", "Mangalia", "mare", 900);
	serv.adauga("calatorie", "Timisoara", "oras", 2000);
	serv.adauga_in_cos("vacanta", "Brasov");
	serv.adauga_in_cos("calatorie", "Timisoara");
	assert(serv.nr_oferte_in_cos() == 2);
	serv.sterge_oferte_cos();
	assert(serv.nr_oferte_in_cos() == 0);
}

void test_serv_genereaza_cos() {
	OfertaRepo rep;
	OfertaValidator val;
	Wishlist list;
	OfertaService serv{ rep, val, list };
	serv.adauga("vacanta", "Brasov", "munte", 1000);
	serv.adauga("calatorie", "Mamaia", "mare", 1000);
	serv.adauga("vacanta", "Mangalia", "mare", 900);
	serv.adauga("calatorie", "Timisoara", "oras", 2000);
	serv.adauga_in_cos("vacanta", "Brasov");
	serv.adauga_in_cos("calatorie", "Timisoara");
	serv.genereaza_cos(1);
	assert(serv.nr_oferte_in_cos() == 1);
	try {
		serv.genereaza_cos(7);
		assert(false);
	}
	catch (OfertaWishlistException&) {
		assert(true);
	}
}

void test_serv_export_cos() {
	OfertaRepo rep;
	OfertaValidator val;
	Wishlist list;
	OfertaService serv{ rep, val, list };
	serv.adauga("vacanta", "Brasov", "munte", 1000);
	serv.adauga("calatorie", "Mamaia", "mare", 1000);
	serv.adauga("vacanta", "Mangalia", "mare", 900);
	serv.adauga("calatorie", "Timisoara", "oras", 2000);
	serv.adauga_in_cos("vacanta", "Brasov");
	serv.adauga_in_cos("calatorie", "Timisoara");
	serv.exporta_cos("test_cos");
}

void test_serv_raport() {
	OfertaRepo rep;
	OfertaValidator val;
	Wishlist list;
	OfertaService serv{ rep, val, list };
	serv.adauga("vacanta", "Brasov", "munte", 1000);
	serv.adauga("vacanta", "Mangalia", "mare", 900);
	serv.adauga("calatorie", "Timisoara", "oras", 2000);

	map<string, DTO> rap = serv.raport();
	assert(rap["vacanta"].get_count() == 2);
	assert(rap["calatorie"].get_count() == 1);
}

void test_creaza_cos() {
	Wishlist lista;
	lista.wishlist_gol();
	auto li = lista.get_oferta();
	assert(li.size() == 0);
}

void test_adauga_cos() {
	Wishlist lista;
	lista.wishlist_gol();
	Oferta o1{ "calatorie", "Maldive", "sejur", 2000 };
	Oferta o2{ "vacanta", "Mamaia", "mare", 1500 };
	lista.adauga_wishlist(o1);
	lista.adauga_wishlist(o2);
	auto li = lista.get_oferta();
	assert(li.size() == 2);
	try {
		lista.adauga_wishlist(o1);
		assert(false);
	}
	catch (const OfertaWishlistException&) {
		assert(true);
	}

}

void test_sterge_cos() {
	Wishlist lista;
	lista.wishlist_gol();
	Oferta o1{ "calatorie", "Maldive", "sejur", 2000 };
	Oferta o2{ "vacanta", "Mamaia", "mare", 1500 };
	lista.adauga_wishlist(o1);
	lista.adauga_wishlist(o2);
	lista.wishlist_gol();
	auto li = lista.get_oferta();
	assert(li.size() == 0);
}
