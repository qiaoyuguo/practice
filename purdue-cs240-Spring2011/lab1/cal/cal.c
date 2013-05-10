/*
 * =====================================================================================
 *
 *       Filename:  cal.c
 *
 *    Description:  calenda
 *
 *        Version:  1.0
 *        Created:  2013年05月10日 09时24分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qiao Yuguo (), qiaoyuguo2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MONTH_IN_YEAR 12
#define DAY_IN_WEEK 7
#define IS_LEAP_YEAR(year) (((year) % 400 ==0) || ((year) % 4 == 0 && (year)% 100 != 0))

void usage(void)
{
    printf("cal <month> <year>\n");
}
int main(int argc, char **argv)
{
    int cur_month; /* current month number  */
    int cur_year;  /* current year number */
    int days_in_cur_month; /* number of days in current month */
    //int is_leap_year; /* check if current year is leap year */
    int what_day_of_first_day; /* what day is first day */
    int i;
    
    char *day_in_week_tbl[DAY_IN_WEEK] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
    /* month table from Gregorian calenda to Zeller */
    int mon_tbl[1 + MONTH_IN_YEAR] = {0, 13, 14, 3, 4, 5, 6,
                                         7,  8,  9, 10, 11, 12};
    /* day in month */
    int day_in_month_tbl[1 + MONTH_IN_YEAR] = {0, 31, 28, 31, 30, 31, 30,
                                                  31, 31, 30, 31, 30, 31};
    if(3 != argc)
    {
        usage();
        return 0;
    }

    cur_month = atoi(argv[1]);
    if(cur_month < 1  || cur_month > 12)
    {
        printf("uncorrect month number");
        return -1;
    }

    cur_year = atoi(argv[2]);
    if(cur_year < 1 )
    {
        printf("uncorrect year number");
        return -1;
    }

    days_in_cur_month = day_in_month_tbl[cur_month];
    if(cur_month == 2)
        days_in_cur_month += IS_LEAP_YEAR(cur_year);
   
    if(cur_month == 1 || cur_month == 2)
        cur_year -= 1;
    cur_month = mon_tbl[cur_month]; /* convert to Zeller day */
    what_day_of_first_day = (1 + ((cur_month + 1)*26)/10 + cur_year + cur_year/4 + 6 * (cur_year/100) + cur_year/400)%DAY_IN_WEEK;

    /* convert zeller day to calenda format*/
    what_day_of_first_day = (what_day_of_first_day + DAY_IN_WEEK- 1)%DAY_IN_WEEK; 
    printf("year = %d, cur_mon = %d, what day = %d\n", cur_year, cur_month, what_day_of_first_day);
    for(i = 0; i < DAY_IN_WEEK; i++ )
    {
        printf("%3s", day_in_week_tbl[i]);
    }
    if(what_day_of_first_day > 0)
    {
        printf("\n");
        for(i = 0; i < what_day_of_first_day; i++)
            printf("   ");
    }
    for(i = what_day_of_first_day; i < what_day_of_first_day + days_in_cur_month; i++)
    {
        int cur_day = i % DAY_IN_WEEK;
        if(cur_day == 0)
            printf("\n");
        printf("%3d", i-what_day_of_first_day+1);
    }
    printf("\n");

    return 0;
}
