/*
 * =====================================================================================
 *
 *       Filename:  ex1.cpp
 *
 *    Description:  apple and worm
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>

using namespace std;

int main(void)
{
    int n,x,y;
    int remained_apple;
    
    cin >> n >>x >>y; 
    remained_apple = n - (int)ceil((double)y/x);
    if(remained_apple >= 0)
        cout << remained_apple << endl;
    else
        cout << 0 << endl;

    return 0;
}
