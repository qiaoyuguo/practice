/*
 * =====================================================================================
 *
 *       Filename:  ex4.c
 *
 *    Description:  problemID: 666
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

int fun(int m, int n)
{
    if(m < 0) 
        return 0;
    if(m == 0 || n == 1)
        return 1;
    return fun(m-n, n) + fun(m, n-1);
}
int main(void)
{
    int count;
    scanf("%d", &count);

    while(count-- > 0)
    {
        int m,n;
        scanf("%d %d", &m, &n);
        printf("%d\n", fun(m, n));
    }
}
