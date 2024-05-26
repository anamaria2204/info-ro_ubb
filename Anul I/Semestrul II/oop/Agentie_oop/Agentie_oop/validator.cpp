#include "validator.h"
#include <assert.h>
#include <sstream>

void OfertaValidator::valideaza(const Oferta& o) {
	vector<string> msgs;
	if (o.get_denumire().size() == 0) msgs.push_back("Denumire vida!");
	if (o.get_destinatie().size() == 0) msgs.push_back("Destinatie vida!");
	if (o.get_tip().size() == 0) msgs.push_back("Tip vid!");
	if (o.get_pret() < 0) msgs.push_back("Pret negativ!");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}