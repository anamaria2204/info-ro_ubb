#include "domeniu.h"
#include "repo.h"
#include "service.h"
#include "ui.h"
#include "teste.h"
#include "petGUI.h"

#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <crtdbg.h>
#include <qapplication.h>

using namespace std;

int main(int argc, char *argv[])
{
    testAll();

    QApplication a(argc, argv);
    
    vector<Oferta> vector;

    //OfertaRepo repo;
    RepoFile repo("oferte.txt");

    OfertaValidator valid;
    Wishlist list;
    OfertaService serv{ repo, valid, list };
    AppGUI gui{ serv };
    gui.show();

    return a.exec();
}
