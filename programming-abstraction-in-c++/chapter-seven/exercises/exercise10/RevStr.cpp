/*
 * =====================================================================================
 *
 *       Filename:  RevStr.cpp
 *    Description:  reverse string using recursive method.
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

string reverse(string str)
{
    int len = str.length();
    if(len == 0 || len == 1)
        return str;
    return reverse(str.substr(1)) + str[0];
}

void printRevStr(string str)
{
    cout << "The reverse string of " << str << " is " << reverse(str) << endl;
}

int main()
{
    printRevStr("program");

    return 0;
}

