/*
 * =====================================================================================
 *
 *       Filename:  1820.c
 *
 *    Description:  Ural steaks
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int n, k;
    scanf("%d %d", &n, &k);

    if(k >= n)
        printf("%d\n", 2);
    else
    {
        if( (n*2) % k != 0)
            printf("%d\n", (n*2)/k + 1);
        else
            printf("%d\n", (n*2)/k);
    }

    return 0;
}
