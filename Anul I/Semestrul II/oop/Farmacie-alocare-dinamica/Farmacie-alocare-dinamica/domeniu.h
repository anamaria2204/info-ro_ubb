#pragma once

typedef struct {
	int cod;
	char* nume;
	int concentratie;
	int cantitate;
} Medicament;

/*
Functia creeaza un medicament
Patrmetrii:
- cod: int > 0
- nume: char diferit de ""
- concentratie: int > 0
- cantitate: int > 0
Return:
pointer catre medicamentul creat
*/

Medicament* creaza(int cod, char* nume, int concentratie, int cantitate);

/*
functia distruge un medicament
dealocam memoria utilizata
*/

void distruge(Medicament* m);

/*
functia valideaza un medicament dat
*/

int valideaza(Medicament* m);


/*
Functia verifica daca doua medicamente au acelasi cod
Parametrii:
- m1: pointer catre medicamentul m1
- m2: pointer catre medicamentul m2

Returneaza:
 1 daca medicamentele au acelasi cod, 0 altfel
*/
int egalCod(Medicament* m1, Medicament* m2);

/*
functia verifica daca doua medicamente sunt identice
Parametrii:
- m1: pointer catre medicamentul m1
- m2: pointer catre medicamentul m2

Return:
 1 daca medicamentele sunt egale, 0 altfel
*/

int egalMedicamente(Medicament* m1, Medicament* m2);

/*
Functia verifica daca doua medicamente au acelasi cod si daca cel de-al
doilea are cantitatea mai mare decat 0
Parametrii:
- m1: pointer catre medicamentul m1
- m2: pointer catre medicamentul m2

Return:
1 daca medicamentele indeplinesc cerintele date, 0 altfel
*/

int egalModifica(Medicament* m1, Medicament* m2);

/*
functia modifica cantitatea unui medicament
Parametrii:
- m1: pointer catre medicamentul m1
- m2: pointer catre medicamentul m2

Return:
medicamentul m1 va avea cantiatea medicamentului m2
*/

void adaugaCantitate(Medicament* m1, Medicament* m2);

/*
* Returneaza codul unui medicament.
*
* Parametri:
* - m: pointer la medicament
*
* Returneaza:
* Codul medicamentului
*/
int returnCod(Medicament* m);

/*
* Verifica daca medicamentul este in stoc.
*
* Parametri:
* - m: pointer la medicament
*
* Returneaza:
* 1 daca medicamentul este in stoc, altfel 0
*/
int verifStoc(Medicament* m);

/*
* Sterge cantitatea unui medicament (seteaza cantitatea la 0).
*
* Parametri:
* - m: pointer la medicament
*/
void stergeCantitate(Medicament* m);

/*
* Compara numele a doua medicamente.
*
* Parametri:
* - m1: pointer la primul medicament
* - m2: pointer la al doilea medicament
*
* Returneaza:
* Un numar negativ daca numele primului medicament este mai mic, 0 daca numele sunt egale,
* si un numar pozitiv daca numele primului medicament este mai mare.
*
*/
int compNume(Medicament* m1, Medicament* m2);

/*
* Compara cantitatea a doua medicamente.
*
* Parametri:
* - m1: pointer la primul medicament
* - m2: pointer la al doilea medicament
*
* Returneaza:
* 1 daca cantitatea primului medicament este mai mare decat a celui de-al doilea, altfel 0
*/
int compCantitate(Medicament* m1, Medicament* m2);

/*
* Filtreaza medicamentele dupa nume.
*
* Parametri:
* - m: pointer la medicamentul care trebuie verificat
* - nume: prima litera a numele dupa care se filtreaza
*
* Returneaza:
* 1 daca prima litera a numelui medicamentului coincide cu litera data, altfel 0
*/
int filtreazaNume(Medicament* m, char nume);

/*
* Filtreaza medicamentele dupa cantitate.
*
* Parametri:
* - m: pointer la medicamentul care trebuie verificat
* - cantitate: valoarea maxima a cantitatii pentru filtrare
*
* Returneaza:
* 1 daca medicamentul are cantitatea mai mica decat valoarea data, altfel 0
*/
int filtrezaCantitate(Medicament* m, int cantitate);

/*
* Copiaza un medicament.
*
* Parametri:
* - m: pointer la medicamentul care trebuie copiat
*
* Returneaza:
* Pointer la o copie a medicamentului dat sau NULL daca alocarea de memorie esueaza.
*/
Medicament* copiazaMedicamente(Medicament* m);
