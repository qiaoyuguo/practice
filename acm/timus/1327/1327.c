/*
 * =====================================================================================
 *
 *       Filename:  1327.c
 *
 *    Description:  fuses 
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int a,b;
    int result;

    scanf("%d %d", &a, &b);
    if(b % 2 == 0)
        result = (b-a+1)/2;
    else
        result = (b-a+2)/2;
    printf("%d\n", result);

    return 0;
}
