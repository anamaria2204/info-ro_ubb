#include "teste.h"
#include "domeniu.h"
#include "repo.h"
#include "assert.h"
#include "validator.h"
#include "service.h"
#include <sstream>

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
	assert(comp_denumire(o1, o2) == 0);
	assert(comp_denumire(o2, o1) == 1);
}

void test_cmp_destinatie() {
	Oferta o1{ "calatorie", "Maldive", "sejur", 2000 };
	Oferta o2{ "vacanta", "Mamaia", "mare", 1500 };
	assert(comp_destinatie(o1, o2) == 0);
	assert(comp_destinatie(o2, o1) == 1);
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
	auto ls = repo.getAll();

	assert(ls.getSize() == 1);
	try {
		repo.store(Oferta{ "calatorie", "Maldive", "vacanta", 2000 });
		assert(false);
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}
	assert(ls.getSize() == 1);

}

void test_sterge_repo() {
	OfertaRepo repo;
	repo.store(Oferta{ "calatorie", "Maldive", "sejur", 2000 });
	assert(repo.getAll().getSize() == 1);
	repo.sterge(0);
	assert(repo.getAll().getSize() == 0);
	try {
		repo.sterge(3);
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
	assert(repo.getAll().getSize() == 2);
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
	assert(repo.getAll().getSize() == 2);
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
	OfertaService ctr{ rep,val };
	ctr.adauga("calatorie", "Maldive", "vacanta", 2000);
	assert(ctr.getAll().getSize() == 1);

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
	OfertaService ctr{ rep,val };
	ctr.adauga("calatorie", "Maldive", "vacanta", 2000);
	ctr.adauga("vacanta", "Mamaia", "sejur", 2100);

	ctr.stergere(0);
	assert(ctr.getAll().getSize() == 1);

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
	OfertaService ctr{ rep,val };
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
	OfertaService ctr{ rep,val };
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
	OfertaService serv{ rep, val };
	serv.adauga("vacanta", "Mamaia", "sejur", 1000);
	serv.adauga("vacanta", "Mangalia", "sejur", 1200);
	serv.adauga("calatorie", "Maldive", "sejur", 2000);
	assert(serv.filtreaza_destinatie("Mamaia").getSize() == 1);
	assert(serv.filtreaza_pret(1100).getSize() == 2);
	assert(serv.filtreaza_pret(1500).getSize() == 1);
}

void test_sorteza_seervice() {
	OfertaRepo rep;
	OfertaValidator val;
	OfertaService serv{ rep, val };
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