/*
 * =====================================================================================
 *
 *       Filename:  1787.c
 *
 *    Description:  Turn for MEGA
 *
 * =====================================================================================
 */
#include <stdio.h>
int main(void)
{
    int i;
    int k,n;
    int sum = 0;

    scanf("%d %d", &k, &n);
    for(i = 0; i < n; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        sum += tmp -k;
        sum = sum < 0 ? 0 : sum;
    }
    printf("%d\n", sum);

    return 0;
}
