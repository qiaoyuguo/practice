/*
 * =====================================================================================
 *
 *       Filename:  ex2.cpp
 *
 *    Description:  elephant drinking water
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>

using namespace std;

const double PI = 3.14159;

int main(void)
{
    int h,r;
    int total = 20;
    double bucket_num;

    cin >> h >> r;
    bucket_num = (total * 1000)/(PI*r*r*h);
    cout << (int)ceil(bucket_num) << endl;

    return 0;
}


