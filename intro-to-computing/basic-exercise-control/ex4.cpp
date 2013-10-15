/*
 * =====================================================================================
 *
 *       Filename:  ex4.cpp
 *
 *    Description:  perfect cube
 *
 * =====================================================================================
 */
#include <iostream>

#define CUBE(x) ((x)*(x)*(x))
using namespace std;

int main(void)
{
    int  i,j,k,l;
    int n;

    cin >> n;
    for(i = 2; i <= n; i++)
        for(j = 2; j < i; j++)
            for(k = j+1; k < i; k++)
                for(l = k+1; l < i; l++)
                    if(CUBE(j) + CUBE(k) + CUBE(l) == CUBE(i))
                        cout << "Cube = " <<i << ", Triple = ("<<j<< ","<<k << "," <<l << ")"<< endl;

    return 0;
}
