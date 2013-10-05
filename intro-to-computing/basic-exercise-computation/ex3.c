/*
 * =====================================================================================
 *
 *       Filename:  e3.c
 *
 *    Description:  problemID 2143
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <math.h>

int main(void)
{
    int h;
    double total_len, hth_len;
    scanf("%d", &h);
    printf("%g\n%g\n", h+2*h*511/(double)512, (double)h/1024);

    return 0;
}
