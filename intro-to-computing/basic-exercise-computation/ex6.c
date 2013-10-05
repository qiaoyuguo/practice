/*
 * =====================================================================================
 *
 *       Filename:  ex6.c
 *
 *    Description:  problemID 6179
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", &n);
    while(n != 1)
    {
        if(n % 2 == 0)
        {
            printf("%d",n);
            n /= 2;
            printf("/2=%d\n", n);
        }
        else
        {
            printf("%d",n);
            n = 3*n+1;
            printf("*3+1=%d\n", n);
        }
    }
    printf("End\n");

    return 0;
}
