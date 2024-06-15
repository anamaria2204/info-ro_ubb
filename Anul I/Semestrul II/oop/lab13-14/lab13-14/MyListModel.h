#pragma once
#include <QAbstractListModel>
#include <vector>
#include "service.h"
#include <sstream>

using namespace std;

class MYListModel : public QAbstractListModel {
	vector <Oferta> oferte;

public:
	MYListModel(const vector<Oferta>& oferte) : oferte{ oferte } {};

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override {
		return oferte.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			const Oferta& o = oferte[index.row()];
			stringstream ss;
			ss << o.get_denumire() << "- destinatie. " << o.get_destinatie();
			return QString::fromStdString(ss.str());
		}
		if (role == Qt::UserRole) {
			const Oferta& o = oferte[index.row()];
			return QString::fromStdString(o.to_string_print());
		}
		return QVariant{};
	}

};