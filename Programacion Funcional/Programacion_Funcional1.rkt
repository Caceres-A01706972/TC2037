#lang racket

;;Ricardo Andres Caceres Villibord A01706972
;;Andres Magaña Perez A01067963

;;file:///C:/Users/Ricardo%20Caceres/Downloads/Programación%20funcional%201.pdf

;;EJERCICIO 1
(define fahrenheit-to-celsius
  (lambda (F)
         (/ (* (- F 32) 5) 9)))

(fahrenheit-to-celsius 212.0)
(fahrenheit-to-celsius 32.0)
(fahrenheit-to-celsius -40.0)

(newline)
(newline)
(newline)

;;EJERCICIO 2
(define sign
  (lambda (n)
    (cond
      [(< n 0) -1]
      [(> n 0) 1]
      [else 0])))
(sign -5)
(sign 10)
(sign 0)

(newline)
(newline)
(newline)

;;EJERCICIO 3
(define roots
  (lambda (a b c)
    (/ (+ (sqrt(- (* b b) (* 4 a c))) (* b -1)) (* 2 a))))

(roots 2 4 2)
(roots 1 0 0)
(roots 4 5 1)

(newline)
(newline)
(newline)

;;EJERCICIO 4
(define calculoBMI
  (lambda (weight height)
    (/ weight (* height height))))

(define BMI
  (lambda (weight height)
    (cond
      [(< (calculoBMI weight height) 20) "underweight"]
      [(and(>= (calculoBMI weight height) 20) (< (calculoBMI weight height) 25)) "normal"]
      [(and(>= (calculoBMI weight height) 25) (< (calculoBMI weight height) 30)) "obese1"]
      [(and(>= (calculoBMI weight height) 30) (< (calculoBMI weight height) 40)) "obese2"]
      [(>= (calculoBMI weight height) 40) "obese3"])))

(BMI 45 1.7)
(BMI 55 1.5)
(BMI 76 1.7)
(BMI 81 1.6)
(BMI 120 1.6)