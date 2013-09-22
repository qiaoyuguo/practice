/*
 * =====================================================================================
 *
 *       Filename:  ex8.c
 *
 *    Description:  problemID: 2709
 *
 * =====================================================================================
 */
#include <stdio.h>

int count_one_in_binary(int n)
{
    int total = 0;
    while(n > 0)
    {
        n = n & (n-1);
        ++total;
    }
    return total;
}
int main(void)
{
    int n,cur_num;

    scanf("%d", &n);
    while(n-- > 0)
    {
        scanf("%d", &cur_num);
        printf("%d\n", count_one_in_binary(cur_num));
    }

    return 0;
}
