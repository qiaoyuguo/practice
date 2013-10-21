/*
 * =====================================================================================
 *
 *       Filename:  even-odd-1.cpp
 *
 *    Description:  even-odd-1
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int main()
{
    int all[10], odd[10], even[10];
    int i = 0, j = 0;

    for(; i < 10; i++)
        cin >> all[i];

    int numOdd = 0;
    int numEven = 0;

    for(i = 0; i < 10; i++)
    {
        if(all[i]%2 != 0)
        {
            odd[numOdd] = all[i];
            numOdd++;
        }
        else
        {
            even[numEven] = all[i];
            numEven++;
        }
    }

    for(i = 0; i < numOdd; i++)
    {
        for(j = 0; j < numOdd -i -1;j++)
        {
            if(odd[j] > odd[j+1])
            {
                int tmp = odd[j+1];
                odd[j+1] = odd[j];
                odd[j] = tmp;
            }
        }
    }

    for(i = 0; i < numEven; i++)
    {
        for(j = 0; j < numEven-1-i; j++)
        {
            if(even[j] > even[j+1])
            {
                int tmp = even[j];
                even[j] = even[j+1];
                even[j+1] = tmp;
            }
        }
    }

    for(i = 0; i < numOdd; i++)
    {
        cout << odd[i] << " ";
    }

    for(i = 0; i < numEven; i++)
    {
        cout << even[i] << " ";
    }
    cout << endl;

    return 0;
}
