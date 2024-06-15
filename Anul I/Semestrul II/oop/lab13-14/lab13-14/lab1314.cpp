#include "lab1314.h"

void AppGUI::initGUI() {

	vectorbutoane.clear();
	this->setWindowTitle("Aplicatie ~ Agentie de turism");
	this->setAutoFillBackground(true);
	QPalette palette = QPalette();
	palette.setColor(QPalette::Window, "#B76DAE");

	QLinearGradient gradient(this->width() / 2, 0, this->width(), 0);
	gradient.setColorAt(0, QColor("#B76DAE"));
	gradient.setColorAt(1, QColor("#F0C7EB"));

	palette.setBrush(QPalette::Window, QBrush(gradient));

	QFont font = QFont("Fantasy", 12, 10, false);
	QFont bold_font = font;
	bold_font.setBold(true);

	this->setAutoFillBackground(true);
	this->setPalette(palette);
	this->setFont(font);

	//layout principal
	QHBoxLayout* mainly = new QHBoxLayout;
	setLayout(mainly);

	//layout lista
	//layout stanga
	mainly->addLayout(listaLayout, 1);
	listaLayout->addSpacing(20);

	QLabel* listlbl = new QLabel("Tabel de oferte");
	listlbl->setAlignment(Qt::AlignCenter);
	listlbl->setFont(bold_font);

	listaLayout->addWidget(listlbl, 1);

	auto s = serv.raport();

	table_view->resizeColumnsToContents();
	table_view->setMinimumSize(500, 200);
	
	listaLayout->addWidget(table_view, 2);

	listaLayout->addWidget(btn_undo);

	listaLayout->addWidget(btn_open_cos);
	listaLayout->addWidget(btn_open_cos_rdonly);

	//layout operatii

	QVBoxLayout* operatiily = new QVBoxLayout;

	mainly->addLayout(operatiily, 1);

	QFormLayout* formly = new QFormLayout;
	operatiily->addLayout(formly);

	formly->addRow(new QLabel{ "Denumire: " }, txtDenumire);
	formly->addRow(new QLabel{ "Destinatie: " }, txtDestinatie);
	formly->addRow(new QLabel{ "Tip:" }, txtTip);
	formly->addRow(new QLabel{ "Pret:" }, txtPret);
	formly->addRow(new QLabel{ "Pozitie: " }, txtPozitie);

	QHBoxLayout* actiunily = new QHBoxLayout;
	operatiily->addLayout(actiunily);

	actiunily->addWidget(btn_adauga);
	actiunily->addWidget(btn_sterge);
	actiunily->addWidget(btn_modifica);
	actiunily->addWidget(btn_cauta);

	operatiily->addSpacing(20);

	QLabel* operatiicoslbl = new QLabel("Adauga in cos");
	operatiicoslbl->setAlignment(Qt::AlignCenter);

	operatiily->addWidget(operatiicoslbl, 1);

	QFormLayout* formlycos = new QFormLayout;
	operatiily->addLayout(formlycos);

	formlycos->addRow(new QLabel{ "Denumire: " }, txtDenumireCos);
	formlycos->addRow(new QLabel{ "Destinatie: " }, txtDestinatieCos);

	QHBoxLayout* actiuniCosly = new QHBoxLayout;
	operatiily->addLayout(actiuniCosly);

	actiuniCosly->addWidget(btn_adauga_cos);

	QLabel* exportCoslbl = new QLabel{ "Exporta cos" };
	exportCoslbl->setAlignment(Qt::AlignCenter);
	operatiily->addWidget(exportCoslbl);

	QFormLayout* formlyex = new QFormLayout;
	operatiily->addLayout(formlyex);

	formlyex->addRow(new QLabel{ "Nume fisier: " }, txtFileCos);

	actiuniCosly->addWidget(btn_export_cos);

	actiuniCosly->addWidget(btn_sterge_cos);

	QVBoxLayout* sortly = new QVBoxLayout;
	operatiily->addLayout(sortly);
	sortly->addSpacing(20);

	QLabel* sortlbl = new QLabel("Tip de sortare");
	sortlbl->setAlignment(Qt::AlignCenter);
	sortlbl->setFont(bold_font);

	sortly->addWidget(sortlbl, 1);

	sortly->addWidget(btn_sort_den);
	sortly->addWidget(btn_sort_des);
	sortly->addWidget(btn_sort_tip_pret);
	sortly->addSpacing(20);

	QLabel* filtereazalbl = new QLabel("Filtrari");
	filtereazalbl->setAlignment(Qt::AlignCenter);
	filtereazalbl->setFont(bold_font);

	sortly->addWidget(filtereazalbl, 1);

	QFormLayout* filtrare_formly = new QFormLayout;
	sortly->addLayout(filtrare_formly);
	textfilter->setStyleSheet("QLineEdit{font-size: 16px;font-weight: 500;border: 1px solid transparent;border-radius: 4px;padding: 4px 6px;}");
	filtrare_formly->addRow(new QLabel{ "Input: " }, textfilter);

	QHBoxLayout* filtrarely = new QHBoxLayout;
	operatiily->addLayout(filtrarely);

	filtrarely->addWidget(btn_filtr_dest);
	filtrarely->addWidget(btn_filtr_pret);

	listaLayout->addWidget(btn_load);
	operatiily->addSpacing(20);
	operatiily->addWidget(btn_raport);
	operatiily->addWidget(btn_exit);

	auto rap = serv.raport();
	for (const auto& p : rap) {
		QPushButton* buton = new QPushButton(QString::fromStdString(p.first));
		vectorbutoane.push_back(buton);
	}
	for (auto buton : vectorbutoane) {
		butoane_raport->addWidget(buton);
	}
	mainly->addLayout(butoane_raport);

}

