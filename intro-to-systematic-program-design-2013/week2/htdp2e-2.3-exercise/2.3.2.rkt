;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname 2.3.2) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
(require 2htdp/universe)
(require 2htdp/image)

;; 2.3.2 Finger Exercises

; Exercise 27: Design the function string-first,which extracts the first character
; from a non-empty string. Don’t worry about empty strings.

;; String -> String
;; extract the first character from the given non-empty string

(check-expect (string-first "hello") "h")
(check-expect (string-first "good") "g")

; (define (string-first str) "") ;stub

; (define (string-first str)     ;template
;  (... str))

(define (string-first str)
  (string-ith str 0))

; Exercise 31: Design the function string-remove-last, which produces a string 
; like the given one with the last character removed.
                                                    
;; String -> String
;; produces a string which removes  the last character of the given string

(check-expect (string-remove-last "hello") "hell")
(check-expect (string-remove-last "smile") "smil")

;(define (string-remove-last str) "") ;stub

;(define (string-remove-last str)    ;template
;  (... str))

(define (string-remove-last str)
  (substring str 0 (- (string-length str) 1)))

;; exercise 33
;; Design a program that moves a car across the world canvas, from left to right,
;; at the rate of three pixels per clock tick.
(define WHEEL-RADIUS 5)
(define WHEEL-DISTANCE (* WHEEL-RADIUS 5))
(define BODY-LENGTH (+ WHEEL-DISTANCE (* 6 WHEEL-RADIUS)))
(define BODY-HEIGHT (* WHEEL-RADIUS 2))
(define WHL (circle WHEEL-RADIUS "solid" "black"))
(define BDY
  (above
    (rectangle (/ BODY-LENGTH 2) (/ BODY-HEIGHT 2)
               "solid" "red")
    (rectangle BODY-LENGTH BODY-HEIGHT "solid" "red")))
(define SPC (rectangle WHEEL-DISTANCE 1 "solid" "white"))
(define WH* (beside WHL SPC WHL))
(define CAR (underlay/xy BDY WHEEL-RADIUS BODY-HEIGHT WH*))

; CarState -> CarState
; launch the program from some initial state
(define (main ws)  
   (big-bang ws (on-tick tock) (to-draw render) (stop-when stop-cond)))
      
; CarState -> CarState
; the clock ticked; move the car by 3 pixels:
; given; 20, expected 23
; given: 78, expected 81

(define (tock ws) (+ ws 3))

; CarState -> Image
; place the car into a scene, according to the given world state
(define (render ws) 
    (place-image CAR ws Y-CAR BACKGROUND))

; CarState -> Boolean
; return True when ws is bigger than scene width, otherwise return False

(define (stop-cond ws)
  (> ws (- SCENE-WIDTH BODY-LENGTH)))

(define SCENE-WIDTH 500)
(define SCENE-HEIGHT (* 5 WHEEL-RADIUS))
(define Y-CAR (/ SCENE-HEIGHT 2))

(define tree
  (underlay/xy (circle 10 'solid 'green)
               9 15
               (rectangle 2 20 'solid 'brown)))
(define BACKGROUND 
  (place-image tree (- SCENE-WIDTH (* 3 WHEEL-RADIUS)) Y-CAR 
               (empty-scene SCENE-WIDTH SCENE-HEIGHT)))
; run the main program
(main 0)