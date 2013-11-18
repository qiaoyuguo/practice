;; Programming Languages, Homework 5

#lang racket
(provide (all-defined-out)) ;; so we can put tests in a second file

;; definition of structures for MUPL programs - Do NOT change
(struct var  (string) #:transparent)  ;; a variable, e.g., (var "foo")
(struct int  (num)    #:transparent)  ;; a constant number, e.g., (int 17)
(struct add  (e1 e2)  #:transparent)  ;; add two expressions
(struct ifgreater (e1 e2 e3 e4)    #:transparent) ;; if e1 > e2 then e3 else e4
(struct fun  (nameopt formal body) #:transparent) ;; a recursive(?) 1-argument function
(struct call (funexp actual)       #:transparent) ;; function call
(struct mlet (var e body) #:transparent) ;; a local binding (let var = e in body) 
(struct apair (e1 e2)     #:transparent) ;; make a new pair
(struct fst  (e)    #:transparent) ;; get first part of a pair
(struct snd  (e)    #:transparent) ;; get second part of a pair
(struct aunit ()    #:transparent) ;; unit value -- good for ending a list
(struct isaunit (e) #:transparent) ;; evaluate to 1 if e is unit else 0

;; a closure is not in "source" programs; it is what functions evaluate to
(struct closure (env fun) #:transparent) 

;; Problem 1
(define (racketlist->mupllist rlist)
  (if (null? rlist)
      (aunit)
      (apair (car rlist) (racketlist->mupllist (rest rlist)))))

(define (mupllist->racketlist mupllist)
  (if (aunit? mupllist)
      empty
      (cons (apair-e1 mupllist) (mupllist->racketlist (apair-e2 mupllist)))))

;; Problem 2

;; lookup a variable in an environment
;; Do NOT change this function
(define (envlookup env str)
  (cond [(null? env) (error "unbound variable during evaluation" str)]
        [(equal? (car (car env)) str) (cdr (car env))]
        [#t (envlookup (cdr env) str)]))

;; Do NOT change the two cases given to you.  
;; DO add more cases for other kinds of MUPL expressions.
;; We will test eval-under-env by calling it directly even though
;; "in real life" it would be a helper function of eval-exp.
(define (eval-under-env e env)
  (cond [(var? e) 
         (envlookup env (var-string e))]
        [(add? e) 
         (let ([v1 (eval-under-env (add-e1 e) env)]
               [v2 (eval-under-env (add-e2 e) env)])
           (if (and (int? v1)
                    (int? v2))
               (int (+ (int-num v1) 
                       (int-num v2)))
               (error "MUPL addition applied to non-number")))]
        ;; CHANGE add more cases here
        [(int? e) e]
        [(ifgreater? e)
         (let ([v1 (eval-under-env (ifgreater-e1 e) env)]
               [v2 (eval-under-env (ifgreater-e2 e) env)])
           (cond [(and (int? v1) (int? v2))
                  (if (> (int-num v1) (int-num v2))
                      (eval-under-env (ifgreater-e3 e) env)
                      (eval-under-env (ifgreater-e4 e) env))]
                 [else
                  (error "require int arguments")]))]
        [(mlet? e)
         (letrec ([v (eval-under-env (mlet-e e) env)]
                  [new-env (cons (cons (mlet-var e) v) env)])
           (eval-under-env (mlet-body e) new-env))]
        [(fun? e)
         (closure env e)]
        [(closure? e) e]
        [(call? e)
         (let ([funexp (eval-under-env (call-funexp e) env)]
               [actual (eval-under-env (call-actual e) env)])
           (cond [(and (closure? funexp) (fun? (closure-fun funexp)))
                  (letrec ([cur-env (closure-env funexp)]
                           [cur-fun (closure-fun funexp)]
                           [func-env (cons (fun-nameopt cur-fun) cur-env)]
                           [param-env (cons (fun-formal cur-fun) actual)]
                           [new-env (cons param-env 
                                          (if (fun-nameopt cur-fun)
                                              (cons func-env cur-env)
                                              cur-env))])
                    (eval-under-env (fun-body cur-fun) new-env))]
                   ; (if (fun-nameopt cur-fun)
                    ;    (eval-under-env ;(mlet (fun-nameopt cur-fun) cur-env 
                     ;                         (mlet (fun-formal cur-fun) actual (fun-body cur-fun)) env)
                     ;   (eval-under-env (mlet (fun-formal cur-fun) actual (fun-body cur-fun)) env)))]
                                        
                        ;(int 1) ;;not implemented!!!
                        ;(eval-under-env (mlet (fun-formal cur-fun) actual (fun-body cur-fun)) e
                 [else
                  (error "error happens")]))]
        [(apair? e)
         (let ([v1 (eval-under-env (apair-e1 e) env)]
               [v2 (eval-under-env (apair-e2 e) env)])
           (apair v1 v2))]
        [(fst? e) 
         (let ([v (eval-under-env (fst-e e) env)])
           (if (apair? v)
               (apair-e1 (fst-e e))
               (error "argument not an apair")))]
        [(snd? e) 
         (let ([v (eval-under-env (snd-e e) env)])
           (if (apair? v)
               (apair-e2 (snd-e e))
               (error "argument not an apair")))]
        [(isaunit? e)
         (let ([v (eval-under-env (isaunit-e e) env)])
           (if (aunit? v)
               (int 1)
               (int 0)))]
        [#t (error (format "bad MUPL expression: ~v" e))]))

;; Do NOT change
(define (eval-exp e)
  (eval-under-env e null))

;; Problem 3

(define (ifaunit e1 e2 e3)
  (if (isaunit e1) e3 e2))

(define (mlet* lstlst e2)
  (if (null? lstlst)
      e2
      (mlet (car (car lstlst)) (cdr (car lstlst)) 
            (mlet* (cdr lstlst) e2))))

(define (ifeq e1 e2 e3 e4) 
  (mlet "_x" e1
        (mlet "_y" e2
              (ifgreater (var "_x") (var "_y") e4
                         (ifgreater (var "_y") (var "_x") e4 e3)))))
                         


;; Problem 4

(define mupl-map
  (fun #f "f1"
       (fun "f2" "xs"
            (ifaunit (var "xs")
                       (aunit)
                       (apair (call (var "f1") (fst (var "xs")))
                              (call (var "f2") (snd (var "xs"))))))))
  

(define mupl-mapAddN 
  (mlet "map" mupl-map
        "CHANGE (notice map is now in MUPL scope)"))

;; Challenge Problem

(struct fun-challenge (nameopt formal body freevars) #:transparent) ;; a recursive(?) 1-argument function

;; We will test this function directly, so it must do
;; as described in the assignment
(define (compute-free-vars e) "CHANGE")

;; Do NOT share code with eval-under-env because that will make
;; auto-grading and peer assessment more difficult, so
;; copy most of your interpreter here and make minor changes
(define (eval-under-env-c e env) "CHANGE")

;; Do NOT change this
(define (eval-exp-c e)
  (eval-under-env-c (compute-free-vars e) null))
