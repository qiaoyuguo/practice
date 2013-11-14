/*
 * =====================================================================================
 *
 *       Filename:  ex3.cpp
 *
 *    Description:  find longest word in a sentence
 *
 *        Version:  1.0
 *        Created:  2013年11月14日 11时17分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qiao Yuguo (), qyg@homewell.com.cn
 *        Company:  
 *
 * =====================================================================================
 */
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int main(void)
{
    char buf[550] = {0};
    char maxWord[50] = {0};
    char curWord[50] = {0};

    int first = 1;
    int maxLen = 0;
    int c;

    int i = 1;
    while( (c=getchar()) != '.')
    {
        if(isalpha(c))
        {
            if(first)
            {
                first = 0;
                i = 0;
            }
            curWord[i++] = c;
        }
        else 
        {
            int curLen = strlen(curWord);
            if(curLen > maxLen)
            {
                maxLen = curLen;
                strcpy(maxWord, curWord);
            }
            first = 1;
        }
    }
    if(strlen(curWord) > maxLen)
        cout << curWord << endl;
    else
        cout << maxWord << endl;

    return 0;
}
