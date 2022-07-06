#lang racket

(define lst '(1 2 3 4 5 6 7 8 9 10))

(define even
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [(= (remainder (first lst) 2) 0) (cons (first lst) (even (rest lst)))]
      [else (even (rest lst))])))

(define odd
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [(= (remainder (first lst) 2) 1) (cons (first lst) (odd (rest lst)))]
      [else (odd (rest lst))])))

(define ugly-numbers
  (lambda (lst)
    (cond
      [(empty? lst) '()]
       [(or(= (remainder (first lst) 2) 0)
           (= (remainder (first lst) 3) 0)
           (= (remainder (first lst) 5) 0)) (cons (first lst) (ugly-numbers (rest lst)))]
      [else (even (rest lst))])))

(define even?
  (lambda (n)
    (= (remainder n 2)0)))

(define odd?
  (lambda (n)
    (= (remainder n 2)1)))

(define ugly-number?
  (lambda (n)
    (or(= (remainder n 2)0)
       (= (remainder n 3)0)
       (= (remainder n 5)0))))

(define redux
  (lambda (pred? lst)
    (cond
      [(empty? lst) '()]
      [(pred? (first lst)) (cons (first lst) (redux pred? (rest lst)))]
      [else (redux pred? (rest lst))])))


(define mult2
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [else (cons (* 2 (first lst)) (mult2 (rest lst)))])))
(define my-map
  (lambda (fn lst)
    (cond
      [(empty? lst) '()]
      [else (cons (fn (first lst)) (my-map fn (rest lst)))])))

;;QuickSort
(define quick2
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [else (append
             (quick2 (filter (lambda (n) (< n (first lst))) lst)) ;; menores => list
             (cons (first lst) '())
            (quick2 (filter (lambda (n) (> n (first lst))) lst)) ;; mayores o iguales
            )])))

(define depth-list
  '( (1 2 3) 4 (5 (6 7 (8 9))) 10 (11) (12)))

(define sum-deep-list
  (lambda (lst)
    (cond
      [(empty? lst) 0]
      [(list? (first lst)) (+ (sum-deep-list (first lst))
                              (sum-deep-list (rest lst)))]
      [(+ (first lst)
          (sum-deep-list (rest lst)))])))

(define search-depth-list
  (lambda (key lst)
    (cond
      [(empty? lst) #f]
      [(list? (first lst)) (or (search-depth-list key (first lst))
                               (search-depth-list key (rest lst)))]
      [(eq? key (first lst)) #t]
      [else (search-depth-list key (rest lst))])))

(define redux-depth-list
  (lambda (pred? lst)
    (cond
      [(empty? lst) '()]
      [(list? (first lst)) (cons (redux-depth-list pred? (first lst))
                                 (redux-depth-list pred? (rest lst)))]
      [else
       (cond
         [(pred? (first lst)) (cons (first lst) (redux-depth-list pred? (rest lst)))]
         [else (redux-depth-list pred? (rest lst))])])))

(define map-depth-list
  (lambda (fn lst)
    (cond
      [(empty? lst) '()]
      [(list? (first lst)) (cons (map-depth-list fn (first lst))
                                 (map-depth-list fn (rest lst)))]
      [else (cons (fn (first lst))
                  (map-depth-list fn (rest lst)))])))

(define bst-tree
  '(50 (25
        (12 () ())
        (35
         (30 () ())
         (40 () ())))
       (75
        (60
         (55 () ())
         (68
          ()
          (70 () ())))
        (85 () ()))))

(define parent
  (lambda (tree)
    (car tree)))

(define left
  (lambda (tree)
    (cadr tree))) ;; (car (cdr tree))

(define right
  (lambda (tree)
    (caddr tree))) ;; (car (cdr (cdr tree)))

(define leaf?
  (lambda (tree)
    (or (null? tree)
        (and (not (list? (car tree)))
         (null? (left tree))
         (null? (right tree))))))

(define depth
  (lambda (tree)
    (cond
      [(leaf? tree) 0]
      [else (+ 1
               (max (depth (left tree))
                    (depth (right tree))))])))

(define post-order
  (lambda (tree)
    (cond
      [(null? tree) '()]
      [else (append (post-order (left tree))
                    (post-order (right tree))
                    (cons (parent tree) '()))])))

(define sum-tree
  (lambda (tree)
    (cond
      [(null? tree) 0]
      [else (+ (parent tree)
               (sum-tree (left tree))
               (sum-tree (right tree)))])))






