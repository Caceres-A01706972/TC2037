#lang racket

;;Ricardo Andres Caceres Villibord A01706972
;;Jairo Barrera Hernandez A01276795

;;Programacion Funcional 2


;;1. La función duplicate toma una lista lst como entrada
;;   y devuelve una nueva lista en donde cada
;;   elemento de lst está duplicado.
(define duplicate
  (lambda (lista)
    (cond
    [(empty? lista) '()]
    [(append (list (first lista) (first lista)) (duplicate (rest lista)))])))


;;2. La función enlist colo ca dentro de una lista
;;   a cada elemento de la lista que recib e como entrada.
(define enlist
  (lambda (lista)
    (cond
      [(empty? lista) '()]
      [(append (cons (cons(first lista) '()) (enlist (rest lista))))])))


;;3. La función positives toma una lista de números
;;   lst como entrada y devuelve una nueva lista que
;;   solo contiene los números p ositivos de lst.
(define positives
  (lambda (lista)
    (cond
      [(empty? lista) '()]
      [else (cond
              [(empty? lista) '()]
              [(< (first lista) 0) (positives (rest lista))]
              [else (append (list (first lista)) (positives (rest lista)))])])))
              

;;4. La función list-of-symbols? toma una lista lst como entrada.
;;   Devuelve verdadero si to dos los elementos (p osiblemente cero)
;;   contenidos en lst son símb olos, o falso en caso contrario.
(define list-of-symbols?
  (lambda (lista)
    (cond
      [(empty? lista) #t]
      [else (cond
              [(symbol? (car lista)) (list-of-symbols? (cdr lista))]
              [else #f])])))

;;5. La función swapper toma tres entradas: dos valores a y b,
;;   y una lista lst. Devuelve una nueva lista en la que cada
;;   o currencia de a en lst se intercambia p or b, y viceversa.
;;   Cualquier otro elemento de lst p ermanece igual.
;;   Se puede sup oner que lst no contiene listas anidadas.
(define swapper
  (lambda (a b lst)
    (cond
      [(empty? lst) lst]
      [(= a (car lst)) (append (list b) (swapper a b  (cdr lst)))]
      [(= b (car lst)) (append (list a) (swapper a b  (cdr lst)))]
      [else (append (list (car lst)) (swapper a b (cdr lst)))])))

;;6.  La función replic toma dos entradas: una lista lst
;;    y un número entero n, donde n≥0. Devuelve una
;;    nueva lista que replica n veces cada elemento contenido en lst.
(define replic
  (lambda (n lista)
    (cond
      [(empty? lista) '()]
      [else (append (replic-aux (car lista) n) (replic n (cdr lista)))])))

(define replic-aux
  (lambda (n x)
    (cond
      [(= x 0) '()]
      [else (cons n (replic-aux n (- x 1)))])))