/*
 * =====================================================================================
 *
 *       Filename:  DigitSum.cpp 
 *    Description:  computer sum of every digit in given integer.
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int digitSum(int n)
{
    if(n < 10)
        return n;
    return n% 10 + digitSum(n / 10);
}

void print_result(int n)
{
    cout << "sum of every digit in " << n << " is " << digitSum(n) << endl;
}

int main()
{
    print_result(12345678);
    print_result(1729);

    return 0;
}
