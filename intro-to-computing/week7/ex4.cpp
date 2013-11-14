/*
 * =====================================================================================
 *
 *       Filename:  ex4.cpp
 *
 *    Description:  swap rows of maxtrix 
 *
 * =====================================================================================
 */
#include <iomanip>
#include <iostream>

#define N 5
using namespace std;

int main(void)
{
    int a[N+2][N+2];
    int i,j,n,m;

    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            cin >> a[i][j];

    cin >> n >>m;

    if(n <0 || m < 0 || n >= N || m >= N)
        cout << "error" << endl;
    else 
    {
        for(j = 0; j < N; j++)
        {
            int tmp = a[n][j];
            a[n][j] = a[m][j];
            a[m][j] = tmp;
        }

        for(i = 0; i < 5; i++)
        {
          for(j = 0; j < 5; j++)
              cout << setw(4) << a[i][j];
          cout << endl;
        }
    }
    return 0;
}
