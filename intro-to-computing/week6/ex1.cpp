/*
 * =====================================================================================
 *
 *       Filename:  ex1.cpp
 *
 *    Description:  sum of numbers
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

const int N = 5;
int main(void)
{
    int n, a[N];
    cin >> n;
    for(int i = 0; i < N; i++)
        cin >> a[i];
    int sum = 0;
    for(int i =0; i < N; i++)
        if(a[i] < n)
            sum += a[i];
    cout << sum << endl;
}
