/*
 * =====================================================================================
 *
 *       Filename:  ex8.c
 *
 *    Description:  problemID: 6183
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int n,i;
    int a[6] = {100, 50, 20, 10, 5, 1};
    int count[6] = {0};

    scanf("%d", &n);
    for(i = 0; i < 6; i++)
    {
        if(n >= a[i])
        {
            count[i]= n/a[i];
            n -= count[i]* a[i];
        }
        if(n <= 0)
            break;
    }
    for(i = 0; i < 6; i++)
        printf("%d\n", count[i]);

    return 0;
}
