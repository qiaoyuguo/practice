/*
 * =====================================================================================
 *
 *       Filename:  ex3.c
 *
 *    Description:  problemID: 1678
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int one_count = 0;
    int five_count = 0;
    int ten_count = 0;
    int n;
    int cur_num;

    scanf("%d", &n);
    while(n-- > 0)
    {
        scanf("%d", &cur_num);
        if(cur_num == 1)
            ++one_count;
        else if(cur_num == 5)
            ++five_count;
        else if(cur_num == 10)
            ++ten_count;
    }
    printf("%d\n", one_count);
    printf("%d\n", five_count);
    printf("%d\n", ten_count);

    return 0;
}
