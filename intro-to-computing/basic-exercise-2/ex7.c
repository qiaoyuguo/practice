/*
 * =====================================================================================
 *
 *       Filename:  ex7.c
 *
 *    Description:  probleID: 1678
 *
 * =====================================================================================
 */
#include <stdio.h>

#define MAX 3

int main(void)
{
    int n, cur_num,i;
    int a[MAX] = {0};

    scanf("%d", &n);
    while(n-- > 0)
    {
        scanf("%d", &cur_num);
        if(cur_num == 1)
            a[0]++;
        else if(cur_num == 5)
            a[1]++;
        else if(cur_num == 10)
            a[2]++;
    }
    
    for(i =0; i < MAX; i++)
        printf("%d\n", a[i]);

    return 0;

}
