#lang racket

(require 2htdp/batch-io) ;; Para leer y manipular archivos

;; Input File
(define archivo "Situación Problema\\Resaltador de Sintaxis 1\\test.txt")
(define file (read-file archivo))
(define file-lt (string-replace file "<" "&lt"))

(define file-gt (string-replace file-lt ">" "&gt"))

(define file-br (string-replace file-gt "\n" " <br> "))

file-br