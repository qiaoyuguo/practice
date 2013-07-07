/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

string intToString(int n)
{
    if(n >= 0 && n <= 9)
        return string("") + char('0' + n);
    return(intToString(n/10) + intToString(n%10));
}

int stringToInt(string str)
{
    if(str.length() == 1)
        return str.at(0)-'0';
    else
        return 10*(stringToInt(str.substr(0,str.length()-1))) + stringToInt(str.substr(str.length()-1,1));
}

/* Main program */

int main() {
   cout<< intToString(998) <<endl;
   cout <<stringToInt("123") <<endl;
   return 0;
}
