/*
 * =====================================================================================
 *
 *       Filename:  ex2.c
 *
 *    Description:  problemID 1711
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int n;
    int i,j;
    double sum = 1;;

    scanf("%d", &n);
    for(i = 1; i <= n; i++)
    {
        double cur_mul = 1.0;
        for(j = 1; j <= i; j++)
            cur_mul *= j;
        sum += 1.0/cur_mul;
    }
    printf("%.10f", sum);

    return 0;
}
