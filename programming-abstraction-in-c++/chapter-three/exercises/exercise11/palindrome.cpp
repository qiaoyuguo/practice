/*
 * =====================================================================================
 *
 *       Filename:  palindrome.cpp
 *
 *    Description:  check if a string is  a palindrome
 *
 *        Version:  1.0
 *        Created:  2013年07月08日 16时44分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qiaoyuguo (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include "console.h"

using namespace std;

bool isSentencePalindrome(string str)
{
    int i = 0;
    int j = str.length() - 1;
    while(i < j)
    {
        if(isalnum(str.at(i)) == 0)
        {
            ++i;
            continue;
        }
        if(isalnum(str.at(j)) == 0)
        {
            --j;
            continue;
        }
        if(tolower(str.at(i)) != tolower(str.at(j)))
            return false;
        ++i;
        --j;
    }
    return true;
}
int main(void)
{
    std::cout << "This program tests sentence palindromes."<<endl;
    std::cout << "Indicte the end of the input with a blank line"<< endl;

    while(true)
    {
        std::cout << "Enter a sentence: ";
        string str;
        getline(std::cin, str);
        if(isSentencePalindrome(str))
            std::cout << "That sentence is a palindrome" << endl;
        else
            std::cout << "That sentence is not a palindrome" << endl;
    }

    return 0;
}
