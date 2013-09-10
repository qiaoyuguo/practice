/*
 * =====================================================================================
 *
 *       Filename:  1225.c
 *
 *    Description:  Flags
 *
 * =====================================================================================
 */
/* get AC by selecting GCC 4.7.2 C11, but if I select GCC 4.7.2 , code can't pass test data 12  */
#include <stdio.h>

#define MAX 55

long long fib[MAX] = {0};
void f()
{
    int i;
    fib[1] = 2;
    fib[2] = 2;
    for(i = 3; i < MAX; i++)
    {
        fib[i] = fib[i-1] + fib[i - 2];
    }
}
int main(void)
{
    int n;
    f();
    scanf("%d", &n);
    printf("%lld\n", fib[n]);

    return 0;
}
