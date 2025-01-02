;;;; Problema 1
;;; Se da un arbore de tipul (1). Sa se afiseze calea de la radacina pana la un 
;;; nod X dat.

;; functie auxiliara pentru a extrage din reprezentarea arborelui, subarborele stang
;; Model matematic:
;; parcurg_st (l1..ln, nv, nm) = { nil, n = 0 }
;;                               { nil, nv = nm + 1 }
;;                               { l1+l2+ parcurg_st(l3..ln, nv+1, nm+l2), altfel }
;;
;; parcurg_st(L: list, Nv: Integer, Nm: integer
;; L - lista sub care e reprezentat arborele
;; Nv - numarul de varfuri 
;; Nm - numarul de muchii
;;


(defun parcurg_st(L Nv Nm)
    (cond 
        ((null L) nil)
        ((= Nv (+ 1 Nm)) nil)
        ( t (cons (car L) (cons (cadr L) (parcurg_st ( cddr L ) (+ 1 Nv) (+ Nm (cadr L ) )))))
    )
)

;; functie de extragere a subarborelui stang
;; Model matematic:
;; stang(l1 l2 l3..ln) = parcurg_st(l3..ln, 0, 0)
;;
;;stang(L: list)
;; L - lista sub care este reprezentat arborele
;;

(defun stang(L) 
    (parcurg_st (cddr L) 0 0 )
)

;; functie auxiliara de parcurs subarborele drept
;;
;; Model matematic:
;; parcurg_dr(l1..ln, nv, nm) = { nil, n = 0 }
;;                              { L , nv = nm + 1 }
;;                              { parcurg(l3..ln, nv+1, nm+l2), altfel }
;;
;; parcurg_dr(L: list, Nv: Integer, Nm: Integer)
;; L - lista arborelui
;; Nv - numar de varfuri
;; Nm - numar de muchii
;;

(defun parcurg_dr(L Nv Nm) 
    (cond
        ((null L) nil)
        ( (= Nv (+ 1 Nm) ) L)
        ( t ( parcurg_dr (cddr L) (+ 1 Nv ) (+ Nm (cadr L) ) ) )
    )
)

;;functia principala de extragere a subarborelui drept
;;
;;Model matematic:
;; drept(l1 l2 l3.. ln) = parcurg_dr(l3..ln, 0, 0)
;;
;; drept(L: list)
;; L - lista arborelui
;;

(defun drept(L)
    (parcurg_dr (cddr L) 0 0 ) 
)

;; functie auxiliara de gasire a drumul de la radacina la un 
;; nod X dat
;;
;;Model matematic:
;; drum_aux(l1..ln, x, col) =
;;      { nil, n = 0 }
;;      { x+col, l1 = x }
;;      { drum_aux(stang(L) l1+col) 
;;              sau                     , l2 > 0 
;;        drum_aux(drept(L) l1+col) }
;;
;; drum_aux(L: list, X: integer, Col: list)
;; L - lista arborelui
;; X - nodul la care dorim sa ajungem
;; col - lista ce conctien calea de la nodul radacina la X
;;       in ordine inversa (nod - radacina) 

(defun drum_aux (L X Col)
    (cond
        ((null L ) nil )
        ((equal (car L) X ) (cons X Col) )
        ((> (cadr L ) 0 )
            (or
            (drum_aux (stang L) X  (cons (car L) Col))
            (drum_aux (drept L) X (cons (car L) Col))
            )
        )
    )
)

;; functie auxiliara de inversare a unei liste
;;
;;Model matematic:
;; invers_aux(l1..ln , Col) = { Col, n = 0 }
;;                            { invers_aux(l2..ln, l1+Col), altfel }
;;
;; invers_aux (L: list, Col: list)
;;  L - lista de inversta
;;  Col - lista inversata

(defun invers_aux(L Col)
    (cond 
        ((null L) Col)
        (t (invers_aux(cdr L) (cons (car L) Col )))
    )
)


;; functie principala de inversare a listei
;; 
;; Model matematic:
;; invers(L) = invers_aux(L, nil)
;;
;; invers(L: list)
;; L - lista de inversat

(defun invers(L)
    (invers_aux L nil )
)

;; functia principala de gasire a drumul de la radacina la un 
;; nod X dat
;;
;; Model matematic:
;; drum(L, X) = invers(drum_aux(L, X, nil))
;;
;; drum(L: list, X: integer)
;; L - lista arborelui
;; X - nodul la care trebuie sa ajungem
;;

(defun drum(L X)
    (invers (drum_aux L X nil ) )
)


;(drum '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) 'e) => a d e 


;(drum '(a 2 b 1 h 1 i 1 y 0 c 2 d 2 f 1 k 0 g 0 e 0) 'f) => a c d f
;(drum '(a 2 b 1 h 1 i 1 y 0 c 2 d 2 f 1 k 0 g 0 e 0) 'y) => a b h i y



