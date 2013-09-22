/*
 * =====================================================================================
 *
 *       Filename:  ex1.c
 *
 *    Description:  problemID:1722 elepant drinking water
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <math.h>

#define PI 3.14159
int main(void)
{
    int h,r;
    static int total = 20;
    double bucket_num;
    scanf("%d %d", &h, &r);

    bucket_num = total*1000/(PI*r*r*h);

    printf("%d\n", (int)ceil(bucket_num));

    return 0;
}