void CosGUI::initCosGUI() {

	this->setAutoFillBackground(true);
	QPalette palette = QPalette();
	palette.setColor(QPalette::Window, "#B76DAE");

	QLinearGradient gradient(this->width() / 2, 0, this->width(), 0);
	gradient.setColorAt(0, QColor("#B76DAE"));
	gradient.setColorAt(1, QColor("#F0C7EB"));

	palette.setBrush(QPalette::Window, QBrush(gradient));
	setWindowTitle("Setare wishlist");

	setFont(QFont("Fantasy", 12, 10, false));

	setAutoFillBackground(true);
	setPalette(palette);

	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	QVBoxLayout* cosly = new QVBoxLayout;
	ly->addLayout(cosly);

	QLabel* coslbl = new QLabel("Wishlist");
	coslbl->setAlignment(Qt::AlignCenter);

	QFont font = QFont("Fantasy", 12, 10, false);
	QFont bold_font = font;
	bold_font.setBold(true);

	coslbl->setFont(bold_font);

	cosly->addWidget(coslbl);
	cosly->addWidget(cos_gol);
	cosly->addSpacing(20);

	QLabel* genereazacoslbl = new QLabel("Genereaza wishlist");
	genereazacoslbl->setAlignment(Qt::AlignCenter);
	genereazacoslbl->setFont(bold_font);
	cosly->addWidget(genereazacoslbl);
	QFormLayout* genereazacosly = new QFormLayout;
	cosly->addLayout(genereazacosly);

	txtCosNumar->setStyleSheet("QLineEdit{font-size: 16px;font-weight: 500;border: 1px solid transparent;border-radius: 4px;padding: 4px 6px;}");
	genereazacosly->addRow(new QLabel{ "Numar oferte: " }, txtCosNumar);

	cosly->addWidget(genereaza_cos);
	cosly->addSpacing(20);

	QVBoxLayout* cosoperatiily = new QVBoxLayout;
	ly->addLayout(cosoperatiily);
	cosoperatiily->addWidget(lista_cos);

	cosoperatiily->addWidget(exit);
}

