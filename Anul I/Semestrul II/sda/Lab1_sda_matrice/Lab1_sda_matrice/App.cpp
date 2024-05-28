#include <iostream>
#include "Matrice.h"
#include "TestExtins.h"
#include "TestScurt.h"
#include <assert.h>

using namespace std;

void test_transpusa() {
	Matrice mat = Matrice(3, 4);
	mat.modifica(0, 1, 3);
	mat.modifica(1, 2, 4);
	Matrice transpusa = mat.transpusa();
	assert(transpusa.nrColoane() == 3);
	assert(transpusa.nrLinii() == 4);
	assert(transpusa.element(1, 0) == 3);
	assert(transpusa.element(2, 1) == 4);
}

int main() {

	test_transpusa();
	testAll();
	testAllExtins();

	cout << "End";
}
