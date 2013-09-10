/*
 * =====================================================================================
 *
 *       Filename:  1636.c
 *
 *    Description:  Penalty Time
 *
 * =====================================================================================
 */

#include <stdio.h>

#define MAX 10

int main(void)
{
    int m, n,i;
    int sum = 0;
    int a[MAX + 5] = {0};

    scanf("%d %d", &m, &n);
    for(i = 0; i < MAX; i++)
    {
        scanf("%d", &a[i]);
        sum += a[i] * 20;
    }

    if(m + sum > n )
        printf("Dirty debug :(\n");
    else
        printf("No chance.\n");

    return 0;
}
