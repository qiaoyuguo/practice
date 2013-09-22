/*
 * =====================================================================================
 *
 *       Filename:  ex5.c
 *
 *    Description:  problemID: 1856
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int x,y;
    while(scanf("%d %d", &x, &y) != EOF)
    {
        if(x >= -1 && x <= 1 && y >= -1 && y <= 1)
            printf("yes\n");
        else
            printf("no\n");
    }

    return 0;
}
