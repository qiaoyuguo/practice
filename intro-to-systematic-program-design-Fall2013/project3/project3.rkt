;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname 39f8d5e1db4df658beea3650c65c08ce) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;; Data definitions:

;; Board size
(define N 4)
;; Board is (listof true|false) that is N*N(16) elements long
;; interp.
;;   A board is a NxN array of squares, where each square has a row and column 
;;   number(r,c).But we represent it as a single flat list, in which the rows
;;   are layed out one after another in a linear fashion.
#;
(define (backtracking-fn bd)
  (local [(define (fn-for-bd bd)
            (... (fn-for-lobd (... bd))))
          
          (define (fn-for-lobd lobd)
            (cond [(empty? lobd) false]
                  [else
                   (local [(define try (fn-for-bd (first lobd)))] ;try first board
                     (if (not (false? try))                     ;successful?
                         try                                    ;if so produce that
                         (fn-for-lobd (rest lobd))))]))]          ;or try rest of boards
    
    (fn-for-bd bd)))

;; Pos is Integer[0, N*N]
;; interp.
;;  the position of a square on the board, for a given p, then
;;    - the row is (quotient p N)
;;    - the column is (remainder p N)
#;
(define (fn-for-pos pos)
  (... (quotient p N) (remainder p N)))

;; list of all column number and row number
(define COLS (build-list N (lambda (x) x)))
(define ROWS COLS)

;; Integer[0,N-1] Integer[0,N-1] -> Integer[0,N*N-1]
;; Convert 0-base row and column to Pos
(define (r-c->pos r c) (+ (* r N) c))

(define-struct coord (x y))
;; Coord is (make-coord Integer[0,N-1] Integer[0,N-1])
;; interp. a coord is a square position x,y
#;
(define (fn-for-coord coord)
  (... (coord-x coord) (coord-y coord)))

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
(define BD3
  (list F F F T
        F T F F
        F F T F
        F F F F))
(define BD4
  (list F F T F
        F F F F
        F F F F
        F F F F))

(define BD1s
  (list F T F F 
        F F F T
        T F F F
        F F T F))
(define BD4s
  (list F F T F
        T F F F
        F F F T
        F T F F))

;; Functions:
;; Board -> Board or false
;; produce a solution for bd, or false if bd is unsolvable
;; Assume: bd is valid
(check-expect (solve BD1) BD1s)
(check-expect (solve BD2) false)
(check-expect (solve BD3) false)
(check-expect (solve BD4) BD4s)

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
;; produce true if board is solved, or else produce false
;; Assume: board is valid, so it it solved if it has four T in it.
(check-expect (solved? BD1) false)
(check-expect (solved? BD2) false)
(check-expect (solved? BD3) false)
(check-expect (solved? BD4) false)
(check-expect (solved? BD1s) true)

;(define (solved? bd) false) ;stub
(define (solved? bd)
  (= (count-true bd) N))

;; Board -> Integer[0,N*N-1]
;; produce number of true values in bd.
(check-expect (count-true BD1) 0)
(check-expect (count-true BD2) 2)
(check-expect (count-true BD1s) 4)

(define (count-true bd) 
  (length (filter (lambda (x) (eq? x true)) bd)))

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
  (keep-only-valid (fill-with-true bd (find-blank-row bd))))

;; Board -> Integer[0,N-1]
;; produce the first row number in which row all squares are all false
(check-expect (find-blank-row BD1) 0)
(check-expect (find-blank-row BD2) 2)
;(define (find-blank-row bd) 1) ;stub
(define (find-blank-row bd)
  (local [(define (find-blank-row-helper cur-row bd)
            (cond [(eq? cur-row N) false]
                  [(row-false? cur-row bd) cur-row]
                  [else
                   (find-blank-row-helper (+ cur-row 1) bd)]))]
    (find-blank-row-helper 0 bd)))


;; Integer[0,N-1] Board -> Boolean
;; produces true if all square in row of bd is false, or else produce true.
(check-expect (row-false? 0 BD1) true)
(check-expect (row-false? 3 BD1) true)
(check-expect (row-false? 1 BD2) false)
(check-expect (row-false? 2 BD2) true)
(check-expect (row-false? 1 BD1s) false)

;(define (row-false? row bd) false) ;stub

(define (row-false? row bd) 
  (andmap  (lambda (x) 
             (false? (list-ref bd (r-c->pos row x))))
           ROWS))

