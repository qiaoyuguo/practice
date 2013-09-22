/*
 * =====================================================================================
 *
 *       Filename:  ex7.c
 *
 *    Description:  ProblemID 6171 (computer sum of odd numbers between m(include m) and n(include n))
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int m, n;
    int i,sum = 0;
    scanf("%d %d", &m, &n);
    
    i = m%2 == 0 ? m+1 : m;
    for(; i <= n; i+=2)
        sum += i;
    printf("%d\n", sum);

    return 0;
}
