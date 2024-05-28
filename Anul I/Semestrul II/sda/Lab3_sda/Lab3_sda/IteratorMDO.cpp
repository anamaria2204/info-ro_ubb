#include "IteratorMDO.h"
#include "MDO.h"
#include <exception>
#include <stdexcept>


//complexitate: theta(1)
IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
	this->curent = nullptr;
}

//complexitate: theta(1)
void IteratorMDO::prim() {
	this->curent = dict.prim->urmator;
}

//complexitate: theta(1)
void IteratorMDO::ultim() {
	this->curent = dict.ultim->precedent;
}

//complexitate: theta(1)
void IteratorMDO::urmator() {
	if (dict.vid())
		throw exception();
	if (this->curent == nullptr) {
		this->prim();
		return;
	}
	if (this->curent == dict.ultim)
		throw exception();
	this->curent = this->curent->urmator;
}

//complexitate: theta(1)
void IteratorMDO::precedent() {
	if (dict.vid())
		throw exception();
	if (this->curent == nullptr) {
		this->ultim();
		return;
	}
	if (this->curent == dict.prim)
		throw exception();
	this->curent = this->curent->precedent;
}

//complexitate: theta(1)
bool IteratorMDO::valid() const {
	return (dict.dim() && this->curent != dict.ultim && this->curent != dict.prim);
}

//complexitate: theta(1)
TElem IteratorMDO::element() {
	if (dict.vid())
		throw exception();
	if (this->curent == nullptr) {
		this->prim();
		return this->curent->elem;
	}
	if (dict.vid() && this->curent == dict.ultim)
		throw exception();
	return this->curent->elem;
}
//complexitate 
// best case theta(1) 
// worst case theta(k) 
// average case theta(k)
void IteratorMDO::revinoKpasi(int k) {
	if (dict.vid())
		throw exception();
	if (this->curent == nullptr) {
		this->ultim();
		return;
	}
	if (curent == dict.prim)
		throw exception();
	while (k != 0) {
		this->curent = this->curent->precedent;
		k--;
	}
}


