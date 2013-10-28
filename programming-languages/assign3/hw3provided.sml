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

val rec first_answer =
    fn f => fn xs => 
	       case xs of
		   [] => raise NoAnswer
		 | x::xs' => if isSome(f(x))
			    then valOf(f(x))
			    else first_answer f xs'
val rec all_answers = 
    fn f => fn xs => 
	       case xs of 
		   [] => SOME []
		 | x::[] => if isSome(f(x))
			    then f(x)
			    else NONE
		 | x::xs' => 
		   let val rest = all_answers f xs'
		   in
		       if isSome(f(x))
		       then 
			   if isSome(rest)
			   then SOME (valOf(f(x)) @ valOf(rest))
			   else f(x)
		       else rest
		   end

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

fun count_wildcards p = 
    g (fn x => 1) (fn x=>0) p

fun count_wild_and_variable_lengths p = 
    g (fn x => 1) (fn v => String.size v) p
    
fun count_some_var(s, p) = 
    g (fn x => 0)  (fn v => if v = s then 1 else 0)   p

fun check_pat p = 
    let
	fun all_vars p =
	    case p of 
		Variable x => [x]
	      | TupleP ps => List.foldl (fn (x,y) => all_vars(x) @ y)  [] ps
	      | _ => []
	fun has_no_dup [] = true
	  | has_no_dup (x::xs) = not (List.exists (fn y => x = y) xs) andalso (has_no_dup xs)
    in
	has_no_dup(all_vars(p))
    end
(**** for the challenge problem only ****)

datatype typ = Anything
	     | UnitT
	     | IntT
	     | TupleT of typ list
	     | Datatype of string

(**** you can put all your code here ****)
