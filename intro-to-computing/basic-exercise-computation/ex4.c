/*
 * =====================================================================================
 *
 *       Filename:  ex4.c
 *
 *    Description:  problemID 1685
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    long double sum = 0;
    int n,i;
    unsigned long long a = 1, b = 2;

    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        unsigned long long tmp = a + b;
        sum += (long double)b/a;
        a = b;
        b = tmp; 
        printf("%llu %llu\n", a, b);
    }

    printf("%.4Lf\n", sum);

    return 0;
}
