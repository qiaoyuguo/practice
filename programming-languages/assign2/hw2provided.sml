(* Dan Grossman, Coursera PL, HW2 Provided Code *)

(* if you use this function to compare two strings (returns true if the same
   string), then you avoid several of the functions in problem 1 having
   polymorphic types that may be confusing *)
fun same_string(s1 : string, s2 : string) =
    s1 = s2

(* put your solutions for problem 1 here *)
fun all_except_option (str:string, lst: string list) = 
    case lst  of	
	[] => NONE
      | x::xs => case same_string(str, x) of
		     true => SOME xs
		   | false => case all_except_option(str,xs) of
				  NONE => NONE
				| SOME ys => SOME (x::ys)

fun get_substitutions1(xss: string list list, s: string ) = 
    case xss of
	[] => []
      | (xs::xss') => case all_except_option(s, xs) of
			  NONE => get_substitutions1(xss', s)
			| SOME xs' => xs' @ get_substitutions1(xss',s)
    
fun get_substitutions2(xss: string list list, s: string) = 
    let fun get_substitutions2_acc(xss: string list list, s:string, acc: string list) = 
	    case xss of
		[] => acc
	      | (xs::xss') => case all_except_option(s, xs) of
				  NONE => get_substitutions2_acc(xss', s, acc)
				| SOME xs' => get_substitutions2_acc(xss', s, acc@xs')
    in
	get_substitutions2_acc(xss, s, [])
    end

fun similar_names(xss: string list list, name:{first:string, middle:string, last:string}) = 
    case name of
	{first = f, middle = m, last = l} => let fun subs(name:{first:string, middle:string, last:string}, xs: string list) = 
						     case xs of
							 [] => []
						       | (x::xs') => case name of
									{first = f', middle=m', last = l'} => {first=x, middle=m', last=l'}::subs(name, xs')
					     in
						 name::subs(name, get_substitutions2(xss, f))
					     end
    
(* you may assume that Num is always used with values 2, 3, ..., 10
   though it will not really come up *)
datatype suit = Clubs | Diamonds | Hearts | Spades
datatype rank = Jack | Queen | King | Ace | Num of int 
type card = suit * rank

datatype color = Red | Black
datatype move = Discard of card | Draw 

exception IllegalMove

(* put your solutions for problem 2 here *)
fun card_color(c:card) = 
    case c of 
	(s,_) => case s of 
		     Clubs => Black
		   | Spades => Black
		   | _ => Red

fun card_value(c:card) = 
    case c of
	(_, r) => case r of
		      Num n => n
		    | Ace => 11
		    | _ => 10

fun remove_card(cs, c, e) = 
    case cs of 
	[] => raise e
      | (x::xs) => if x = c
		   then xs
		   else case remove_card(xs, c, e) of
			    [] => [x]
			  | [y] => (x::[y])
fun all_same_color(cs) =
    case cs of
	[] => true
      | x::[]=> true
      | x::y::ys => if card_color(x) = card_color(y)
		    then all_same_color(y::ys)
		    else false

fun sum_cards(cs) = 
    case cs of
	[] => 0
      | x::cs' => card_value(x) + sum_cards(cs')

fun score(cs, goal) = 
    let 
	val total = sum_cards(cs)
    in 
	let 
	    val pre_score = if total > goal
			    then 3*(total-goal)
			    else goal-total
	in
	    if all_same_color(cs)
	    then pre_score div 2
	    else pre_score
	end
    end
		 
fun officiate(cs, ms, goal) =
    let fun officiate_helper (cs:card list, ms:move list, hs:card list, goal:int) = 
	    case (cs, ms, hs, goal) of
		(_, [], hs, goal) => score(hs, goal)
	      | (cs, (Discard(c))::ms', hs, goal) => officiate_helper(cs, ms', remove_card(hs, c, IllegalMove), goal)
	      | ([], _, hs, goal) => score(hs, goal)
	      | (x::cs', Draw::ms', hs, goal) => let val cur_score = score(x::hs, goal) 
						 in 
						     if cur_score > goal
						     then cur_score
						     else officiate_helper(cs', ms', x::hs, goal)
						 end
    in
	officiate_helper(cs, ms, [], goal)
    end