void CosGUI::reloadList(const vector<Oferta>& oferte) {
	model = new MYListModel{ oferte };
	lista_cos->setModel(model);
}

void AppGUI::load_table(const vector<Oferta>& oferte) {
	model = new MyTableModel{ oferte };
	table_view->setModel(model);
	table_view->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void AppGUI::clear_cos_text_box() {
	txtDenumireCos->clear();
	txtDestinatieCos->clear();
}

void AppGUI::adauga_cos_ui() {
	string denumire = txtDenumireCos->text().toStdString();
	string destinatie = txtDestinatieCos->text().toStdString();
	QMessageBox msg;

	auto found = serv.filtreaza_destinatie(destinatie);
	if (found.empty()) {
		msg.warning(this, "Warning", "Oferta nu exista in lista de oferte!");
		clear_cos_text_box();
		return;
	}

	if (found.size() == 1) {
		try {
			serv.adauga_in_cos(denumire, destinatie);
		}
		catch (OfertaWishlistException& ex) {
			msg.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
		catch (OfertaServiceException& ex) {
			msg.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
		catch (OfertaRepoException& ex) {
			msg.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
		catch (ValidateException& ex) {
			std::stringstream sout;
			sout << ex;
			msg.warning(this, "Warning", QString::fromStdString(sout.str()));
		}
	}
	else {
		if (destinatie != "") {
			try {
				serv.adauga_in_cos(denumire, destinatie);
			}
			catch (OfertaWishlistException& ex) {
				msg.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
			}
			catch (OfertaServiceException& ex) {
				msg.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
			}
			catch (OfertaRepoException& ex) {
				msg.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
			}
			catch (ValidateException& ex) {
				std::stringstream sout;
				sout << ex;
				msg.warning(this, "Warning", QString::fromStdString(sout.str()));
			}
		}
		else {
			msg.warning(this, "Warning", "Introduceti destinatia!");
		}
	}
	clear_cos_text_box();
	//cos_nou->reloadList(serv.getAllOferte());
	
	cos_nou->notify();
}

void AppGUI::goleste_cos_ui() {
	serv.sterge_oferte_cos();
	cos_nou->notify();
}

void CosGUI::connectCosSiganls() {
	QObject::connect(exit, &QPushButton::clicked, [&]() {
		this->notify();
		this->close();
		});

	QObject::connect(cos_gol, &QPushButton::clicked, [&]() {
		serv.sterge_oferte_cos();
		reloadList(serv.getAllOferte());
		serv.notify();
		});

	QObject::connect(genereaza_cos, &QPushButton::clicked, [&]() {
		string numar = txtCosNumar->text().toStdString();
		int nr_corect;
		QMessageBox msg;

		try {
			nr_corect = stoi(numar);
		}
		catch (std::invalid_argument& mesaj) {
			msg.warning(this, "Warining", "Input invalid!\n");
			txtCosNumar->clear();
			return;
		}

		try {
			serv.genereaza_cos(nr_corect);
		}
		catch (OfertaWishlistException& mesaj) {
			msg.warning(this, "Warining", QString::fromStdString(mesaj.get_mesaj()));
		}
		serv.notify();
		reloadList(serv.getAllOferte());
		});
}

void AppGUI::clear_text_box() {
	txtDenumire->clear();
	txtDestinatie->clear();
	txtTip->clear();
	txtPret->clear();
}

void AppGUI::adauga_ui() {
	string denumire = txtDenumire->text().toStdString();
	string destinatie = txtDestinatie->text().toStdString();
	string tip = txtTip->text().toStdString();
	string pret = txtPret->text().toStdString();
	QMessageBox msgbox;

	qDebug() << denumire << destinatie;

	int pret_corect;
	try {
		pret_corect = stoi(pret);
	}
	catch (std::invalid_argument& mesaj) {
		msgbox.warning(this, "Warning", "Pretul trebuie sa fie un numar natural!");
		return;
	}
	try {
		serv.adauga(denumire, destinatie, tip, pret_corect);
	}
	catch (OfertaRepoException& ex) {
		msgbox.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
	}
	catch (ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		msgbox.warning(this, "Warning", QString::fromStdString(sout.str()));
	}
	clear_text_box();
	load_table(serv.getAll());
}

void AppGUI::sterge_ui() {
	string pozitie = txtPozitie->text().toStdString();
	QMessageBox msgbox;

	int pozitie_corecta;
	try {
		pozitie_corecta = stoi(pozitie);
	}
	catch (std::invalid_argument& mesaj) {
		msgbox.warning(this, "Warning", "Pozitia trebuie sa fie un numar natural!");
		return;
	}
	try {
		serv.stergere(pozitie_corecta);
	}
	catch (OfertaServiceException& ex) {
		msgbox.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
	}
	catch (OfertaRepoException& ex) {
		msgbox.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
	}

	clear_text_box();
	load_table(serv.getAll());
}

void AppGUI::modifica_ui() {
	string pozitie = txtPozitie->text().toStdString();
	string denumire = txtDenumire->text().toStdString();
	string destinatie = txtDestinatie->text().toStdString();
	string tip = txtTip->text().toStdString();
	string pret = txtPret->text().toStdString();
	QMessageBox msgbox;

	qDebug() << denumire << destinatie;

	int pret_corect;
	try {
		pret_corect = stoi(pret);
	}
	catch (std::invalid_argument& mesaj) {
		msgbox.warning(this, "Warning", "Pretul trebuie sa fie un numar natural!");
		return;
	}

	qDebug() << pozitie;
	int pozitie_corecta;
	try {
		pozitie_corecta = stoi(pozitie);
	}
	catch (std::invalid_argument& mesaj) {
		msgbox.warning(this, "Warning", "Pozitia trebuie sa fie un numar natural!");
		return;
	}

	try {
		serv.modificare(pozitie_corecta, denumire, destinatie, tip, pret_corect);
	}
	catch (OfertaServiceException& ex) {
		msgbox.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
	}
	catch (OfertaRepoException& ex) {
		msgbox.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
	}

	clear_text_box();
	load_table(serv.getAll());
}

void AppGUI::cauta_ui() {
	string denumire = txtDenumire->text().toStdString();
	string destinatie = txtDestinatie->text().toStdString();
	QMessageBox msgbox;

	qDebug() << denumire << destinatie;

	try {
		Oferta oferta = serv.cautare(denumire, destinatie);
		qDebug() << oferta.to_string_print();

		vector<Oferta> oferte;
		oferte.push_back(oferta);

		clear_text_box();
		load_table(oferte);
	}
	catch (OfertaServiceException& ex) {
		msgbox.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
	}
	catch (OfertaRepoException& ex) {
		msgbox.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
	}
	txtDenumire->clear();
	txtDestinatie->clear();
}

void AppGUI::sorteaza_denumire_ui() {
	vector<Oferta> oferte = serv.sorteaza_denumire();
	load_table(oferte);
}

void AppGUI::sorteaza_destinatie_ui() {
	vector<Oferta> oferte = serv.sorteaza_destinatie();
	load_table(oferte);
}

void AppGUI::sorteaza_tip_pret_ui() {
	vector<Oferta> oferte = serv.sorteaza_tip_pret();
	load_table(oferte);
}

void AppGUI::filtreaza_destinatie_ui() {
	string destinatie = textfilter->text().toStdString();
	QMessageBox msgBox;

	qDebug() << destinatie;

	vector<Oferta> oferte = serv.filtreaza_destinatie(destinatie);
	for (const auto& oferta : oferte) {
		qDebug() << oferta.to_string_print();
	}

	textfilter->clear();
	load_table(oferte);
}

void AppGUI::filteraza_pret_ui() {
	string pret = textfilter->text().toStdString();
	QMessageBox msgbox;
	int pret_corect;
	try {
		pret_corect = stoi(pret);
	}
	catch (std::invalid_argument& mesaj) {
		msgbox.warning(this, "Warning", "Input invalid!");
		textfilter->clear();
		return;
	}

	vector <Oferta> oferte = serv.filtreaza_pret(pret_corect);
	for (const auto& oferta : oferte) {
		qDebug() << oferta.to_string_print();
	}

	textfilter->clear();
	load_table(oferte);
}

void AppGUI::raport_ui() {
	for (auto buton : vectorbutoane) {
		QObject::connect(buton, &QPushButton::clicked, this, [this, buton]() {
			auto txt = buton->text();
			const auto& rap = serv.raport();
			for (const auto& p : rap) {
				if (p.first == txt.toStdString()) {
					QMessageBox::information(this, "Raport", "Numarul de oferte de acest tip este: " + QString::number(p.second.get_count()));
				}
			}
			});
	}
}

void AppGUI::connectSignals() {
	QMessageBox msgBox;

	QObject::connect(btn_exit, &QPushButton::clicked, [&]() {
		QMessageBox exitMessageBox;

		exitMessageBox.setWindowTitle("Iesire");
		exitMessageBox.setText("La revedere!");

		exitMessageBox.exec();
		this->close();
		});

	QObject::connect(btn_load, &QPushButton::clicked, [&]() {
		load_table(serv.getAll());
		});

	QObject::connect(btn_adauga, &QPushButton::clicked, this, &AppGUI::adauga_ui);
	QObject::connect(btn_sterge, &QPushButton::clicked, this, &AppGUI::sterge_ui);
	QObject::connect(btn_modifica, &QPushButton::clicked, this, &AppGUI::modifica_ui);
	QObject::connect(btn_cauta, &QPushButton::clicked, this, &AppGUI::cauta_ui);

	QObject::connect(btn_sort_den, &QPushButton::clicked, this, &AppGUI::sorteaza_denumire_ui);
	QObject::connect(btn_sort_des, &QPushButton::clicked, this, &AppGUI::sorteaza_destinatie_ui);
	QObject::connect(btn_sort_tip_pret, &QPushButton::clicked, this, &AppGUI::sorteaza_tip_pret_ui);

	QObject::connect(btn_filtr_dest, &QPushButton::clicked, this, &AppGUI::filtreaza_destinatie_ui);
	QObject::connect(btn_filtr_pret, &QPushButton::clicked, this, &AppGUI::filteraza_pret_ui);

	QObject::connect(btn_undo, &QPushButton::clicked, [&]() {
		try {
			serv.undo();
		}
		catch (OfertaServiceException& ex) {
			msgBox.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
		catch (OfertaRepoException& ex) {
			msgBox.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
		}

		load_table(serv.getAll());
		});

	QObject::connect(btn_open_cos, &QPushButton::clicked, [&]() {
		CosGUI* cos_n = new CosGUI(serv);
		cos_n->initCosGUI();
		cos_n->connectCosSiganls();
		cos_n->show();
		cos_n->reloadList(serv.getAllOferte());
		cos_n->addObserver(cos_n);
		});

	QObject::connect(btn_open_cos_rdonly, &QPushButton::clicked, [&]() {
		CosReadOnlyGUI* cos_rdonly_n = new CosReadOnlyGUI{ serv };
		cos_rdonly_n->show();
		});

	QObject::connect(btn_adauga_cos, &QPushButton::clicked, this, &AppGUI::adauga_cos_ui);

	QObject::connect(btn_sterge_cos, &QPushButton::clicked, this, &AppGUI::goleste_cos_ui);

	QMessageBox mesajCos;

	QObject::connect(btn_export_cos, &QPushButton::clicked, [&]() {
		string nume_fisier = txtFileCos->text().toStdString();

		QMessageBox msg;

		try {
			serv.exporta_cos(nume_fisier);
		}
		catch (OfertaWishlistException& ex) {
			msgBox.warning(nullptr, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
		});
	raport_ui();
}