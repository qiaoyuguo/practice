/*
 * =====================================================================================
 *
 *       Filename:  palindrome.cpp
 *
 *    Description:  check if a string is  a palindrome
 *
 *        Version:  1.0
 *        Created:  2013年07月10日 16时04分41秒
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

char shiftChar(char c, int shift)
{
    if(isupper(c))
        return (c-'A' + shift)%26 + 'A';
    else if(islower(c))
        return (c-'a' + shift)%26 + 'a';
    else
        return c;
}

string encodeCaesarCipher(string str, int shift)
{
    int len = str.length();
    string cipher = string();
    for(int i = 0; i < len; i++)
    {
        cipher.push_back(shiftChar(str.at(i), shift));
    }
    return cipher;
}

void handle_input(void)
{
    cout << "This program encodes a message using a Casesar cipher." << endl;
    int shift= getInteger("Enter the number of character postion to shift: ");
    string str = getLine("Enter a message: ");
    string cipher = encodeCaesarCipher(str, shift);
    cout << "Encoded message: " << cipher << endl;
}
int main(void)
{
   handle_input();

   return 0;
}
