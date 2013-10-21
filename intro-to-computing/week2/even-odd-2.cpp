/*
 * =====================================================================================
 *
 *       Filename:  even-odd-2.cpp
 *
 *    Description:  even-odd-2
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int main()
{
    int a[10];
    int i = 0, j = 0;
    for(; i < 10; i++)
    {
        cin >> a[i];
    }

    for(i = 0; i < 9; i++)
    {
        for(j = 0;  j< 9-i; j++)
        {
            if(a[j] > a[j+1])
            {
                int tmp = a[j+1];
                a[j+1] = a[j];
                a[j] = tmp;
            }
        }
    }

    for(i = 0; i < 10; i++)
        if(a[i] % 2 == 1)
            cout  << a[i] << " ";

    for(i = 0; i < 10; i++)
        if(a[i] % 2 == 0)
            cout << a[i] << " ";
    cout << endl;

    return 0;

}
