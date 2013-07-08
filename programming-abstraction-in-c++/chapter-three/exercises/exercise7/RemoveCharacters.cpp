/*
 * =====================================================================================
 *
 *       Filename:  RemoveCharacters
 *
 *    Description:  remove all characters of one string which occurs in another string
 *
 *        Version:  1.0
 *        Created:  2013年07月08日 16时34分41秒
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

std::string removeCharacters(std::string str, std::string remove)
{
    int len = str.length();
    std::string result= "";
    for(int i = 0; i < len; i++)
        if(remove.find(str[i]) == std::string::npos)
            result += str[i];
    return result;
}
int main(void)
{
    std::cout << removeCharacters("counterrevolutionaries", "aeiou") <<std::endl;

    return 0;
}
