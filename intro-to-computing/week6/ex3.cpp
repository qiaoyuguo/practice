/*
 * =====================================================================================
 *
 *       Filename:  ex3.cpp
 *
 *    Description:  buying house
 *
 * =====================================================================================
 */
#include <cmath>
#include <iostream>

using namespace std;

int main(void)
{
    int n,k;

    while(cin >> n >> k)
    {

        int i;
        bool is_find = true;
        double cur_price = 200;
        for(i = 1; n*i < cur_price; i++)
        {
            if(n < cur_price/100 * k)
            {
                is_find = false;
                break;
            }
            cur_price *= 1+k/100.0;
        }
        if(is_find)
            cout << i << endl;
        else
            cout <<"Impossible" << endl;
    }
    return 0;
}
