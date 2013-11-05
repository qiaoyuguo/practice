(* Homework3 Simple Test*)
(* These are basic test cases. Passing these tests does not guarantee that your code will pass the actual homework grader *)
(* To run the test, add a new line to the top of this file: use "homeworkname.sml"; *)
(* All the tests should evaluate to true. For example, the REPL should say: val test1 = true : bool *)
use "hw3provided.sml";
val test1 = only_capitals ["A","B","C"] = ["A","B","C"]
val test1_1 = only_capitals ["Abc", "abc"] = ["Abc"]

val test2 = longest_string1 ["A","bc","C"] = "bc"
val test2_1 = longest_string1 ["ab", "bc"] =  "ab"
val test2_2 = longest_string1 [] = ""

val test3 = longest_string2 ["A","bc","C"] = "bc"
val test3_1 = longest_string2 ["ab", "bc", "cd"] = "cd"
val test3_2 = longest_string2 [] = ""

val test4a= longest_string3 ["A","bc","C"] = "bc"
val test4a_1 = longest_string3 ["ab", "bc"] =  "ab"
val test4a_2 = longest_string3 [] = ""

val test4b= longest_string4 ["A","B","C"] = "C"
val test4b_1 = longest_string4 ["ab", "bc", "cde"] = "cde"
val test4b3_2 = longest_string4 [] = ""

val test5 = longest_capitalized ["A","bc","C"] = "A";
val test5_1 = longest_capitalized [] = ""

val test6 = rev_string "abc" = "cba";

val test7 = first_answer (fn x => if x > 3 then SOME x else NONE) [1,2,3,4,5] = 4

val test8 = all_answers (fn x => if x = 1 then SOME [x] else NONE) [2,3,4,5,6,7] = NONE
val test8_1 = all_answers (fn x => if x = 1 then SOME [x] else NONE) [] = SOME []
val test8_2 = all_answers (fn x => if x = 1 then SOME [x] else NONE) [1,2,3,4,5,6,7]  = SOME [1]
val test8_3 = all_answers (fn x => if x > 4 then SOME [x] else NONE) [1,2,3,4,5,6,7]  = SOME [5,6,7]

val test9a_1 = count_wildcards Wildcard = 1
val test9a_2 = count_wildcards (TupleP [Wildcard, Wildcard, ConstP(5)]) = 2
val test9a_3 = count_wildcards (ConstructorP ("dt", TupleP [Wildcard, Wildcard, Wildcard])) = 3
val test9a_4 = count_wildcards (TupleP [Wildcard, TupleP [Wildcard, Wildcard], ConstP 5]) = 3
val test9a_5 = count_wildcards (TupleP [ConstP 10, TupleP [Variable "str"], ConstP 5]) = 0;

val test9b = count_wild_and_variable_lengths (Variable("a")) = 1

val test9c = count_some_var ("x", Variable("x")) = 1;

val test10 = check_pat (Variable("x")) = true
val test10_1 = check_pat (TupleP [Variable("x"), Variable("y")]) = true
val test10_2 = check_pat (TupleP [Variable("x"), Variable("x")]) = false
val test10_3 = check_pat (TupleP [Variable("x"), Variable("y"), Variable("x")]) = false
val test10_4 = check_pat(Wildcard) = true
(*
val test11 = match (Const(1), UnitP) = NONE

val test12 = first_match Unit [UnitP] = SOME []

*)
