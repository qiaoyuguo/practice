/*
 * =====================================================================================
 *
 *       Filename:  ex8.cpp
 *
 *    Description:  platform with max length
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <iostream>
using namespace std;

int max_sub_seq(int *a, int len)
{
    int max  = 0;
    int cur_seq_len = 0;
    for(int i = 0; i < len; i++)
    {
       if(i == 0) 
           cur_seq_len = 1;
       else if(a[i] == a[i-1])
       {
           ++cur_seq_len;
       }
       else
       {
           if(cur_seq_len > max)
               max = cur_seq_len;
           cur_seq_len = 1;
       }
    }
    return max;
}
int main(void)
{
    int n, *a;
    while( (cin >> n) && (n != 0))
    {
        a = (int*)malloc(n* sizeof(int));
        if(a == NULL)
            return -1;

        for(int i = 0; i < n; i++)
            cin >> a[i];
        cout << max_sub_seq(a, n) << endl;
        free(a);
    }

    return 0;
}
