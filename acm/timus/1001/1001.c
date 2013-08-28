/*
 * =====================================================================================
 *
 *       Filename:  1001.c
 *
 *    Description:  Reverse root
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double arr[128*1024];

int main(void)
{
    int count = 0;
    int i;
    double n;

    while(scanf("%lf", &n)!=EOF)
    {
        arr[count++] = sqrt(n);
    }

    for(i = count-1; i >= 0; i--)
    {
        printf("%.4f\n", arr[i]);
    }

    return 0;
}
