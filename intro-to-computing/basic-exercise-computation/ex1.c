/*
 * =====================================================================================
 *
 *       Filename:  ex1.c
 *
 *    Description:  problemID 6177
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int n, origin_total, origin_effective;
    double origin_rate;
    scanf("%d %d %d", &n, &origin_total, &origin_effective);
    origin_rate = (double)origin_effective/origin_total;
    --n;
    while(n-- > 0)
    {
        int cur_total, cur_effective;
        double cur_rate;

        scanf("%d %d", &cur_total, &cur_effective);
        cur_rate = (double)cur_effective/cur_total;
        if(cur_rate - origin_rate > 0.05)
            printf("better\n");
        else if(origin_rate - cur_rate > 0.05)
            printf("worse\n");
        else
            printf("same\n");
    }

    return 0;
}

