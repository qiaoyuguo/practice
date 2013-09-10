/*
 * =====================================================================================
 *
 *       Filename:  1607.c
 *
 *    Description:  Taxi
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int a, a_inc, b, b_inc;

    scanf("%d %d %d %d", &a, &a_inc, &b, &b_inc);

    while(a <= b )
    {
        a += a_inc;
        if(a > b)
            a = b;
        b -= b_inc;
    }
    printf("%d\n", a);

    return 0;
}
