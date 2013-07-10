/*
 * =====================================================================================
 *
 *       Filename:  LetterSubsCipher.cpp
 *
 *    Description:  encode use letter substitute cipher
 *
 *        Version:  1.0
 *        Created:  2013年07月10日 16时34分41秒
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
#include "simpio.h"

using namespace std;

char subsChar(char c, string table)
{
    if(isupper(c))
        return table[c - 'A'];
    else if(islower(c)) 
        return table[c - 'a'];
    return c;
}

string encodeSubsCipher(string str, string alphaTable)
{
    int len = str.length();
    string cipher = string();
    for(int i = 0; i < len; i++)
    {
        cipher.push_back(subsChar(str.at(i), alphaTable));
    }
    return cipher;
}

void handle_input(void)
{
    cout << "Letter substitution cipher." << endl;
    string alphaTable= getLine("Enter a 26-letter key: ");
    string str = getLine("Enter a message: ");
    string cipher = encodeSubsCipher(str, alphaTable);
    cout << "Encoded message: " << cipher << endl;
}
int main(void)
{
   handle_input();

   return 0;
}
