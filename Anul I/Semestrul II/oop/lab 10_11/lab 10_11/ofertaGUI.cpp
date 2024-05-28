#include "petGUI.h"

void AppGUI::initGUI() {

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
	QVBoxLayout* listly = new QVBoxLayout;
	mainly->addLayout(listly, 1);

	QLabel* listlbl = new QLabel("Lista de oferte");
	listlbl->setAlignment(Qt::AlignCenter);
	listlbl->setFont(bold_font);

	listly->addWidget(listlbl, 1);
	table->resizeColumnsToContents();
	table->setMinimumSize(500, 200);
	listly->addWidget(table, 2);
	listly->addWidget(lista_oferte_ui, 3);
	listly->addWidget(btn_undo);

	listly->addWidget(btn_cos);

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

	listly->addWidget(btn_load_table);
	listly->addWidget(btn_load_list);
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

void AppGUI::cosGUI() {

	this->setAutoFillBackground(true);
	QPalette palette = QPalette();
	palette.setColor(QPalette::Window, "#B76DAE");

	QLinearGradient gradient(this->width() / 2, 0, this->width(), 0);
	gradient.setColorAt(0, QColor("#B76DAE"));
	gradient.setColorAt(1, QColor("#F0C7EB"));

	palette.setBrush(QPalette::Window, QBrush(gradient));
	wishlist->setWindowTitle("Setare wishlist");

	wishlist->setFont(QFont("Fantasy", 12, 10, false));

	wishlist->setAutoFillBackground(true);
	wishlist->setPalette(palette);

	QHBoxLayout* ly = new QHBoxLayout;
	wishlist->setLayout(ly);

	QVBoxLayout* cosly = new QVBoxLayout;
	ly->addLayout(cosly);

	QLabel* coslbl = new QLabel("Wishlist");
	coslbl->setAlignment(Qt::AlignCenter);

	QFont font = QFont("Fantasy", 12, 10, false);
	QFont bold_font = font;
	bold_font.setBold(true);

	coslbl->setFont(bold_font);

	cosly->addWidget(coslbl);
	cosly->addWidget(btn_sterge_cos);
	cosly->addSpacing(20);

	QFormLayout* genereazaly = new QFormLayout;
	cosly->addLayout(genereazaly);

	txtDenumireCos->setStyleSheet("QLineEdit{font-size: 16px;font-weight: 500;border: 1px solid transparent;border-radius: 4px;padding: 4px 6px;}");
	txtDestinatieCos->setStyleSheet("QLineEdit{font-size: 16px;font-weight: 500;border: 1px solid transparent;border-radius: 4px;padding: 4px 6px;}");
	genereazaly->addRow(new QLabel{ "Denumire: " }, txtDenumireCos);
	genereazaly->addRow(new QLabel{ "Destinatie: " }, txtDestinatieCos);

	cosly->addWidget(btn_adauga_cos);
	cosly->addSpacing(20);

	QLabel* genereazacoslbl = new QLabel("Genereaza wishlist");
	genereazacoslbl->setAlignment(Qt::AlignCenter);
	genereazacoslbl->setFont(bold_font);
	cosly->addWidget(genereazacoslbl);
	QFormLayout* genereazacosly = new QFormLayout;
	cosly->addLayout(genereazacosly);

	txtNumarCos->setStyleSheet("QLineEdit{font-size: 16px;font-weight: 500;border: 1px solid transparent;border-radius: 4px;padding: 4px 6px;}");
	genereazacosly->addRow(new QLabel{ "Numar oferte: " }, txtNumarCos);

	cosly->addWidget(btn_genereaza_cos);
	cosly->addSpacing(20);

	QLabel* exportcoslbl = new QLabel("Exporta wishlist");
	exportcoslbl->setAlignment(Qt::AlignCenter);
	exportcoslbl->setFont(bold_font);
	cosly->addWidget(exportcoslbl);
	QFormLayout* exportly = new QFormLayout;
	cosly->addLayout(exportly);

	txtFileCos->setStyleSheet("QLineEdit{font-size: 16px;font-weight: 500;border: 1px solid transparent;border-radius: 4px;padding: 4px 6px;}");
	exportly->addRow(new QLabel{ "Nume fisier:" }, txtFileCos);

	cosly->addWidget(btn_export_cos);

	QVBoxLayout* cosoperatiily = new QVBoxLayout;
	ly->addLayout(cosoperatiily);
	cosoperatiily->addWidget(lista_oferte);

	cosoperatiily->addWidget(btn_exit_cos);
}

void AppGUI::load_table(const vector<Oferta>& oferte) {
	this->table->clearContents();
	this->table->setColumnCount(5);
	this->table->setRowCount(oferte.size() + 1);

	int nr_linii = 0;
	table->verticalHeader()->setVisible(false);
	table->horizontalHeader()->setVisible(false);
	table->setItem(nr_linii, 0, new QTableWidgetItem("Nr."));
	table->setItem(nr_linii, 1, new QTableWidgetItem("Denumire"));
	table->setItem(nr_linii, 2, new QTableWidgetItem("Destinatie"));
	table->setItem(nr_linii, 3, new QTableWidgetItem("Tip"));
	table->setItem(nr_linii, 4, new QTableWidgetItem("Pret"));

	nr_linii++;

	for (const auto& oferta : oferte) {
		table->setItem(nr_linii, 0, new QTableWidgetItem(QString::number(nr_linii)));
		table->setItem(nr_linii, 1, new QTableWidgetItem(QString::fromStdString(oferta.get_denumire())));
		table->setItem(nr_linii, 2, new QTableWidgetItem(QString::fromStdString(oferta.get_destinatie())));
		table->setItem(nr_linii, 3, new QTableWidgetItem(QString::fromStdString(oferta.get_tip())));
		table->setItem(nr_linii, 4, new QTableWidgetItem(QString::number(oferta.get_pret())));
		nr_linii++;
	}
}

void AppGUI::load_list(const vector<Oferta>& oferte) {
	lista_oferte->clear();
	for (const auto& oferta : oferte) {
		lista_oferte->addItem(QString::fromStdString(oferta.get_denumire() + " - destinatie. " + oferta.get_destinatie()));
	}
}

void AppGUI::load_list_oferte(const vector<Oferta>& oferte) {
	lista_oferte_ui->clear();
	for (const auto& oferta : oferte) {
		lista_oferte_ui->addItem(QString::fromStdString(oferta.get_denumire() + " - destinatie. " + oferta.get_destinatie()));
	}
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
		msg.warning(wishlist, "Warning", "Oferta nu exista in lista de oferte!");
		clear_cos_text_box();
		return;
	}

	if (found.size() == 1) {
		try {
			serv.adauga_in_cos(denumire, destinatie);
		}
		catch (OfertaWishlistException& ex) {
			msg.warning(wishlist, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
		catch (OfertaServiceException& ex) {
			msg.warning(wishlist, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
		catch (OfertaRepoException& ex) {
			msg.warning(wishlist, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
		catch (ValidateException& ex) {
			std::stringstream sout;
			sout << ex;
			msg.warning(wishlist, "Warning", QString::fromStdString(sout.str()));
		}
	}
	else {
		if (destinatie != "") {
			try {
				serv.adauga_in_cos(denumire, destinatie);
			}
			catch (OfertaWishlistException& ex) {
				msg.warning(wishlist, "Warning", QString::fromStdString(ex.get_mesaj()));
			}
			catch (OfertaServiceException& ex) {
				msg.warning(wishlist, "Warning", QString::fromStdString(ex.get_mesaj()));
			}
			catch (OfertaRepoException& ex) {
				msg.warning(wishlist, "Warning", QString::fromStdString(ex.get_mesaj()));
			}
			catch (ValidateException& ex) {
				std::stringstream sout;
				sout << ex;
				msg.warning(wishlist, "Warning", QString::fromStdString(sout.str()));
			}
		}
		else {
			msg.warning(wishlist, "Warning", "Introduceti destinatia!");
		}
	}
	clear_cos_text_box();
	load_list(serv.getAllOferte());
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
	catch(OfertaServiceException& ex){
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
	catch (OfertaRepoException& ex){
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
		load_list_oferte(oferte);
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

	QObject::connect(btn_load_table, &QPushButton::clicked, [&]() {
		load_table(serv.getAll());
	});
	QObject::connect(btn_load_list, &QPushButton::clicked, [&]() {
		load_list_oferte(serv.getAll());
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

	QObject::connect(btn_cos, &QPushButton::clicked, [&]() {
		wishlist->show();
		});

	QObject::connect(btn_exit_cos, &QPushButton::clicked, [&]() {
		wishlist->close();
		});

	QObject::connect(btn_adauga_cos, &QPushButton::clicked, this, &AppGUI::adauga_cos_ui);

	QObject::connect(btn_sterge_cos, &QPushButton::clicked, [&]() {
		serv.sterge_oferte_cos();
		load_list(serv.getAllOferte());
		});
	QMessageBox mesajCos;

	QObject::connect(btn_genereaza_cos, &QPushButton::clicked, [&]() {
		string nr_oferte = txtNumarCos->text().toStdString();
		int nr_oferte_corecte;
		try {
			nr_oferte_corecte = stoi(nr_oferte);
		}
		catch (std::invalid_argument& mesaj) {
			txtNumarCos->clear();
			mesajCos.warning(wishlist, "Warning", "Numarul de oferte trebuie sa fie un numar natural");
			return;
		}
		try {
			serv.genereaza_cos(nr_oferte_corecte);
		}
		catch (OfertaWishlistException& ex) {
			msgBox.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
		}
		catch (OfertaServiceException& ex) {
			msgBox.warning(this, "Warning", QString::fromStdString(ex.get_mesaj()));
		}

		txtNumarCos->clear();
		load_list(serv.getAllOferte());
		});

	QObject::connect(btn_export_cos, &QPushButton::clicked, [&]() {
		string nume_fisier = txtFileCos->text().toStdString();
		serv.exporta_cos(nume_fisier);
		txtFileCos->clear();
		});
	raport_ui();
}