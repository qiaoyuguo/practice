/*
 * =====================================================================================
 *
 *       Filename:  ex10.c
 *
 *    Description:  problemID 6182
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int n;
    int sel_num;
    scanf("%d", &sel_num);
    for(n = 81; n <= 342; n++)
    {
        int h7, t7, s7;
        int h9, t9, s9;
        h7 = n/49;
        t7 = (n/7)%7;
        s7 = n%7; 
        h9 = n/81;
        t9 = (n/9)%9;
        s9 = n%9;
        if(h7 == s9 && t7 == t9 && s7 == h9)
        {
            if(sel_num == 1)
                printf("%d\n",n);
            else if(sel_num == 2)
                printf("%d%d%d\n", h7, t7,s7);
            else if(sel_num == 3)
                printf("%d%d%d\n", h9, t9, s9);
        }
    }

    return 0;
}

