/*
 * =====================================================================================
 *
 *       Filename:  1876.c
 *
 *    Description:  Centipede's Morning
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int l,r,max;
    int l_max, r_max;

    scanf("%d %d", &l, &r);
    r_max = 2*40 + 2*(r-40) + 40; // try all right in first 40 tries, then throw other r-40 away , then take left 40
    l_max = 1+39*2+2*(l-40)+40;// take 39 left and throw all other l-40 left away, then 40 right
    max = l_max > r_max ? l_max : r_max;
    
    printf("%d\n", max);

    return 0;
}
