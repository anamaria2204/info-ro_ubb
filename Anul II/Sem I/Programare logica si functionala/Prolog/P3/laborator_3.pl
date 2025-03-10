/*
 * Problema 13
 *
 *     "Colorarea hartilor". Se dau n tari. Se cer toate modalitatile de
 *     colorare a celor n tari cu m culori, astfel incat doua tari
 *     vecine sa nu fie colorate la fel.
 *
 */

 /*
 *  Determina initial inversul unei liste, vom folosi un invers_aux care
 *  va stoca intr-o variabila colectoare inversul listei
 *
 *  Model matematic:
 *        invers_aux(l1..ln, Col) = { Col, n = 0 }
 *                                  { invers_aux(l2..ln,l1+Col), altfel }
 *
 *  invers_aux(Col: list, L: list, R: list)
 *  - Col - variabila colectoare
 *  - L - lista initiala, lista de inversat
 *  - R - lista rezultat, inversa listei initiale
 *
 *  Model de flux: (i, i, O)
 *
 */

 invers_aux(Col, [], Col).
 invers_aux(Col, [H|T], R):- invers_aux([H|Col], T, R).

/*
 *  Determinam acum inversul listei folosind invers_aux
 *
 *  Model matematic:
 *    invers(l1..ln) = invers_aux(l1..ln,[])
 *
 *  invers(L: list, Rez: list)
 *  L - lista initiala
 *  Rez - lista rezultata, cu lista initiala inversata
 *
 *  Model de flux: (i, o)
 *
 */
 invers(L, Rez):- invers_aux([], L, Rez).

 /*
  *  Contstruim lista de culori, de la un m dat, formam o lista de
  *  culori de la 1 la m.
  *
  *  Model matematic:
  *    genereaza_culori_rec(m) = { [], m = 0 }
  *                              { m + genereaza_culori(m-1), m > 0 }
  *
  *  genereaza_culori_rec(M: Integer, R: list)
  *    M - numarul de culori de generat
  *    R - lista rezultat, lista de culori
  *  Model de flux: (i,o) determinist
  *
  */
 genereaza_culori_rec(0,[]).
 genereaza_culori_rec(M,[M|R]):- M > 0, M1 is M - 1, genereaza_culori_rec(M1, R).

/*
 * Predicatul principal de a forma lista de culori
 *
 * Model matematic:
 *   genereaza_culori(m) = invers(genereaza_culori_rec(m))
 *
 * genereaza_culori(M: integer, R:list)
 *   M - numarul de culori de generat
 *   R - lista de culori
 * Model de flux: (i,o)
 *
 */
genereaza_culori(M,R):- genereaza_culori_rec(M, L),
                        invers(L,R).

/*
 * Generam recursiv lista de tari de la 1 la n, n fiind dat, lista va
 * fi de forma, n(tara)-_(culoarea tarii)
 *
 * Model matematic:
 *
 *  genereaza_tari_rec(n) = { [], n = 0 }
 *                          { n + genereaza_tari_rec(n-1), n > 0 }
 *
 *  genereaza_tari_rec(N : integer, R: list)
 *    N - numarul de tari de generat
 *    R - lista tarilor
 *  Model de flux: (i, o) determinist
 *
 */
 genereaza_tari_rec(0,[]).
 genereaza_tari_rec(N,[N|R]):- N > 0, N1 is N - 1, genereaza_tari_rec(N1, R).

/*
 *  Predicatul principal de generare a tarilor
 *
 *  Model matematic:
 *    genereaza_tari(n) = invers(genereaza_tari_rec(n))
 *
 * genereaza_tari(N:Integer, R: list)
 *  N - numarul de tari de generat
 *  R - lista rezultat
 * Model de flux: (i,o) determinist
 *
 */
genereaza_tari(N,R):- genereaza_tari_rec(N, L),
                      invers(L, R).

