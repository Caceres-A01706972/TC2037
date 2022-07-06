#lang racket
;;sum-of-squares: number number => number
(define sum-of-squares
  (lambda (n m)
    (+ (* n n) (* m m))))

;;(sum-of-squares 2 3)

;;area-of-circle: number => number
(define area-of-circle
  (lambda (radio)
    (* 3.141592 radio radio)))

;;(area-of-circle 10)

;; area-of-disk: number number => number
(define area-of-disk
  (lambda (outer inner)
    (- (area-of-circle outer)
       (area-of-circle inner))))

;;(area-of-disk 10 1)

(define fn
  (lambda (x)
    (lambda (y)
      (+ x y))))

;;(define gn (fn 10)) esto me va a permitir cargar a x con el valor de 10
;;ahora si yo digo (gn 5), va a darme 15 porque x ya tenia 10 y le estoy dando 5 a y



;; wage: number number => number
(define wage
  (lambda (payment hours)
    (* payment hours)))
;; tax: number number => number
(define tax
  (lambda (wage rate)
    (* wage rate)))
;; netpay: number number => number
(define netpay
  (lambda (payment hours rate)
    (- (wage payment hours)
       (tax (wage payment hours) rate))))


;;cual es el mayor entre dos numeros
;; max2: number number => number 
(define max2
  (lambda (a b)
    (cond
      [(> a b) a]
      [else b])))


(define interest-rate
  (lambda (amount)
    (cond
      [(<= amount 1000) 0.04]
      [(<= amount 5000) 0.045]
      [else 0.05])))










