/*
 * =====================================================================================
 *
 *       Filename:  ex5.c
 *
 *    Description:  problemID 6175
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <math.h>

int main(void)
{
    int n;
    int bad, good;

    scanf("%d", &n);
    while(n-- > 0)
    {
        int count = 1;
        scanf("%d %d", &bad, &good);
        if(bad <= good)
        {
          printf("%d\n", 1);
          continue;
        }
        while(bad > good)
        {
            ++count;
            bad -= good;
            if(bad <= 0)
                break;
            bad *= 2;
            if(bad > 1e6)
                bad = 1e6;
            good = (int)floor(good*1.05);
        }
        printf("%d\n", count);
    }
    return 0;
}
