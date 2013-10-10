/*
 * =====================================================================================
 *
 *       Filename:  ex1805.c
 *
 *    Description:  1805
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int ch;
    int prev = 0;
    int count = 0;

    while((ch=getchar()) != '#')
    {
        if(ch == ' ' || ch == '\n')
            continue;
        if(ch == prev)
        {
            ++count;
        }
        else 
        {
            if(prev != 0)
                printf("%c%d", prev, count);
            count = 1;
            prev = ch;
        }
    }
    printf("%c%d\n", prev, count);

    return 0;
}
