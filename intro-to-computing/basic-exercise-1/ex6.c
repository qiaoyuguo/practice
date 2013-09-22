/*
 * =====================================================================================
 *
 *       Filename:  ex6.c
 *
 *    Description:  problemID:1735  (check if a year  is leap year)
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int a;
    int is_leap;

    scanf("%d", &a);
    is_leap =(a%3200 != 0&& a % 400 == 0) || (a % 4 == 0 && a % 100 != 0);

    if(is_leap)
        printf("Y\n");
    else
        printf("N\n");

    return 0;
}
