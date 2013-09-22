/*
 * =====================================================================================
 *
 *       Filename:  ex8.c
 *
 *    Description:  problemID 1703: ( sum of numbers which is not relevant to 7)
 *
 * =====================================================================================
 */
#include <stdio.h>

#define SQUARE(x) ((x)*(x))

int is_not_relevant_to_seven(int n)
{
    if(n%7 == 0)
        return 0;
    if(n%10 == 7)
        return 0;
    if((n/10)==7)
        return 0;
    return 1;
}
int main(void)
{
    int i;
    int n;
    int sum = 0;

    scanf("%d", &n);
    for(i = 1; i <= n; i++)
        if(is_not_relevant_to_seven(i))
            sum += SQUARE(i);

    printf("%d\n", sum);

    return 0;
}
