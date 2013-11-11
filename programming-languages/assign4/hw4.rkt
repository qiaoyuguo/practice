
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
           (car (list-tail xs (remainder n (length xs) )))])))

;; problem 4
;; Stream Natural -> List
;; produce first n elements of stream s
;(define powers-of-two 
;  (letrec [(f (lambda (x) (cons x (lambda () (f (* x 2))))))]
;    (lambda () (f 2))))
(define (stream-for-n-steps xs n)
  (let ([pr (xs)])
    (if (= n 0)
        empty
        (cons (car pr) (stream-for-n-steps (cdr pr) (- n 1))))))

;; problem 5
;; a stream which is like natural numbers except numbers divisible by 5 are negated
(define funny-number-stream
  (letrec [(f (lambda (x) (cons (if (= (remainder x 5) 0)
                                    (- x)
                                    x)
                                (lambda () (f (+ x 1))))))]
    (lambda () (f 1))))

;; problem 6
;; write a stream dan-then-dog where the elments of the stream alternate between
;; the strings "dan.jpg" and "dog.jpg"
(define dan-then-dog
  (letrec [(f (lambda (x) (cons x (lambda () (f  (if (string=? x "dan.jpg")
                                                     "dog.jpg"
                                                     "dan.jpg"))))))]
    (lambda () (f "dan.jpg"))))

;; problem 7
;; take a stream and return another stream, if ith elment is x, then 
;; corresponding result element  is (0 . x)
(define (stream-add-zero s)
  (letrec [(pr (s))]
    (lambda () (cons (cons 0 (car pr)) (stream-add-zero (cdr pr))))))

;; problem 8
;; List List -> Stream
;; produce a stream with each element is (x . y) (x belongs to xs, y belongs to ys)
(define (inter-list xs ys)
  (local [(define (f xs y) 
          (if (empty? xs)
              empty
              (cons (cons  (car xs) y) (f (cdr xs) y))))]
    (if (empty? ys)
        empty
        (append (f xs (car ys)) (inter-list xs (cdr ys))))))
        
(define (cycle-lists xs ys)
  (letrec [(zlen (* (length xs) (length ys)))
           (f (lambda (x) (cons (cons (list-nth-mod xs zlen) (list-nth-mod ys zlen))
                                (lambda () (f  (+ x 1))))))]
    (lambda () (f 0))))
                