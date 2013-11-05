/*
 * =====================================================================================
 *
 *       Filename:  2_2.cpp
 *
 *    Description:  sum of odd numbers
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

int main(void)
{
    int m,n;
    int i,sum = 0;

    cin >> m >> n;
    i = m % 2 == 0 ? m+1:m;
    for(; i <= n; i+=2)
    {
        sum += i;
    }
    cout << sum << endl;

    return 0;
}
