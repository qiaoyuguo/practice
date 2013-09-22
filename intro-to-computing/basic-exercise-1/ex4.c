/*
 * =====================================================================================
 *
 *       Filename:  ex4.c
 *
 *    Description:  problemID: 1709
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <math.h>

#define epsilon 1e-8

int main(void)
{
    int n;
    double a,b,c;
    double delta;
    double x1,x2;
    scanf("%d",&n);
    while(n--> 0)
    {
        scanf("%lf %lf %lf",&a,&b,&c);
        delta = b*b-4*a*c;
        if(fabs(delta) < epsilon)
        {
            x1 = -b/(2*a);
            if(fabs(x1) < epsilon)
                x1 = 0.0;
            printf("x1=x2=%.5f\n", x1);
        }
        else if(delta > epsilon)
        {
            x1 = (-b+sqrt(delta))/(2*a);
            x2 = (-b-sqrt(delta))/(2*a);
            if(fabs(x1) < epsilon)
                x1 = 0.0;
            if(fabs(x2) < epsilon)
                x2 = 0.0;
            printf("x1=%.5f;x2=%.5f\n", x1,x2);
        }
        else
        {
            double real_part = (-b)/(2*a);
            double image_part = sqrt(-delta)/(2*a);

            if(fabs(real_part) < epsilon)
                real_part = 0.0;
            if(fabs(image_part) < epsilon)
                image_part = 0.0;
            
            printf("x1=%.5f+%.5fi;x2=%.5f-%.5fi\n",real_part,image_part,real_part,image_part);
        }
    }
    return 0;

}
