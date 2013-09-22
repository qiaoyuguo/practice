/*
 * =====================================================================================
 *
 *       Filename:  ex2.c
 *
 *    Description:  ProblemID:6170 apple and worm
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <math.h>

int main(void)
{
    int n,x,y;
    int remain_apple;

    scanf("%d %d %d", &n, &x, &y);
    remain_apple = n - (int)ceil((double)y/x);
    printf("%d\n", remain_apple >= 0 ? remain_apple : 0);

    return 0;
}
