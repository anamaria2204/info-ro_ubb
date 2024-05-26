#include "ui.h"
#include <iostream>
#include "teste.h"
#include <sstream>

using std::cin;
using std::cout;

void print_meniu() {
	cout << "Aplicatia permite: \n";
	cout << "1. Adaugare oferta\n";
	cout << "2. Stergere oferta\n";
	cout << "3. Modificare oferta\n";
	cout << "4. Cauta oferta\n";
	cout << "5. Filtreaza oferta dupa denstinatie\n";
	cout << "6. Filtreaza oferta dupa pret\n";
	cout << "7. Sorteaza oferte\n";
	cout << "8. Afiseaza lista de oferte\n";
	cout << "0. Exit\n";
}

void testAll() {
	test_domeniu();
	test_validator();
	test_cmp_denumire();
	test_cmp_destinatie();

	test_adauga_repo();
	test_sterge_repo();
	test_modifica_repo();
	test_cauta_repo();

	test_adauga_service();
	test_sterge_service();
	test_modifica_service();
	test_cauta_service();
	test_filtreaza_service();
	test_sorteza_seervice();

}

void UI::tipareste(const vector<Oferta>& oferte) {
	cout << "Ofertele: \n";
	for (const auto& oferta : oferte) {
		cout << "Denumire: " << oferta.get_denumire() << " Destinatie: " << oferta.get_destinatie()
			<< " Tip: " << oferta.get_tip() << " Pret: " << oferta.get_pret() << "\n";
	}
}

void UI::adaugaOferta() {
	string denumire;
	string destinatie;
	string tip;
	float pret;
	cout << "Denumire: ";
	cin >> denumire;
	cout << "Destinatie: ";
	cin >> destinatie;
	cout << "Tip: ";
	cin >> tip;
	cout << "Pret: ";
	cin >> pret;
	try {
		srv.adauga(denumire, destinatie, tip, pret);
		cout << "\n";
		cout << "Oferta adaugata cu succes!\n";
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		cout << mesaj << "\n";
	}
	catch (const OfertaRepoException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		cout << mesaj << "\n";
	}
}

void UI::start() {
	while (true) {
		cout << "\n";
		print_meniu();
		cout << "\n";
		cout << "Optiunea dorita este: ";
		int cmd = 0;
		cin >> cmd;
		if (cmd == 0) {
			cout << "La revdere!";
			break;
		}
		else if (cmd == 1) {
			adaugaOferta();
		}
		else if (cmd == 2) {
			int pozitie;
			cout << "Pozitia dorita: ";
			cin >> pozitie;
			try {
				srv.stergere(pozitie);
				cout << "Oferta stearsa cu succes!";
			}
			catch (const ValidateException& ex) {
				std::stringstream sout;
				sout << ex;
				const auto mesaj = sout.str();
				cout << mesaj << "\n";
			}
			catch (const OfertaRepoException& ex) {
				std::stringstream sout;
				sout << ex;
				const auto mesaj = sout.str();
				cout << mesaj << "\n";
			}
			catch (const OfertaServiceException& ex) {
				std::stringstream sout;
				sout << ex;
				const auto mesaj = sout.str();
				cout << mesaj << "\n";
			}
		}
		else if (cmd == 3) {
			int pozitie;
			cout << "Pozitia dorita: ";
			cin >> pozitie;
			string denumire;
			string destinatie;
			string tip;
			float pret;
			cout << "Noua denumire: ";
			cin >> denumire;
			cout << "Noua destinatie: ";
			cin >> destinatie;
			cout << "Noual tip: ";
			cin >> tip;
			cout << "Noua pret: ";
			cin >> pret;
			try {
				srv.modificare(pozitie, denumire, destinatie, tip, pret);
				cout << "\n";
				cout << "Modificare realizata cu succes!";
			}
			catch (const OfertaServiceException& ex) {
				std::stringstream sout;
				sout << ex;
				const auto mesaj = sout.str();
				cout << mesaj << "\n";
			}
		}
		else if (cmd == 4) {
			string denumire;
			string destinatie;
			cout << "Denumirea cautata: ";
			cin >> denumire;
			cout << "Destinatia cautata: ";
			cin >> destinatie;
			try {
				Oferta o = srv.cautare(denumire, destinatie);
				cout << "Oferta cautata este: ";
				cout << "Denumire: " << o.get_denumire() <<
					", Destinatie: " << o.get_destinatie() <<
					", Tip: " << o.get_tip() <<
					", Pret: " << o.get_pret();
			}
			catch (const OfertaRepoException& ex) {
				std::stringstream sout;
				sout << ex;
				const auto mesaj = sout.str();
				cout << mesaj << "\n";
			}
		}
		else if (cmd == 5) {
			string destinatie;
			cout << "Destinatie: ";
			cin >> destinatie;
			tipareste(srv.filtreaza_destinatie(destinatie));
		}
		else if (cmd == 6) {
			float pret;
			cout << "Pret: ";
			cin >> pret;
			tipareste(srv.filtreaza_pret(pret));
		}
		else if (cmd == 7) {
			int optiune;
			cout << "Ofertele pot fi sortate dupa: 1 - denumire, 2 - destinatie, 3 - tip+pret\n";
			cout << "Optiunea dorita de filtrare este: ";
			cin >> optiune;
			if (optiune == 1) {
				tipareste(srv.sorteaza_denumire());
			}
			else if (optiune == 2) {
				tipareste(srv.sorteaza_destinatie());
			}
			else if (optiune == 3) {
				tipareste(srv.sorteaza_tip_pret());
			}
		}
		else if (cmd == 8) {
			cout << "\n";
			tipareste(srv.getAll());
		}
		else {
			cout << "\n";
			cout << "Optiune invalida, introduceti alta optiune!\n";
		}
	}
}