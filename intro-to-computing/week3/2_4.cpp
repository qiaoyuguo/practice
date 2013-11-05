/*
 * =====================================================================================
 *
 *       Filename:  2_4.cpp
 *
 *    Description:  count of 1s
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int count_one_in_binary(int n)
{
    int total = 0;
    while(n > 0)
    {
        n = n & (n -1);
        ++total;
    }

    return total;
}

int main(void)
{
    int n,cur_num;

    cin >> n;
    while(n-- > 0)
    {
        cin >> cur_num;
        cout << count_one_in_binary(cur_num) << endl;
    }

    return 0;
}
