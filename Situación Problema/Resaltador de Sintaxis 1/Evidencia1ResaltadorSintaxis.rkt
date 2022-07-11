#lang racket

;; Created By: Ricardo Andrés Cáceres Villbiord A01706972
;; Class: TC2037 Implementación de Métodos Computacionales
;; Date: 07/07/2022 

;; Actividad Integradora: RESALTADOR DE SINTAXIS
;; Github: 

(require 2htdp/batch-io) 

(define archivo "Situación Problema\\Resaltador de Sintaxis 1\\test.txt")

;; The function opens an input file, reads it character by character,
;; returning it in a list of characters.
;; file->list-of-strings: filename => list
(define file->list-of-chars
  (lambda (filename)
    (flatten
     (map string->list
          (read-1strings archivo)))))
;; usage example
;(file->list-of-chars archivo)

;; The function converts a list of characters to a list of strings.
;; It is an auxiliary function of the function that appears after,
;; although it can be used independently.
;; list-of-chars->list-of-strings: list list list => list
(define list-of-chars->list-of-strings
  (lambda (loc aux result)
    (cond
      [(empty? loc) result]
      [(char-whitespace? (car loc))
       (list-of-chars->list-of-strings (cdr loc)
                                       '()
                                       (cons
                                        (list->string aux)
                                        result))]
      [(char-punctuation? (car loc))
       (list-of-chars->list-of-strings (cdr loc)
                                       '()
                                       (cons
                                        (list->string
                                         (cons (car loc) '()))
                                        (cons
                                         (list->string aux)
                                         result)))]
      [else
       (list-of-chars->list-of-strings (cdr loc)
                                       (append aux (cons (car loc) '()))
                                       result)])))
;; usage example
;(list-of-chars->list-of-strings (file->list-of-chars archivo) '() '())


;; The function opens an input file, reads it character by character,
;; returning it in a list of string.
;; file->list-of-strings: filename => list
(define file->list-of-strings
  (lambda (filename)
    (reverse
     (list-of-chars->list-of-strings
      (file->list-of-chars archivo) '() '()))))
;(file->list-of-strings archivo)

; list of strings to single string
(define list-of-strings->string
  (lambda (strlst)
    (string-join strlst " ")))
;; usage example
;; (define strlst (file->list-of-strings input-filename))
;; (list-of-strings->string strlst)


(define codigo (file->list-of-strings archivo))

(define file (read-file archivo))
(define file-lt (string-replace file "<" "&lt"))

(define file-gt (string-replace file-lt ">" "&gt"))

(define file-br (string-replace file-gt "\n" " <br> "))


(define is-include?
    (lambda (palabra)
        (cond
            [(empty? palabra) #f]
            [(regexp-match-exact? #rx"#include|#include[ ]*%lt[A-Za-z_0-9]*&gt|&lt[A-Za-z_0-9]*&gt" palabra) #t]
            [else #f])))

(define is-from-language?
    (lambda (palabra)
        (cond
            [(empty? palabra) #f]
            [(regexp-match-exact? #rx"namespace|if|else|for|while|do|switch|case|continue|break|int|float|double|long|string|cin|cout|char|const|void|bool|false|true|static|virtual|new|class|private|public|throw|this|catch|try|return|volatile|extern|union|sizeof|pair|printf|scanf" palabra) #t]
            [else #f])))

(define is-integer?
    (lambda (palabra)
        (cond
            [(empty? palabra) #f]
            [(regexp-match-exact? #rx"[0-9]+;?" palabra) #t]
            [else #f])))

(define is-decimal?
    (lambda (palabra)
        (cond
            [(empty? palabra) #f]
            [(regexp-match-exact? #rx"[0-9]+[.][0-9]+;?" palabra) #t]
            [else #f])))


(define is-cadena?
    (lambda (palabra)
        (cond
            [(empty? palabra) #f]
            [(regexp-match-exact? #rx"\\?*[\"][a-zA-Z_0-9]*" palabra) #t]
            [else #f])))

(define is-operador?
    (lambda (palabra)
        (cond
            [(empty? palabra) #f]
            [(regexp-match-exact? #rx"[+][+]|[-][-]|[*][*]|[+]|[-]|[*]|[/]|[%]|[!]|[=]|[==]|&lt|&gt|&lt{1}|&gt&gt|&lt=|&gt=" palabra) #t]
            [else #f])))

(define is-identificador?
    (lambda (palabra)
        (cond
            [(empty? palabra) #f]
            [(regexp-match-exact? #rx"[a-zA-Z_]+[a-zA-Z_0-9]*;?,?" palabra) #t]
            [else #f])))

(define is-delimitadorFuncion?
    (lambda (palabra)
        (cond
            [(empty? palabra) #f]
            [(regexp-match-exact? #rx".*\\(|.*\\)|.*\\{|.*\\}" palabra) #t]
            [else #f])))

(define is-comment?
    (lambda (palabra)
        (cond
            [(empty? palabra) #f]
            [(regexp-match-exact? #rx"//[a-zA-Z]*" palabra) #t]
            [else #f])))

(define lexer
  (lambda (lst)
    (cond
        [(null? lst) " "]
        [(is-integer? (car lst)) (string-append(string-append (string-append (string-append "<span class=integer> " (car lst)) " </span>") " ")(lexer (cdr lst)))]
        [(is-include? (car lst)) (string-append(string-append (string-append (string-append "<span class=include> " (car lst)) " </span>") " ")(lexer (cdr lst)))]
        [(is-from-language? (car lst)) (string-append(string-append (string-append (string-append "<span class=reservada> " (car lst)) " </span>") " ")(lexer (cdr lst)))]
        [(is-operador? (car lst)) (string-append(string-append (string-append (string-append "<span class=operador> " (car lst)) " </span>") " ")(lexer (cdr lst)))]
        [(is-cadena? (car lst)) (string-append(string-append (string-append (string-append "<span class=cadena> " (car lst)) " </span>") " ")(lexer (cdr lst)))]
        [(is-delimitadorFuncion? (car lst)) (string-append(string-append (string-append (string-append "<span class=delimitadorFuncion> " (car lst)) " </span>") " ")(lexer (cdr lst)))]
        [(is-decimal? (car lst)) (string-append(string-append (string-append (string-append "<span class=decimal> " (car lst)) " </span>") " ")(lexer (cdr lst)))]
        [(is-identificador? (car lst)) (string-append(string-append (string-append (string-append "<span class=identificador> " (car lst)) " </span>") " ")(lexer (cdr lst)))]
        [(is-comment? (car lst)) (string-append(string-append (string-append (string-append "<span class=comment> " (car lst)) " </span>") " ")(lexer (cdr lst)))]
        [else (string-append " "(string-append (string-append (car lst) " ")(lexer (cdr lst))))])))

(define html-head (string-append "<!DOCTYPE html><html lang=\"es\"><head><meta charset=\"UTF-8\">
<title>Resaltador Lexico</title><link href=\"styles.css\" rel=\"stylesheet\"></head><body>" (lexer (string-split file-br))))
(define html (string-append html-head "</body></html>"))
(define output-file (write-file "Resaltador.html" html))







