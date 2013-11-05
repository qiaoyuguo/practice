/*
 * =====================================================================================
 *
 *       Filename:  ex5.c
 *
 *    Description:  seperate different bits of an 3-bit integer
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int main(void)
{
    int n;
    cin >> n;

    cout << n/100 << endl;
    cout << (n/10)%10 << endl;
    cout << n%10 << endl;

    return 0;
}
