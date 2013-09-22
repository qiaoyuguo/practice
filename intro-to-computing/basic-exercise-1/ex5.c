/*
 * =====================================================================================
 *
 *       Filename:  ex5.c
 *
 *    Description:  problemID:1752 chicken and rabbit
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int n,a;

    scanf("%d", &n);
    while(n-- > 0)
    {
        scanf("%d", &a);
        if(a < 2 || a % 2 != 0)
            printf("0 0\n");
        else if(a == 2)
            printf("1 1\n");
        else
            printf("%d %d\n", (a/4+(a-a/4*4)/2),a/2);
    }

    return 0;
}
