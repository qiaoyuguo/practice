/*
 * =====================================================================================
 *
 *       Filename:  test_ex2.c
 *
 *    Description:  test ex2
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int n = 10,i;
    srand(time(NULL));
    printf("1\n");
    printf("%d\n", n);;
    for(i = 0; i < n; i++)
    {
        int cur_opt = rand()%3;
        if(cur_opt == 0 || cur_opt == 1)
        {
            int cur_num;
            printf("push");
            cur_num = rand()%n;
            printf(" %d", cur_num);
        }
        else
            printf("pop");
        printf("\n");
    }

    return 0;
}
