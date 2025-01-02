;;;; Problema 7
;;; a) Sa se scrie o functie care testeaza data o lista
;;; este liniara
;; 
;; Model matematic:
;; testeaza(l1..ln) = { true, n = 0 }
;;                    { nil, l1 este lista }
;;                    { testeaza(l1..ln), altfel }
;; testeaza(L: list)
;; L - lista de verificat
;;
;; Returneaza T - lista este liniara, NIL altfel
;;
; Teste:
; (testeaza '(1 2 3 4) ) => T
; (testeaza '(1 2 (3) 4 )) => NIL

(defun testeaza(L)
    (cond
        ((null L) T )
        ((listp(car L )) NIL)
        ( T (testeaza(cdr L) ) )
    )
)

;;; b) Definiti o functie care substituie prima aparitie a
;;; unui element intr-o lista data

;; Prima data vom extrage ultimul element din lista
;;
;; Model matematic:
;; ultim(l1.. ln) = { l1, n = 1 }
;;                  { ultim(l2..ln), altfel }
;;
;; ultim(L: list)
;; L -lista din care vom extrage ultimul element
;;
;; Returneaza l - ultimul element din lista, NIL daca lista este vida 
;;
; Teste:
; (ultim '(1 2 3 (4 5) (6) ) ) => 6
; (ultim '(1 2 3 4 (a) ( b (f) ) ) ) => f

(defun ultim(L)
    (cond
		((and (null (cdr l)) (listp (car l))) (ultim (car l)))
		((and (null (cdr l)) (atom (cdr l))) (car l))
		(t (ultim (cdr l)))
    )
)

;; Vom inlocui prima aparitie a unui element dat intr-o 
;; lista data cu ultimul element al listei

;; Model matematic:
;; inlocuieste(l1..ln E F) = { nil , n = 0 }
;;                           { l1 + sub(l2..ln e 0 ), l1 != e, f = 0 }
;;                           { E + sub(l2..ln e 1 ), l1 = e, f = 1 }
;;                           { l1 + sub(l2..ln e 1), f = 1 }

;; inlocuieste(L: list E: Integer F: Integer )
;; L -lista in care inlocuim elementul dorit
;; E - elementul de inlocuit
;; F - indicator pentru a marca faptul ca am schimbat prima aparitie
;;     a elementului E in lista L
;
;Teste:
; (inlocuieste_aux '(1 2 3 4 8) 3 0) => (1 2 8 4 8)

(defun inlocuieste_aux(L E F)
    (cond
        ((null L) nil )
        ((and (null (equal (car L) E ) ) (= F 0) ) (cons (car L ) (inlocuieste_aux (cdr L) E 0 )))
        ((and (equal (car L) E) (= F 0) ) (append (list (ultim L )) (inlocuieste_aux (cdr L) E 1 )))
        ((= F  1) (cons (car L ) (inlocuieste_aux (cdr L) E 1) ))
    )
)

;; Functia principala de inlocuire
;; Model matematic:
;; inlocuieste ( L, e) = { inlocuieste_aux(L, e, 0) }
;;
;;
; Teste:
; (inlocuieste '(1 2 3 4 5) 3) => (1 2 5 4 5)

(defun inlocuieste(L E)
    (inlocuieste_aux L E 0 )
)

;;;c) Sa se inlocuiasca fiecare sublista a unei liste cu ultimul ei element. 
;;;  Prin sublista se intelege elemet de pe primul nivel, care este lista

;; Model matematic:
;; inlocuieste_list(l1..ln) = { nil, n = 0 }
;;                            { ultim(c1..cn) + inlocuieste_list(l2..ln) , l1 este lista, notez cu c1..cn - lista l1 }
;;                            { l1 + inlocuieste_list(l2..ln), altfel }

;; inlocuieste_list(L: list)
;; L - lista pe care modificam
;;

; Test:
; (inlocuieste_list '(a (b c) (d (e (f))))) => (a c f)

(defun inlocuieste_list(L)
    (cond
        ((null L ) nil )
        ((listp (car L )) (append (list (ultim (car L))) (inlocuieste_list (cdr L))) )
        ( T (cons (car L ) (inlocuieste_list (cdr L )) ))
    )
) 

;;; d) Definiti o functie care interclaseaza fara pastrarea dublurilor doua liste liniare sortate

;;Model matematic:
;; interclaseaza(l1..ln, p1..pm) = { l1..ln, m = 0 }
;;                                 { p1..pm, n = 0 }
;;                                 { l1 + interclaseaza (l2..ln, p1..pm), l1 < p1 }
;;                                 { p1 + interclaseaza (l1..ln, p2..pm), l1 > p1 }
;;                                 { l1 + interclaseaza (l2..ln, p2..pm), altfel (l1 = p1) }

;; interclaseaza (A: list, B: list)
;; A - lista 1 liniara sortata
;; B - lista 2 liniara sortata

;Teste:
; (interclaseaza '(1 2 3 4 5) '(2 7 4 6 8)) => (1 2 3 4 5 6 7 8)

(defun interclaseaza(A B)
    (cond
        ( (null A) B )
        ( (null B) A )
        ( ( < (car A) (car B) ) (cons (car A) ( interclaseaza (cdr A) B ) ) )
        ( ( > (car A) (car B ) ) (cons (car B) ( interclaseaza A (cdr B ) ) ) )
        ( T (cons (car A) ( interclaseaza (cdr A ) (cdr B) ) ) )
    )
)