/*
 *  Predicatul member verifica daca un element apartine unei liste
 *
 *  Model matematic:
 *   member(l1..ln) =
 *     1. l1, l != 0
 *     2. member(l2..ln), altfel
 *
 *  member(L: list, X: Integer)
 *  Model de flux(i,o) nedeterminist
 *
 */
membru([E|_],E).
membru([_|T],E):- membru(T,E).

/*
 *  Verificam daca doua tari adiacente au culori diferite
 *
 *  Model matematic:
 *   culori_diferite(T1,culoare1, T2,culoare2, l1..ln) =
 *      1. member(l1..ln, (T1,T2)), culoare1 != culoare2
 *      2. member(l1..ln, (T2,T1)), culoare1 != culoare2
 *
 *  culori_diferite(T1,culoare1: pair, T2,culoare2: pair, Adj - list)
 *     T1,culoare1 - prima pereche de tara si culoare de verificat
 *     T2,culoare2 - a doua pereche de tara si culoare de verificat
 *     Adj - lista de adiacenta a tarilor
 *
 * Model de flux: (i, i, i), nedeterminist oferit de predicatul membru
 *
 */

 culori_diferite(Adj, [T1,C1], [T2,C2]) :-
     (membru(Adj, (T1, T2)); membru(Adj, (T2, T1))) -> C1 \= C2; true.
/*
 * Verifcam daca o culoare aleasa pentru o tara este valida, nu este
 * adiacenta cu o alta tara cu aceasi culoare
 *
 * este_valid(T1,C1, l1..ln, p1..pm) =
 *        1. true, n = 0
 *        2. este_valid(T1,C1, l2..ln, p1..pm), n > 0, (l1 pair)
 *              culori_diferite(T1,C1,l1, p1..pm) = true
 *
 *  este_valid(T1,C1: pair, L: list, Adj : list)
 *     T1,C1 - perechea de tara culoare de verificat
 *     L - lista de perechi tara, culoare existente
 *     Adj - lista de adiacenta a tarilor
 *
 *  Model de flux: (i, i, i) nedeterminist
 */

este_valid(_, [], _).
este_valid([Tara, Culoare], [[TaraVecina, CuloareVecina] | Rest], Adj) :-
    culori_diferite(Adj,[Tara, Culoare], [TaraVecina, CuloareVecina]),
    este_valid([Tara, Culoare], Rest, Adj).
/*
 * Construim predicatul colorare care atribuie fiecarei tari o culoare
 *
 * colorare(t1..tn, c1..cm, a1..ap)=
 *  1. [], n =0
 *  2. t1,c1 + colorare(t2..tn, c1..cm, a1...ap), n > 0,
 *            membru(c1...cm), este_valid(t1,c1, [t1,c1], a1..ap) = true
 *
 * colorare(T: list, C: list, Adj: list, R: list)
 *     T - lista tarilor
 *     C - lista culorilor
 *     Adj - lista de adiacenta a tarilor
 *     R - lista rezultat, cu posibilitatile de colorare
 *
 * Model de flux: (i, i, i, o) nedeterminist oferit de predicatul member
 *
 */

colorare([], _, _, []).
colorare([Tara|T], Culori, Adj,[[Tara, Culoare] | Rez]):-
     membru(Culori, Culoare),
     colorare(T, Culori, Adj, Rez),
     este_valid([Tara,Culoare], Rez, Adj).
/*
 *
 *   Predicatul de colorare a tarilor
 *
 *   Model matematic :
 *     colorare_tari(N,M,Adj) =
 *        1. colorare(genereaza_tari(N), genereaza_culori(M), Adj)
 *
 *   colorare_tari(N: integer, M: integer, Adj: list, R: list)
 *       N - numarul de tari
 *       M - numarul de culori
 *       Adj - lista de adiacenta a tarilor
 *       R - lista rezultat
 *
 *   Model de flux : (i, i, i, o) nedeterminist
 */
colorare_tari(N, M, Adiacente, Configuratie) :-
    genereaza_tari(N, Tari),
    genereaza_culori(M, Culori),
    colorare(Tari, Culori, Adiacente, Configuratie).














