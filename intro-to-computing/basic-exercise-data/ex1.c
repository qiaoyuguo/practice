/*
 * =====================================================================================
 *
 *       Filename:  ex1.c
 *
 *    Description:  problemID: 6173
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <math.h>

int main(void)
{
    int n;
    int sum = 0;
    int cur_num;

    scanf("%d", &n);
    while(n-- > 0)
    {
        scanf("%d", &cur_num);
        sum += (int)ceil((double)cur_num/70);
    }
    printf("%d.%d\n", sum/10, sum%10);

    return 0;
}
