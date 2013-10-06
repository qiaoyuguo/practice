/*
 * =====================================================================================
 *
 *       Filename:  ex1801.c
 *
 *    Description: 1801 
 *
 * =====================================================================================
 */

#include <stdio.h>

int reverse_num(int n)
{
    int h_bit = n/100;
    int t_bit = (n/10)%10;
    int s_bit = n%10;

    return s_bit*100+t_bit*10+h_bit;
}
int main(void)
{
    int n;

    while(EOF != scanf("%d", &n))
    {
        printf("%d\n", n + reverse_num(n));
    }

    return 0;
}
