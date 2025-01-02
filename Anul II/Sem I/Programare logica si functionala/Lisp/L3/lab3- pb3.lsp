;;;; Problema 3
;;; Sa se construiasca o functie care verifica daca un atom este membru al unei liste
;;;nu neaparat liniare
;;
;; Model matematic:
;;      verifica(l1..ln, e) = { false, n = 0 }
;;                            { true, l1 = e si l1 este atom }
;;                            { verfica(l2..ln,e), l1 != e si l1 este atom }
;;                            {                                        n        
;;                            { t daca t se afla in lista rezultata de U verifica(Li,e) , altfel, unde Li = (l1..ln) }
;;                              fals altfel                           i=1                                                            
;;
;;
;; verifica(L: list, E: atom)
;; L - lista in care cautam atomul e
;; E - atomul de cautat
;;
;;

(defun verifica (L E)
    (cond
        ((null L) nil )
        ((and (atom (car L)) (equal (car L) E)) t)
        ((atom (car L) ) (verifica(cdr L) E) )
        (t (if (membrul (mapcar (lambda (sublist) (verifica sublist E)) L) t) t nil) )
    )
)

;;; Functie ce verifica daca un element apartine unei liste 
;;;liniare
;; Model matematic:
;;      membrul (l1..ln,e) = { false, n = 0}
;;                           { L, l1 = e  }
;;                           { membrul(l2..ln, e), altfel }
;;
;; membrul(L: list, E: element)
;; L - lista in care cautam E
;; E - elementul de cautat
;; return: lista ce incepe cu E daca E e in lista, nil atfel
;;

(defun membrul (L E)
    (cond 
        ((null L) nil )
        ((equal (car L) E) L)
        ( t (membrul (cdr L) E ) )
    )
)