/*
 * =====================================================================================
 *
 *       Filename:  ex1.c
 *
 *    Description:  problemID:1716
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    double sum = 0;
    int age;
    int n,i;

    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        scanf("%d", &age);
        sum += age;
    }

    printf("%.2f", sum/n);

    return 0;
}

