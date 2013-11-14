/*
 * =====================================================================================
 *
 *       Filename:  ex2.cpp
 *
 *    Description:  compare strings ignoring lowercase or uppercase
 *
 * =====================================================================================
 */
#include <cctype>
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

int char_nocase_cmp(char c1, char c2)
{
    if((isupper(c1) && isupper(c2)) || (islower(c1) && islower(c2)))
        return c1 - c2;
    if(isupper(c1) && islower(c2))
        return c1+32 - c2; /* lowercase substract uppercase of a character is 32 */
    return c1-32 - c2;
}
int main(void)
{
    char s1[100] = {0};
    char s2[100] = {0};
    int i,len1,len2, len;
    int res_cmp;

    gets(s1);
    gets(s2);

    len1 = strlen(s1);
    len2 = strlen(s2);
    i = 0;
    while(i < len1 && i < len2)
    {
        int cur_cmp = char_nocase_cmp(s1[i], s2[i]);
        if(cur_cmp != 0)
        {
            res_cmp = cur_cmp;
            break;
        }
        ++i;
    }
    if(i == len1 && i == len2)
        cout << '=' << endl;
    else if(i < len1 && i < len2)
        cout << (res_cmp>0?'>':'<') << endl;
    else if(i < len1)
        cout << '>' << endl;
    else
        cout << '<'  << endl;

    return 0;
}
