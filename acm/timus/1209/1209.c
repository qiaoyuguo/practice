/*
 * =====================================================================================
 *
 *       Filename:  1209.c
 *
 *    Description:  1,10,100,1000,..
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <math.h>


int main(void)
{
    long n,i;
    scanf("%ld", &n);
    for(i = 0; i < n; i++)
    {
        long cur_n;
        long double cur_d;
        scanf("%ld", &cur_n);
        cur_d = sqrtl(8*(double)cur_n-7);
        if((long)cur_d == cur_d)
            printf("1 ");
        else
            printf("0 ");
    }
    printf("\n");

    return 0;
}
