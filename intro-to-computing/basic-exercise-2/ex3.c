/*
 * =====================================================================================
 *
 *       Filename:  ex3.c
 *
 *    Description:  problemID: 6172 
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <math.h>

#define SQUARE(x) ((x)*(x))

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt(SQUARE(x1-x2)+SQUARE(y1-y2));
}
int main(void)
{
    double x1,y1,x2,y2,x3,y3;
    double a, b, c, half_circum;

    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);
    a = distance(x1,y1,x2,y2);
    b = distance(x2,y2,x3,y3);
    c = distance(x3,y3,x1,y1);
    half_circum= (double)(a + b + c)/2;
    
    printf("%.2f\n", sqrt(half_circum * (half_circum - a) * (half_circum-b) * (half_circum-c)));

    return 0;
}
