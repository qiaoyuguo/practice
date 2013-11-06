/*
 * =====================================================================================
 *
 *       Filename:  ex5.cpp
 *
 *    Description:  find numbers sum of whose digits can be devided by itself
 * =====================================================================================
 */
#include <iostream>

using namespace std;

bool is_true(int n)
{
    int t = n/10;
    int s = n%10;
    if(n % (t + s) == 0)
        return true;
    else 
        return false;
}
int main(void)
{
    int n;
    cin >> n;

    for(int i = 10; i <= n; i++)
    {
        if(is_true(i))
            cout << i << endl;
    }

    return 0;
}
