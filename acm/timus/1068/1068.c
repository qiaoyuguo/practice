/*
 * =====================================================================================
 *
 *       Filename:  1068.c
 *
 *    Description:  Sum 
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int n;
    int i;
    int sum = 0;

    scanf("%d", &n);
    if(n >= 1)
    {
        for(i = 1; i <= n; i++)
            sum += i;
    }
    else
    {
        for(i = n; i <= 1; i++)
            sum += i;
    }

    printf("%d\n", sum);

    return 0;
}
