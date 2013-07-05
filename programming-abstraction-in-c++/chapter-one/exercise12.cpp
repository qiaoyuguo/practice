/*
 * =====================================================================================
 *
 *       Filename:  exercise12.cpp
 *
 *    Description:  computer area of  quarter circle 
 *
 *        Version:  1.0
 *        Created:  2013年07月05日 22时15分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qiaoyuguo (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>
using namespace std;

#define MAX 10000

double square(double x)
{
    return x *x;
}
double compute_quarter_circle(double r)
{
    double sum = 0;
    for(int i = 1; i <= MAX; i++)
    {
        double height= sqrt(square(r)- square(r*(double)i/MAX));
        sum += height * r/MAX;
    }
    return sum;
}

int main(void)
{
    cout << "area of a quarter circle whose radius is 1 is:" << compute_quarter_circle(1.0) <<endl;
    return 0;
}
