/*
 * =====================================================================================
 *
 *       Filename:  ex2.c
 *
 *    Description:  problemID: 1677
 *
 * =====================================================================================
 */
#include <stdio.h>

#define MAX 10

int main(void)
{
    double price[MAX] = {28.9, 32.7, 45.6, 78, 35, 86.2, 27.8, 43, 56, 65};
    int n,i,cur_num;
    double sum;

    scanf("%d", &n);
    while(n-- > 0)
    {
       sum = 0;
       for(i = 0; i < MAX; i++) 
       {
           scanf("%d", &cur_num);
           sum += cur_num * price[i];
       }
       printf("%.2f\n", sum);
    }

    return 0;
}
