/* 1a
 *
 * Sa se scrie un predicat care intoarce diferenta a doua multimi
 *
 *  Verificam daca un element apartine multimii
 *
 *  este_in_multime(X,l1..ln) = { false, n = 0 }
 *                              { true, n = 1 si l1 = X}
 *                              { este_in_multime(l2..ln, X), altfel }
 *  este_in_multime(X,L)
 *  X : intreg dat
 *  L : lista de numere intregi data
 *
 *  Model de flux: (i,i)
 *
 */

este_in_multime(X,[X|_]):- !.
este_in_multime(X,[_|L]) :- este_in_multime(X,L).

go1:- este_in_multime(1,[1,2,4]). %true
go2:- este_in_multime(2,[1,3,4,5]).   %false

/*
 *  Diferenta a doua multimi
 *
 *  dif(l1..ln, d1..dn) = { [] , n = 0}
 *                        { dif(l2..ln,d1..dn),
 *                         este_in_multime(l1,d1..dn)}
 *                        { l1 + dif(l2..ln, d1..dn), altfel}
 *
 *  dif(L1, L2, R)
 *  L1 : lista de numere intregi data
 *  L2 : lista de numere intregi data
 *  R : lista rezultata dupa scadere
 *
 *
 *  Model de flux: (i, i, o)
 *
 */

dif([],_,[]):- !.
dif([H|T],L, R):- este_in_multime(H,L), !, dif(T,L,R).
dif([H|T],L,R):- dif(T,L,R1),R =[H|R1].

go3:- dif([1,2,3],[1,2],R), R=[3].   %true
go4:- dif([1,2,3],[1,2,3],R), R=[].  %true
go5:- dif([1,2,3],[4,5,6],R), R=[1,2,3].  %true

/*
 * 1b
 *
 * Sa se scrie un predicat care adauga intr-o lista dupa fiecare element
 * par valoarea 1.
 *
 *  adauga(l1..ln) = { [], n = 0 }
 *                   { [l1,1] + adauga(l2..ln), l1 este par }
 *                   { l1 + adauga(l2..ln), altfel }
 *
 *  adauga(L,R)
 *  L : lista de numere intregi data
 *  R : lista de numere intregi rezultata dupa inserarea nr 1 dupa
 *  elementele pare
 *
 *  Model de flux: (i,o)
 *
 */

adauga([],[]):- !.
adauga([H|T],R):- H mod 2 =:= 0, !, adauga(T,R1), R = [H,1|R1].
adauga([H|T],R):- adauga(T,R1), R =[H|R1].

go6:- adauga([1,3],R), R=[1,3]. %true
go7:- adauga([2,4],R), R=[2,1,4,1]. %true
go8:- adauga([],R), R=[]. %true
