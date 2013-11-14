/*
 * =====================================================================================
 *
 *       Filename:  ex5.cpp
 *
 *    Description:  check abnormal cells
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

int main(void)
{
    int a[100][100] = {{0}};
    int n;
    int i,j;
    int total = 0;

    cin >>n;

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            cin >> a[i][j];


    for(i = 1; i < n-1; i++)
        for(j = 1; j < n-1; j++)
        {
            if(a[i][j] + 50 <= a[i-1][j] && a[i][j]+50 <= a[i][j-1]
              && a[i][j] + 50 <= a[i+1][j] && a[i][j]+50 <= a[i][j+1])
                total += 1;
        }

    cout << total << endl;

    return 0;
}
