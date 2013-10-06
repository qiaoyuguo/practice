/*
 * =====================================================================================
 *
 *       Filename:  ex1803.c
 *
 *    Description:  1803
 *
 * =====================================================================================
 */

#include <stdio.h>

int luck_num(int a, int b)
{
    int n = a + b;

    while(n >= 10)
    {
        int t_bit = n/10;
        int s_bit = n%10;
        n = t_bit + s_bit;
    }

    return n;
}

int main(void)
{
    int n;
    while(EOF != scanf("%d", &n))
    {
        int h_bit = n/100;
        int t_bit = (n/10)%10;
        int s_bit = n%10;

        printf("%d\n", luck_num(luck_num(h_bit, t_bit), luck_num(t_bit, s_bit)));
    }

    return 0;
}
