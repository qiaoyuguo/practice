/*
 * =====================================================================================
 *
 *       Filename:  gcd.cpp
 *
 *    Description:  compute greatest common divisor using Euclid's algorithm
 *
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int gcd(int a, int b)
{
    if(b == 0)
        return a;
    return gcd(b, a % b); 
}

void print_gcd(int a, int b)
{
    int result = gcd(a, b);
    cout << "the greatest common divisor of " << a << " and " << b << " is " << result << endl;
}

int main()
{
    print_gcd(12, 27);
    print_gcd(36, 60);


    return 0;
}
