/*
 * =====================================================================================
 *
 *       Filename:  ex2.cpp
 *
 *    Description: find three-bit integer who satisfy condition
 *
 *        Version:  1.0
 *        Created:  2013年10月15日 10时48分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qiao Yuguo (), qyg@homewell.com.cn
 *        Company:  
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>
using namespace std;

bool is_perfect_square(int n)
{
    int sqrt_n = (int)(sqrt(n)+0.5);
    return sqrt_n * sqrt_n == n;
}
bool has_two_same_bit(int n)
{
    int sbit = n%10;
    int tbit = (n/10)%10;
    int hbit = n/100;
    return (sbit == tbit || sbit == hbit || tbit == hbit);
}
int main(void)
{
    int n;

    cin >> n;
    int i;
    for(int count = 0;  count < n; count++)
    {
        for(i = 100; i < 999; i++)
        {
            if(is_perfect_square(i) && has_two_same_bit(i))
            {
                ++count;
                if(count == n)
                    break;
            }
        }
    }

    cout << i << endl;

    return 0;
}
