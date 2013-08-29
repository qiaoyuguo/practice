/*
 * =====================================================================================
 *
 *       Filename:  1910.c
 *
 *    Description:  Titan Ruins
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int a,b,c;
    int sum;
    int max_sum = 0;
    int count = 0;
    int n,i;
   
    scanf("%d %d %d",&n, &a, &b);
    for(i = 2; i < n; i++)
    {
        scanf("%d", &c);
        sum = a + b + c;
        if(sum > max_sum)
        {
            max_sum = sum;
            count = i;
        }
        a = b;
        b = c;
    }
    printf("%d %d\n", max_sum, count);

    return 0;
}
