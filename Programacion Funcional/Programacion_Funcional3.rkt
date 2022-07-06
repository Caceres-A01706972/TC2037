#lang racket

;;Ricardo Andres Caceres Villibord A01706972
;; Rodrigo Gomez Quiroz

;;Programacion_Funcional3

;; 1.La función insert toma dos entradas:
;; un número n y una lista lst que contiene
;; números en orden ascendente. Devuelve una
;; nueva lista con los mismos elementos de lst
;; pero con n insertado en su lugar correspondiente.
(define insert
  (lambda (num lista)
    (cond
      [(empty? lista) (append (list num))]
      [(>= (car lista) num) (cons num lista)]
      [else (cons (car lista)(insert num (cdr lista)))])))


;; 2. La función insertion-sort toma una lista desordenada
;; de números como entrada y devuelve una nueva lista con los
;; mismos elementos p ero en orden ascendente. Se debe usar
;; la función insert denida en el ejercicio anterior para
;; escribir insertion-sort. No se debe utilizar la función
;; sort o alguna similar predefinida.
(define insertion-sort
  (lambda (lista)
    (cond
      [(empty? lista) '()]
      [else (insert (car lista) (insertion-sort (cdr lista)))])))


;; 3. La función deep-reverse toma una lista como entrada.
;; Devuelve una lista con los mismos elementos que su entrada pero en
;; orden inverso. Si hay listas anidadas, estas también deben invertirse.
 (define (deep-reverse l)
  (map
   (lambda (x)
         (if (list? x)
             (deep-reverse x)
             x)) (reverse l)))

;; 4. La función pack toma una lista lst como entrada. Devuelve
;; una lista de listas que agrupan los elementos iguales consecutivos.
(define (pack lista)
  (define lista-aux (list))
  (define lista-final (list))
  (define (pack-aux lista lista1 lista2)
    (if (empty? lista)
        (reverse lista2)
        (if (= (length lista) 1)
            (if (empty? lista1)
                (pack-aux (cdr lista) (list) (append (list (list (car lista))) lista2))
                (if (eq? (car lista) (car lista1))
                    (pack-aux (cdr lista) (list) (append (list (append (list (car lista)) lista1)) lista2))
                    (pack-aux (cdr lista) (list) (append (list (car lista)) lista2))))
            (if (eq? (car lista) (cadr lista))
                (pack-aux (cdr lista) (append (list (car lista)) lista1) lista2)
                (if (empty? lista1)
                    (pack-aux (cdr lista) (list) (append (list (list (car lista))) lista2))
                    (pack-aux (cdr lista) (list) (append (list (append (list (car lista)) lista1)) lista2)))))))
  (pack-aux lista lista-aux lista-final))
                             
                             
;; 5.La función compress toma una lista lst como entrada. Devuelve
;; una lista en la que los elementos repetidos consecutivos de lst se
;; reemplazan por una sola instancia. El orden de los elementos no debe modicarse.
(define compress
  (lambda (lista)
    (cond
      [(empty? lista) '()]
      [(= (length lista) 1) lista]
      [(eq? (car lista) (cadr lista)) (compress (cdr lista))]
      [else (append (list (car lista))
                    (compress (cdr lista)))])))


;; 6. La función encode toma una lista lst como entrada. Los elementos
;; consecutivos en lst se codifican en listas de la forma (n e), donde
;; n es el número de o currencias del elemento e.
(define (encode lista)
  (define contador 0) 
    (define (encode-aux lista contador)
      (cond
        [(empty? lista) '()]
        [(= (length lista) 1) (list (append (list (+ 1 contador)) lista))]
        [(eq? (car lista) (cadr lista)) (encode-aux (cdr lista) (+ 1 contador))]
        [(append (list (append (list (+ 1 contador)) (list (car lista)))) (encode-aux (cdr lista) 0))]))

  (encode-aux lista contador))

      
    
      


