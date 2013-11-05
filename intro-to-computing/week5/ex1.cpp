/*
 * =====================================================================================
 *
 *       Filename:  ex1.cpp
 *
 *    Description:  age and illness
 *
 * =====================================================================================
 */

#include <cstdio>
#include <iostream>
using namespace std;

int main(void)
{
    int count[4] = {0};
    int n,i;
    int cur_num;
    const char *s[4] = {"1-18: ", "19-35: ", "36-60: ", "60-: "};

    cin >> n;
    for(i = 0; i < n; i++)
    {
        cin >> cur_num;
        if(cur_num <= 18)
            ++count[0];
        else if(cur_num <= 35)
            ++count[1];
        else if(cur_num <= 60)
            ++count[2];
        else 
            ++count[3];
    }
    for(i = 0; i < 4; i++)
    {
        printf("%s%.2lf%%\n", s[i], (double)(100*count[i])/n);
    }
    
    return 0;
}
