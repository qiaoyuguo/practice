;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname project3) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ())))


;; Data definitions:

;; Board is (listof true|false) that is 16 elements long
;; interp.
;;   A board is a 4x4 array of squares, where each square has a row and column 
;;   number(r,c).But we represent it as a single flat list, in which the rows
;;   are layed out one after another in a linear fashion.

;; Pos is Natural[0, 15]
;; interp.
;;  the position of a square on the board, for a given p, then
;;    - the row is (quotient p 4)
;;    - the column is (remaind p 4)

;; Convert 0-base row and column to Pos
(define (r-c->pos r c) (+ (* r 4) c))

;; Constants:
(define F false) ; F stands for no queens
(define T true)  ; T stands for having queens.

(define BD1 
  (list F F F F 
        F F F F
        F F F F
        F F F F))
(define BD2
  (list F F F T
        F T F F
        F F F F
        F F F F))
(define BD1s
  (list F T F F 
        F F F T
        T F F F
        F F T F))
 
;; Functions:
;; Board -> Board or false
;; produce a solution for bd, or false if bd is unsolvable
;; Assume: bd is valid
(check-expect (solve BD1) BD1s)

;(define (solve bd) false) ;stub

(define (solve bd)
  (local [(define (solve--bd bd)
            (if (solved? bd)
                bd
                (solve--lobd (next-boards bd))))
          (define (solve--lobd lobd)
            (cond [(empty? lobd) false]
                  [else
                   (local [(define try (solve--bd (first lobd)))]
                     (if (not (false? try))
                         try
                         (solve--lobd (rest lobd))))]))]
    (solve--bd bd)))

;; Board -> Boolean
;; produce true if board is solved
;; Assume: board is valid, so it it solved if it has four T in it.
(check-expect (solved? BD1) false)
(check-expect (solved? BD2) false)
(check-expect (solved? BD1s) true)

;(define (solved? bd) false) ;stub
(define (solved? bd)
  (= (count-true bd) 4))

;; Board -> Natural
;; produce number of true values in bd.
(check-expect (count-true BD1) 0)
(check-expect (count-true BD2) 2)
(check-expect (count-true BD1s) 4)

(define (count-true bd) 
  (length (filter (lambda (x) (not (false? x))) bd)))

;; Board -> (ListOf Board)
;; produces list of valid next boards from board
;; find  first row whose squares are all false, then fill any square in the row with true, keep 
;; only valid boards
(check-expect (next-boards BD1) 
              (list (cons T (rest BD1))
                    (cons F (cons T (rest (rest BD1)))) 
                    (cons F (cons F (cons T (rest (rest (rest BD1))))))
                    (cons F (cons F (cons F (cons T (rest (rest (rest (rest BD1))))))))))
(define (next-boards bd)
  (keep-only-valid (fill-with-true (find-blank-row bd) bd)))

;; Board -> Natural[0,3]
;; produce the first row whose squares are all false
(check-expect (find-blank-row BD1) 0)
(check-expect (find-blank-row BD2) 2)
(define (find-blank-row bd) 1) ;stub

;; Natural[0,3] Board -> Boolean
;; produces true if all square in row of bd is false, or else produce true.
(check-expect (row-false? 0 BD1) true)
(check-expect (row-false? 3 BD1) true)
(check-expect (row-false? 1 BD2) false)
(check-expect (row-false? 2 BD2) true)
(check-expect (row-false? 1 BD1s) false)

;(define (row-false? row bd) false) ;stub

(define (row-false? row bd)
  (andmap (list-ref bd (r-c->pos row 0)) ))
;; Natural[1,4] Board -> (list of Board)
;; produce 4 Boards, with any square of row in bd filled with true

(check-expect (fill-with-true 1 BD1)
              (list (cons T (rest BD1))
                    (cons F (cons T (rest (rest BD1))))
                    (cons F (cons F (cons T (rest (rest (rest BD1))))))
                    (cons F (cons F (cons F (cons T (rest (rest (rest (rest BD1))))))))))
(define (fill-with-true row bd) empty)

;; (listof Board) -> (listof Board)
;; produce list containing only valid boards

(check-expect (keep-only-valid (list (cons T (cons T (rest (rest BD1)))))) 
              empty)
(define (keep-only-valid lobd) empty) ;stub