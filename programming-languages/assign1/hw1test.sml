(* Homework1 Simple Test *)
(* These are basic test cases. Passing these tests does not guarantee that your code will pass the actual homework grader *)
(* To run the test, add a new line to the top of this file: use "homeworkname.sml"; *)
(* All the tests should evaluate to true. For example, the REPL should say: val test1 = true : bool *)

use "hw1sol.sml";
val test1 = is_older((1,2,3),(2,3,4)) = true
val test1_1 = is_older((1,2,3),(1,3,4)) = true
val test1_2 = is_older((1,2,3),(1,1,4)) = false
val test1_3 = is_older((2,3,4),(1,3,4)) = false
val test1_4 = is_older((1,2,3),(1,2,4)) = true
val test1_5 = is_older((1,2,3),(1,2,2)) = false
val test1_6 = is_older((1,2,3),(1,2,3)) = false

val test2 = number_in_month([(2012,2,28),(2013,12,1)],2) = 1
val test2_1 = number_in_month([(2012,2,28),(2013,12,1), (2010, 2, 3)],2) = 2
val test2_2 = number_in_month([(2012,2,28),(2013,2,1)],2) = 2
val test2_3 = number_in_month([(2012,12,28),(2013,12,1)],2) = 0

val test3 = number_in_months([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28)],[2,3,4]) = 3
val test3_1 = number_in_months([(2012,12,28),(2013,12,1),(2011,1,31),(2011,1,28)],[2,3,4]) = 0

val test4 = dates_in_month([(2012,2,28),(2013,12,1)],2) = [(2012,2,28)]
val test4_1 = dates_in_month([(2012,12,28),(2013,12,1)],2) = []
val test4_2 = dates_in_month([(2012,2,28),(2013,2,1), (2010,2,8),(2009,2, 5)],2) = [(2012,2,28),(2013,2,1), (2010,2,8),(2009,2, 5)]

val test5 = dates_in_months([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28)],[2,3,4]) = [(2012,2,28),(2011,3,31),(2011,4,28)]
val test5_1 = dates_in_months([(2012,2,28)], [3,4,5]) = []

val test6 = get_nth(["hi", "there", "how", "are", "you"], 2) = "there"
val test6_1 = get_nth(["hi", "there", "how", "are", "you"], 1) = "hi"
val test6_2 = get_nth(["hi", "there", "how", "are", "you"], 5) = "you"

val test7 = date_to_string((2013, 6, 1)) = "June 1, 2013"
val test7_1 = date_to_string((2013, 1, 1)) = "January 1, 2013"
val test7_2 = date_to_string((2010,12 , 1)) = "December 1, 2010"
val test7_3 = date_to_string((2010, 2, 1)) = "February 1, 2010"
val test7_4 = date_to_string((2010, 3, 1)) = "March 1, 2010"
val test7_5 = date_to_string((2010, 4, 1)) = "April 1, 2010"
val test7_6 = date_to_string((2010, 5, 1)) = "May 1, 2010"
val test7_7 = date_to_string((2010, 7, 1)) = "July 1, 2010"
val test7_9 = date_to_string((2010, 8, 1)) = "August 1, 2010"
val test7_10 = date_to_string((2010, 9, 1)) = "September 1, 2010"
val test7_11= date_to_string((2010, 10, 1)) = "October 1, 2010"
val test7_12= date_to_string((2010, 11, 1)) = "November 1, 2010"

val test8 = number_before_reaching_sum(10, [1,2,3,4,5]) = 3
val test8_1 = number_before_reaching_sum(9, [1,2,3,4,5]) = 3
val test8_2 = number_before_reaching_sum(7, [1,2,3,4,5]) = 3
val test8_3 = number_before_reaching_sum(6, [1,2,3,4,5]) = 2

val test9 = what_month(70) = 3
val test9_1 = what_month(31) = 1
val test9_2 = what_month(32) = 2
val test9_3 = what_month(59) = 2
val test9_4 = what_month(60) = 3
val test9_5 = what_month(90) = 3

val test10 = month_range(31, 34) = [1,2,2,2]
val test10_1 = month_range(58, 62) = [2,2,3,3,3]

val test11 = oldest([(2012,2,28),(2011,3,31),(2011,4,28)]) = SOME (2011,3,31)
