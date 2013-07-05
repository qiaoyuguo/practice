/*
 * =====================================================================================
 *
 *       Filename:  exercise11.cpp
 *
 *    Description:  computer pi/4 using Leibniz Equation(just 1000 numbers):
 *                  pi/4 = 1-1/3+1/5-1/7+1/9-1/11+...
 *
 *        Version:  1.0
 *        Created:  2013年07月05日 22时08分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qiaoyuguo (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;

#define MAX 10000
double quarter_pi(void)
{
    double sum = 0;
    int direction = 1;
    for(int i = 1; i <= MAX; i++)
    {
       sum += direction * 1.0/(2*i-1);
       direction = -direction;
    }

    return sum;
}

int main(void)
{
    cout <<"value of pi/4 is:" <<quarter_pi()<<endl;

    return 0;
}
