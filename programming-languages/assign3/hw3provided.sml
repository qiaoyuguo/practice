(* Coursera Programming Languages, Homework 3, Provided Code *)

fun only_capitals(xs:string list) = 
    List.filter (fn s=> Char.isUpper(String.sub(s, 0))) xs

fun longest_string1(xs) = 
    foldl (fn (x,y) => if String.size(x) > String.size(y) then x else y) "" xs

fun longest_string2(xs) = 
    foldl (fn (x,y) => if String.size(x) >= String.size(y) then x else y) "" xs

val longest_string_helper =
    fn f => fn xs => foldl f "" xs

fun longest_string3(xs) = 
    longest_string_helper (fn (x,y) => if String.size(x) > String.size(y) then x else y)  xs
fun longest_string4(xs) = 
    longest_string_helper (fn (x,y) => if String.size(x) >= String.size(y) then x else y)  xs

fun longest_capitalized(xs) = 
    foldl (fn (x,y) => if String.size(x) > String.size(y) then x else y) "" (only_capitals(xs))

fun rev_string(s) = 
    implode(rev(explode s))


exception NoAnswer

datatype pattern = Wildcard
		 | Variable of string
		 | UnitP
		 | ConstP of int
		 | TupleP of pattern list
		 | ConstructorP of string * pattern

datatype valu = Const of int
	      | Unit
	      | Tuple of valu list
	      | Constructor of string * valu

fun g f1 f2 p =
    let 
	val r = g f1 f2 
    in
	case p of
	    Wildcard          => f1 ()
	  | Variable x        => f2 x
	  | TupleP ps         => List.foldl (fn (p,i) => (r p) + i) 0 ps
	  | ConstructorP(_,p) => r p
	  | _                 => 0
    end

(**** for the challenge problem only ****)

datatype typ = Anything
	     | UnitT
	     | IntT
	     | TupleT of typ list
	     | Datatype of string

(**** you can put all your code here ****)
