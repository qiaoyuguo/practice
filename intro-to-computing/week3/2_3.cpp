/*
 * =====================================================================================
 *
 *       Filename:  2_3.cpp
 *
 *    Description:  count of integers
 *
 * =====================================================================================
 */
#include <iostream>

#define MAX 3

using namespace std;

int main(void)
{
    int n,cur_num,i;
    int a[MAX] = {0};

    cin >> n;
    while(n-- > 0)
    {
        cin >> cur_num;
        if(cur_num == 1)
            a[0]++;
        else if(cur_num == 5)
            a[1]++;
        else if(cur_num == 10)
            a[2]++;
    }

    for(i = 0; i < MAX; i++)
        cout << a[i] << endl;

    return 0;
}
