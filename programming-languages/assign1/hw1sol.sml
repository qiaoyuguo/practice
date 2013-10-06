fun is_older(day1: int * int *int, day2: int * int *int): bool = 
       if (#1 day1 < #1 day2)
       then true
       else if (#1 day1 > #1 day2)
       then false
       else if (#2 day1 < #2 day2)
       then true
       else if (#2 day1 > #2 day2)
       then false
       else if (#3 day1 < #3 day2)
       then true
       else false

fun number_in_month(xs: (int * int *int) list, a_month: int) : int = 
    if null xs
    then 0
    else
	let val tl_ans = number_in_month(tl xs, a_month)
	in
	    if ((#2 (hd xs)) = a_month)
	    then 1 + tl_ans
	    else tl_ans
	end

fun number_in_months(ds: (int*int*int) list, ms: int list):int = 
    if null ms
    then 0
    else number_in_month(ds, hd ms) + number_in_months(ds, tl ms)

fun dates_in_month(ds: (int*int*int) list, a_month: int): (int*int*int) list =
    if null ds
    then []
    else 
	let val tl_ans = dates_in_month(tl ds, a_month)
	in
	    if ((#2 (hd ds)) = a_month)
	    then (hd ds)::tl_ans
	    else tl_ans
	end

fun dates_in_months(ds: (int*int*int) list, months:int list):(int*int*int) list = 
    if null months
    then []
    else dates_in_month(ds, hd months) @ dates_in_months(ds, tl months)
	 
fun get_nth(ss: string list,  n: int): string = 
    if n = 1
    then hd ss
    else get_nth(tl ss, n-1)

fun date_to_string(date: int*int*int): string = 
    let val months = ["January", "February", "March", "Aprill", "May", "June",
		      "July", "August", "September", "October", "November", "December"]
    in List.nth(months, #2 date -1 ) ^" " ^ Int.toString(#3 date) ^ ", " ^ Int.toString(#1 date)
    end

fun number_before_reaching_sum(sum:int, ns: int list) : int = 
    if (hd ns) >= sum 
    then 0
    else 1 + number_before_reaching_sum(sum - hd ns, tl ns)

fun what_month(day: int) : int = 
    let val ds = [0,31,28,31,30,31,30,31,31,30, 31, 30, 31]
    in 
	number_before_reaching_sum(day, ds)
    end

fun month_range(day1:int, day2: int): int list = 
    if day1 > day2
    then []
    else what_month(day1)::month_range(day1+1, day2)

fun oldest(ds: (int *int*int) list) : (int*int*int) option = 
    if null ds
    then NONE
    else 
	let fun oldest_nonempty(ds: (int*int*int) list):(int*int*int) = 
		if null (tl ds)
		then hd ds
		else 
		    let val tl_ans = oldest_nonempty(tl ds)
		    in
			if is_older(hd ds, tl_ans)
			then hd ds
			else tl_ans
		    end
	in
	    SOME (oldest_nonempty ds)
	end
		  
	    
