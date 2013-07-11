/*
 * =====================================================================================
 *
 *       Filename:  StdDev.cpp
 *
 *    Description:  This program computes standard derivation of double vector.
 *
 *
 * =====================================================================================
 */
#include <iomanip> 
#include <cmath>
#include <iostream>
#include "vector.h"
#include "random.h"

double square(double x)
{
    return x * x;
}
double expectation(Vector<double> data)
{
    double sum = 0;
    int total= data.size();
    for(int i = 0; i < total; i++)
        sum += data.get(i);
    return sum/total;
}
double stddev(Vector<double> &data)
{
    double sum = 0;
    double expt = expectation(data);
    int size = data.size();
    for(int i = 0; i < size; i++)
        sum += square(expt - data.get(i));
    return sqrt(sum/size);
}

void init_data(Vector<double> &data)
{
    for(int i = 0; i < 100; i++)
        data.add(randomReal(0, 100));
}

void print_data(Vector<double> &data)
{
    for(int i = 0; i < data.size(); i++)
    {
        cout <<setw(10) <<data.get(i);
        if((i + 1)%10 == 0)
            cout << endl;
    }
    cout << endl;
}

int main(void)
{
    Vector<double> data;
    init_data(data);
    //print_data(data);
    cout << stddev(data) << endl;

    return 0;
}
