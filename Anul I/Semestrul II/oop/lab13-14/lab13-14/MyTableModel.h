#pragma once
#include <QAbstractTableModel>
#include <QAbstractItemView>
#include <iostream>
#include <vector>
#include "domeniu.h"

using std::vector;

class MyTableModel : public QAbstractTableModel {
	vector<Oferta> oferte;

public:
	MyTableModel(const vector<Oferta>& oferte) : oferte{ oferte } {};
	
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override {
		return oferte.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex{}) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			const Oferta& o = oferte[index.row()];
			switch (index.column()) {
			case 0:
				return QString::fromStdString(o.get_denumire());
			case 1:
				return QString::fromStdString(o.get_destinatie());
			case 2:
				return QString::fromStdString(o.get_tip());
			case 3:
				return QString::number(o.get_pret());
			default:
				break;
			}
		}
		return QVariant{};
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
			switch (section){
			case 0:
				return "Denumire";
			case 1:
				return "Destinatie";
			case 2:
				return "Tip";
			case 3:
				return "Pret";
			default:
				break;
			}
		}
		else if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
			return section + 1;
		}
		return QVariant{};
	}

	Oferta getoferta(const vector<Oferta>& oferte) {
		this->oferte = oferte;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}
};