;; Integer[0,N-1] Board -> (list of Board)
;; produce N Boards, with any square of row in bd filled with true
(check-expect (fill-with-true BD1 0)
              (list (cons T (rest BD1))
                    (cons F (cons T (rest (rest BD1))))
                    (cons F (cons F (cons T (rest (rest (rest BD1))))))
                    (cons F (cons F (cons F (cons T (rest (rest (rest (rest BD1))))))))))
;(define (fill-with-true  bd row) empty) ;stub

(define (fill-with-true bd row)
  (local [(define (lst-head lst pos)
            (if (< pos 0)
                empty
                (cons (first lst) (lst-head (rest lst) (- pos 1)))))
          (define (lst-tail lst pos)
            (local [(define cur-len (length lst))]
              (if (>= pos cur-len)
                  empty
                  (cons (list-ref lst pos) (lst-tail lst (+ pos 1))))))
          ]
    (map (lambda (x)
           (local [(define cur-pos (r-c->pos row x))]
             (append (lst-head bd (- cur-pos 1))
                     (list true)
                     (lst-tail bd (+ cur-pos 1)))))
         ROWS)))

; (listof Board) -> (listof Board)
;; produce list containing only valid boards

(check-expect (keep-only-valid (list (cons T (cons T (rest (rest BD1)))))) 
              empty)
;(define (keep-only-valid lobd) empty) ;stub
(define (keep-only-valid lobd )
  (filter bd-valid? lobd))

;; Board -> Boolean
;; produce true if bd is a valid board.
(check-expect (bd-valid? BD1) true)
(check-expect (bd-valid? BD2) true)
(check-expect (bd-valid? BD3) false)

;(define (bd-valid? bd) false) ;stub
(define (bd-valid? bd)
  (not (queens-attack? (get-all-queens bd))))

;; Board -> (ListOf Coord)
;; produce queen position lists
(check-expect (get-all-queens BD1) empty)
(check-expect (get-all-queens BD2) (list (make-coord 0 3) (make-coord 1 1)))
(check-expect (get-all-queens BD3) (list (make-coord 0 3) (make-coord 1 1) (make-coord 2 2)))

;(define (get-all-queens bd) empty) ;stub
(define (get-all-queens bd)
  (map (lambda (pos) 
         (make-coord (quotient pos N) (remainder pos N)))
       (get-all-queens-pos bd)))

;; Board -> ListOfInteger
;; produdes all queens positions 
(check-expect (get-all-queens-pos BD1) empty)
(check-expect (get-all-queens-pos BD2) (list 3 5))
(check-expect (get-all-queens-pos BD3) (list 3 5 10))

;(define (get-all-queens-pos bd) empty) ;stub
(define (get-all-queens-pos bd)
  (local [(define (get-all-queens-pos-helper bd cur-pos)
            (cond [(empty? bd) empty]
                  [(false? (first bd)) (get-all-queens-pos-helper (rest bd) (+ cur-pos 1))]
                  [else
                   (cons cur-pos (get-all-queens-pos-helper (rest bd) (+ cur-pos 1)))]))]
    (get-all-queens-pos-helper bd 0)))

;; (ListOf Coord) -> Boolean
;; produce true if it has one coord attacks other coords.
(check-expect (queens-attack? empty) false)
(check-expect (queens-attack? (list (make-coord 0 3))) false)
(check-expect (queens-attack? (list (make-coord 0 0) (make-coord 0 3))) true)
(check-expect (queens-attack? (list (make-coord 1 2) (make-coord 3 2))) true)
(check-expect (queens-attack? (list (make-coord 1 1) (make-coord 2 0))) true)
(check-expect (queens-attack? (list (make-coord 0 3) (make-coord 1 1))) false)
(check-expect (queens-attack? (list (make-coord 0 3) (make-coord 1 1) (make-coord 2 2))) true)

;(define (queens-attack?  loc) false) ;stub

(define (queens-attack? loc)
  (local [(define (queen-attack--coord? a-coord b-coord)
            (local [(define ax (coord-x a-coord))
                    (define ay (coord-y a-coord))
                    (define bx (coord-x b-coord))
                    (define by (coord-y b-coord))]
              (cond [(or (eq? ax bx) (eq? ay by)) true]
                    [(eq? (abs (- ax bx)) (abs (- ay by))) true]
                    [else false])))
          (define (queen-attack--loc? a-coord loc)
            (cond [(empty? loc) false]
                  [(queen-attack--coord? a-coord (first loc)) true]
                  [else
                   (queen-attack--loc? a-coord (rest loc))]))]
    (cond [(empty? loc) false]
          [(empty? (rest loc)) false]
          [(queen-attack--loc? (first loc) (rest loc)) true]
          [else
           (queens-attack? (rest loc))])))