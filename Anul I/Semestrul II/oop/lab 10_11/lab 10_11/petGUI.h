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
#include <QGraphicsDropShadowEffect>
#include "service.h"
#include "domeniu.h"
#include <sstream>

class AppGUI : public QWidget {

private:
	OfertaService& serv;
	QWidget* wishlist = new QWidget;
	QTableWidget* table = new QTableWidget;
	QListWidget* lista_oferte = new QListWidget;
	QListWidget* lista_oferte_ui = new QListWidget;

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
	QPushButton* btn_load_table = new QPushButton{ "Load table" };
	QPushButton* btn_load_list = new QPushButton{ " Load list" };

	//butoane pentru cos

	QPushButton* btn_adauga_cos = new QPushButton{ "Adauga in cos" };
	QPushButton* btn_sterge_cos = new QPushButton{ "Goleste cos" };
	QPushButton* btn_genereaza_cos = new QPushButton{ "Genereaza cos" };
	QPushButton* btn_export_cos = new QPushButton{ "Export cos" };
	QPushButton* btn_exit_cos = new QPushButton{ "Exit" };

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

	//pt cos

	QLineEdit* txtDenumireCos = new QLineEdit;
	QLineEdit* txtFileCos = new QLineEdit;
	QLineEdit* txtDestinatieCos = new QLineEdit;
	QLineEdit* txtNumarCos = new QLineEdit;

	void load_list(const vector<Oferta>& oferte);
	void load_table(const vector<Oferta>& oferte);
	void load_list_oferte(const vector <Oferta>& oferte);
	void cosGUI();
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

public:
	AppGUI(OfertaService& serv) : serv{ serv } {
		initGUI();
		cosGUI();
		connectSignals();
	}
};