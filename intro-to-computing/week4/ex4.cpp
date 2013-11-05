/*
 * =====================================================================================
 *
 *       Filename:  ex4.cpp
 *
 *    Description:  min even and max odd number 
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>

using namespace std;

int main(void)
{
    const int N = 6;
    int a[N];
    for(int i = 0; i < N; i++)
    {
        cin >> a[i];
    }
    int min_even = 100;
    int max_odd = 0;

    for(int i = 0; i < N; i++)
    {
        if(a[i] % 2 == 0 && a[i] < min_even)
            min_even = a[i];
        else if(a[i] % 2 == 1 && a[i] > max_odd)
            max_odd = a[i];
    }

    //cout << min_even << max_odd << endl;
    cout << abs(min_even - max_odd) << endl;

    return 0;
}
