#ifndef MYVECTOR_H_
#define MYVECTOR_H_
#include "domeniu.h"

#define initial_cap 2;

template <typename TElem>
class IteratorVector;

template <typename TElem>
class VectorDinamic {
private:

	TElem* elemente; // vectorul
	int size;
	int capacitate;
	void redimensionare();

public:

	//Constructor.
	VectorDinamic();

	//Destructor.
	~VectorDinamic();

	//Constructor de copiere.
	VectorDinamic(const VectorDinamic& ot);


	/** operator assignment */
	VectorDinamic& operator=(const VectorDinamic& ot);

	/**
	 Move constructor
	 Apelat daca construim un nou vector dintr-un r-value (ex temporary, expresie de la return)
	 Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
	*/
	VectorDinamic(VectorDinamic&& ot) noexcept;

	/**
	Move assignment
	Similar cu move constructor
	Folosit la assignment
	*/
	VectorDinamic& operator=(VectorDinamic&& ot) noexcept;

	//Adaugare in vector.
	void push_back(const TElem& el);

	TElem& operator[](int poz) const;

	int getSize() const noexcept;

	bool empty() const noexcept;

	/*
		*modifica informatiile unui element
		* @param position pozitia elementului ce urmeaza a fi modificat
		* @param new_price noul pret al elementului
		* @param new_subst noua substanta activa a elementului
	*/
	void modifica_element(int position, int new_price, const string & new_subst);

	void erase(int poz);

	friend class IteratorVector<TElem>;

	IteratorVector<TElem> begin() const;

	IteratorVector<TElem> end() const;

	IteratorVector<TElem> iterator() {
		return IteratorVector(*this);
	}
};

template <typename TElem>
VectorDinamic<TElem>::VectorDinamic() {
	this->size = 0;
	this->capacitate = 2;
	this->elemente = new TElem[2];
}

template <typename TElem>
VectorDinamic<TElem>::~VectorDinamic() {
	delete[] this->elemente;
}

template <typename TElem>
VectorDinamic<TElem>::VectorDinamic(const VectorDinamic& ot) {
	this->elemente = new TElem[ot.capacitate];
	for (int i = 0; i < ot.size; i++) {
		this->elemente[i] = ot.elemente[i];
	}
	this->size = ot.size;
	this->capacitate = ot.capacitate;
}

template <typename TElem>
void VectorDinamic<TElem>::erase(int poz) {
	this->size--;
	for (int i = poz; i < this->size; i++) {
		this->elemente[i] = this->elemente[i + 1];
	}
}

template <typename TElem>
void VectorDinamic<TElem>::redimensionare() {
	capacitate *= 2;
	auto* nou = new TElem[capacitate];
	for (int i = 0; i < size; i++) {
		nou[i] = elemente[i];
	}
	delete[] elemente;
	elemente = nou;
}

template <typename TElem>
void VectorDinamic<TElem>::push_back(const TElem& e) {
	if (size == capacitate) {
		redimensionare();
	}
	elemente[size++] = e;
}

template<typename TElem>
VectorDinamic<TElem>& VectorDinamic<TElem>::operator=(const VectorDinamic<TElem>& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] this->elemente;
	// Copy the data pointer from other
	this->elemente = ot.elemente;
	this->size = ot.size;
	this->capacitate = ot.capacitate;

	// Release the data pointer from the source object so that
	// the destructor does not free the memory multiple times.
	ot.elemente = nullptr;
	ot.size = 0;
	ot.capacitate = 0;
	return *this;
}

template <typename ElementType>
VectorDinamic<ElementType>::VectorDinamic(VectorDinamic&& ot) noexcept {
	// Copy the data pointer from other
	this->elemente = ot.elemente;
	this->size = ot.size;
	this->capacitate = ot.capacitate;

	// Release the data pointer from the source object so that
	// the destructor does not free the memory multiple times.
	ot.elemente = nullptr;
	ot.size = 0;
	ot.capacitate = 0;
}

/*
Move assignment
Similar cu move constructor
Folosit la assignment
Elibereaza ce continea obiectul curent (this)
"fura" interiorul lui ot
pregateste ot pentru distrugere
*/
template <typename ElementType>
VectorDinamic<ElementType>& VectorDinamic<ElementType>::operator=(VectorDinamic&& ot) noexcept {
	if (this == &ot) {
		return *this;
	}
	delete[] this->elemente;
	// Copy the data pointer from other
	this->elemente = ot.elemente;
	this->size = ot.size;
	this->capacitate = ot.capacitate;

	// Release the data pointer from the source object so that
	// the destructor does not free the memory multiple times.
	ot.elemente = nullptr;
	ot.size = 0;
	ot.capacitate = 0;
	return *this;
}

template <typename TElem>
TElem& VectorDinamic<TElem>::operator[](int poz) const {
	return elemente[poz];
}

template <typename TElem>
int VectorDinamic<TElem>::getSize() const noexcept {
	return size;
}

template <typename TElem>
bool VectorDinamic<TElem>::empty() const noexcept {
	return size == 0;
}

template <typename TElem>
IteratorVector<TElem> VectorDinamic<TElem>::begin() const {
	return IteratorVector<TElem>(*this);
}

template <typename TElem>
IteratorVector<TElem> VectorDinamic<TElem>::end() const {
	return IteratorVector<TElem>(*this, size);
}

template <typename TElem>
class IteratorVector {
private:

	const VectorDinamic<TElem>& vector; // referinta la vectorul dinamic
	int poz = 0; //Setam prima pozitie la 0.

public:

	explicit IteratorVector(const VectorDinamic<TElem>& v);
	IteratorVector(const VectorDinamic<TElem>& v, int poz) noexcept;

	bool valid() const;
	TElem& element() const;
	void next();
	TElem& operator*();
	IteratorVector& operator++();
	bool operator==(const IteratorVector& ot) noexcept;
	bool operator!=(const IteratorVector& ot) noexcept;
};

template <typename TElem>
IteratorVector<TElem>::IteratorVector(const VectorDinamic<TElem>& v) : vector(v) {}

template <typename TElem>
IteratorVector<TElem>::IteratorVector(const VectorDinamic<TElem>& v, int poz) noexcept : vector{ v }, poz{ poz } {}

template <typename TElem>
bool IteratorVector<TElem>::valid() const {
	return poz < vector.getSize();
}

template <typename TElem>
TElem& IteratorVector<TElem>::element() const {
	return vector.elemente[poz];
}

template <typename TElem>
void IteratorVector<TElem>::next() {
	poz++;
}

template <typename TElem>
TElem& IteratorVector<TElem>::operator*() {
	return element();
}

template <typename TElem>
IteratorVector<TElem>& IteratorVector<TElem>::operator++() {
	next();
	return *this;
}

template <typename TElem>
bool IteratorVector<TElem>::operator==(const IteratorVector<TElem>& ot) noexcept {
	return ot.poz == poz;
}

template <typename TElem>
bool IteratorVector<TElem>::operator!=(const IteratorVector<TElem>& ot) noexcept {
	return !(*this == ot);
}

#endif // !MYVECOTR_H_
