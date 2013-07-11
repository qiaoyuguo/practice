/*
 * =====================================================================================
 *
 *       Filename:  cannonball.cpp
 *
 *    Description:  given the height of pyramid of cannonball, compute
 *    the number of connonballs it contains
 *
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int raiseToPower(int n, int k)
{
    if(k == 0)
        return 1;
    return n * raiseToPower(n, k-1);
}

void print_result(int n, int k)
{
    cout << n << " raised to " << k << " is " << raiseToPower(n, k) << endl;
}
int main(void)
{
    print_result(2, 8);
    print_result(3,6);

    return 0;
}
