#include <stdio.h>
#include "ui.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>

int main() {
	testAll();
	//run();

	if (_CrtDumpMemoryLeaks())
		printf("\nMEMORY LEAKS\n");

	return 0;
}
