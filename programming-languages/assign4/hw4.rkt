
#lang racket

(provide (all-defined-out)) ;; so we can put tests in a second file

;; put your code below

;; problem 1
;; Natural Natural -> ListOfNatural
;; produce numbers from low to high separated by stride in sorted order.
(define sequence
  (lambda (low high stride)
    (if (> low high)
        empty
        (cons low (sequence (+ low stride) high stride)))))

;; problem 2
;; ListOfString String -> ListOfString
;; produces  a string list of which each elment is a string of xs appended by suffix
(define (string-append-map xs suffix)
  (map (lambda (x) (string-append x suffix)) xs))

;; problem 3
;; List Integer -> get the ith element where i is length(xs) mod n
(define list-nth-mod
  (lambda (xs n)
    (cond [(< n 0) (error "list-nth-mod: negative number")]
          [(= n 0) (error "list-nth-mod: empty list")]
          [else 
           (car (list-tail xs (remainder (length xs) n)))])))

;; problem 4
;; Stream Natural -> List
;; produce first n elements of stream s
(define stream-for-n-steps empty)