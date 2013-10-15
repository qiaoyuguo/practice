/*
 * =====================================================================================
 *
 *       Filename:  ex5.cpp
 *
 *    Description:  special natural number
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int main(void)
{
    int n, sel_num;
    cin >> sel_num;
    for(n = 81; n <= 342; n++)
    {
        int h7,t7,s7;
        int h9,t9,s9;

        h7 = n/49;
        t7 = (n/7)%7;
        s7 = n%7;
        h9 = n/81;
        t9 = (n/9)%9;
        s9 = n%9;
        if(h7 == s9 && t7 == t9 && s7 == h9)
        {
            if(sel_num == 1)
                cout << n << endl;
            else if(sel_num == 2)
                cout <<h7<<t7<<s7 << endl;
            else if(sel_num == 3)
                cout <<h9 <<t7 << s9 << endl;
        }
    }

    return 0;
}
