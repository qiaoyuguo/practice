
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
          [(empty? xs) (error "list-nth-mod: empty list")]
          [(= n 0) (first xs)]
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
       
(define (cycle-lists xs ys)
  (letrec [(f (lambda (x) (cons (cons (list-nth-mod xs x) (list-nth-mod ys x))
                                (lambda () (f  (+ x 1))))))]
    (lambda () (f 0))))

;; problem 9
;; Integer (VectorOf pair) -> pair or false
;; produces first pair whose car field is v, or else produce false
(define (vector-assoc v vec)
  (local [(define (vector-assoc-helper v vec pos)
            (local [(define len (vector-length vec))]
              (cond [(>= pos len) #f]
                    [(not (pair? (vector-ref vec pos))) (vector-assoc-helper v vec (+ pos 1))]
                    [(equal? v (car (vector-ref vec pos))) (vector-ref vec pos)]
                    [else
                     (vector-assoc-helper v vec (+ pos 1))])))]
    (vector-assoc-helper v vec 0)))
                    
;; problem 10
;; List Integer -> (Number-> pair or false)
;; produce a function that takes one argument v  and return the same thing that (assoc v xs) would return.

(define (cached-assoc xs n) 
  (letrec ([memo (make-vector n #f)]
           [pos 0]

         (lambda (v)
           (let [ans (vector-assoc v memo)]
            (if ans
                ans
                (begin
                  (vector-set! memo pos (assoc  v xs))
                  (begin 
                    (set! pos (remainder (+ pos 1) n))
                    (assoc v xs)
                    (print "cnt is:")
                    (local [(define (print-memo memo start)
                              (if (>= start n)
                                  (print "end printing memo")
                                  (begin
                                    (print (vector-ref memo start))
                                    (print-memo memo (+ start 1)))))]
                      (print-memo memo 0))))))))
(define xs (list (cons 1 2) (cons 3 4) (cons 5  6) (cons 7 8) (cons 9 10)))
(define thing (cached-assoc xs 3))
  