#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QLabel>
#include <QDebug>
#include <QRadioButton>
#include <QHeaderView>
#include <QSplitter>
#include <QIcon>
#include <QPaintEvent>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include "service.h"
#include "domeniu.h"
#include <sstream>
#include "observer.h"
#include <qpainter.h>

#include "MyListModel.h"
#include "MyTableModel.h"

class CosGUI : public QWidget, public Observable, public Observer {
	friend class AppGUI;
	friend class OfertaService;
	friend class CosReadOnlyGUI;

private:
	OfertaService& serv;

	//butoane
	QPushButton* cos_gol = new QPushButton{ "&Goleste cos" };
	QPushButton* genereaza_cos = new QPushButton{ "&Genereaza cos" };
	QPushButton* exit = new QPushButton{ "&Exit" };

	//textboxuri
	QLineEdit* txtCosNumar = new QLineEdit;

	//lista
	QListView* lista_cos = new QListView;
	MYListModel* model = nullptr;

public:
	explicit CosGUI(OfertaService& serv) : serv{ serv } {
		serv.addObserver(this);
	};

	void initCosGUI();
	void connectCosSiganls();
	void reloadList(const vector<Oferta>& oferte);
	void update() override {
		reloadList(serv.getAllOferte());
	}

};

class CosReadOnlyGUI : public QWidget, public Observer {
	friend class CosGUI;
	OfertaService& serv;
	QListWidget* lista_obiecte = new QListWidget;

public:
	explicit CosReadOnlyGUI(OfertaService& serv) : serv{ serv } {
		initCosReadOnlyGUI();
		serv.addObserver(this);
	}

	void initCosReadOnlyGUI() {
		this->setWindowTitle("Cos ~ read only");
	}

	void update() override {
		repaint();
	}

	void reload() {
		lista_obiecte->clear();
		for (const auto& o : serv.getAllOferte())
			lista_obiecte->addItem(QString::fromStdString(o.to_string_print()));
	}

	void paintEvent(QPaintEvent* e) override {
		QPainter p(this);
		srand(time(0));

		int x = -20;
		for (const auto& elem : serv.getAllOferte()) {
			x += 40;
			int forma = rand() % 4;
			int inaltime = rand() % 130;
			int start_y = rand() % 60;

			QColor color;

			int color_num = rand() % 5;
			switch (color_num) {
			case 0:
				color = Qt::red;
				break;
			case 1:
				color = Qt::blue;
				break;
			case 2:
				color = Qt::green;
				break;
			case 3:
				color = Qt::yellow;
				break;
			case 4:
				color = Qt::cyan;
				break;
			default:
				break;
			}
			switch (forma) {
			case 0:
				p.drawRect(x, start_y, 20, inaltime);
				break;
			case 1:
				p.drawEllipse(x, start_y, 20, inaltime);
				break;
			case 2:
				p.fillRect(x, start_y, 20, inaltime, color);
				break;
			default:
				p.fillRect(x, start_y, 20, inaltime, color);
				break;
			}
		}
	}

	~CosReadOnlyGUI() {
		serv.removeObserver(this);
	}
};


class AppGUI : public QWidget {

public:
	AppGUI(OfertaService& serv) : serv{ serv } {
		initGUI();
		cos_nou = new CosGUI(serv);
		cos_nou->initCosGUI();
		cos_nou->connectCosSiganls();
		connectSignals();
	}

private:

	MyTableModel* model = nullptr;
	QTableView* table_view = new QTableView;


	OfertaService& serv;
	CosGUI* cos_nou;
	QTableWidget* table_main = new QTableWidget;
	QVBoxLayout* listaLayout = new QVBoxLayout;

	//butoane

	QPushButton* btn_adauga = new QPushButton{ "Adauga" };
	QPushButton* btn_sterge = new QPushButton{ "Sterge" };
	QPushButton* btn_modifica = new QPushButton{ "Modifica" };
	QPushButton* btn_cauta = new QPushButton{ "Cauta" };
	QPushButton* btn_undo = new QPushButton{ "Undo" };
	QPushButton* btn_cos = new QPushButton{ "Cos" };
	QPushButton* btn_sort_den = new QPushButton{ "Sorteaza dupa denumire" };
	QPushButton* btn_sort_des = new QPushButton{ "Sorteaza dupa destinatie" };
	QPushButton* btn_sort_tip_pret = new QPushButton{ "Sorteaza dupa tip si pret" };
	QPushButton* btn_filtr_dest = new QPushButton{ "Filtreaza dupa destinatie" };
	QPushButton* btn_filtr_pret = new QPushButton{ "Filtreaza dupa pret" };
	QLineEdit* textfilter = new QLineEdit;
	QPushButton* btn_exit = new QPushButton{ "Exit" };
	QPushButton* btn_load = new QPushButton{ "Load" };

	//butoane pentru cos

	QPushButton* btn_open_cos = new QPushButton{ "Deschide cos" };
	QPushButton* btn_open_cos_rdonly = new QPushButton{ "Deschide cos read only" };
	QPushButton* btn_adauga_cos = new QPushButton{ "&Adauga in cos" };
	QPushButton* btn_sterge_cos = new QPushButton{ "&Goleste cos" };
	QPushButton* btn_export_cos = new QPushButton{ "&Export cos" };
	
	QLineEdit* txtDenumireCos = new QLineEdit;
	QLineEdit* txtFileCos = new QLineEdit;
	QLineEdit* txtDestinatieCos = new QLineEdit;

	//buton dinamic
	vector<QPushButton*> vectorbutoane;
	QVBoxLayout* butoane_raport = new QVBoxLayout;
	QPushButton* btn_raport = new QPushButton{ "Raport" };

	//layout

	QLineEdit* txtDenumire = new QLineEdit;
	QLineEdit* txtDestinatie = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;
	QLineEdit* txtPozitie = new QLineEdit;
	
	void load_table(const vector<Oferta>& oferte);
	void load_list_oferte(const vector <Oferta>& oferte);

	void connectSignals();
	void initGUI();

	void clear_text_box();
	void clear_cos_text_box();
	void adauga_ui();
	void sterge_ui();
	void modifica_ui();
	void cauta_ui();
	void filtreaza_destinatie_ui();
	void filteraza_pret_ui();
	void sorteaza_denumire_ui();
	void sorteaza_destinatie_ui();
	void sorteaza_tip_pret_ui();
	void raport_ui();
	void adauga_cos_ui();
	void goleste_cos_ui();
};