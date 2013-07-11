/*
 * =====================================================================================
 *
 *       Filename:  MorseCode.cpp
 *
 *    Description:  Morse code to/from string depending on first character
 *    string.
 *
 *
 * =====================================================================================
 */
#include <iostream>
#include "map.h"
#include "console.h"

void initMaps(Map<char,string> & Char2Morse, Map <string, char> & Morse2Char)
{
    Map<char, string> map;
    char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int len = strlen(alpha);
    string morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", //A B C D E F
                      "--.", "....", "..", ".---", "-.-", ".-..", // G H I J K L
                      "--", "-.", "---", ".--.", "--.-", ".-.", //M N O P Q R
                      "...", "-", "..-", "...-", ".--", "-..-", //S T U V W X
                      "-.--", "--.." //Y Z
                     };

    for(int i = 0; i < len; i++)
    {
        Char2Morse.put(alpha[i], morse[i]);
        Morse2Char.put(morse[i], alpha[i]);
    }
}

string core_conv(Map<char,string> & Char2Morse, Map <string, char> & Morse2Char, string str)
{
    string result;
    int len = str.length();

    if(len == 0)
        return str;
    str = trim(str);
    char first_char = str.at(0);
    if(first_char == '-' || first_char == '.')
    {
        istringstream iss(str);
        string sub;
        while(iss)
        {
            iss >>sub;
            if(!iss)
                break;
            result += Morse2Char.get(sub);
        }
    }
    else
    {
        for(int i = 0; i < len; i++)
        {
            if(Char2Morse.containsKey(str[i]))
                result += Char2Morse.get(str[i]);
            else
                result += str[i];
            if(i < len-1)
                result += " ";
        }
    }
    return result;
}

void core_handle(void)
{
    cout << "Morse code translator" << endl;
    string s;
    //string s1 = "SOS TITANIC";
    //string s2 = "WE ARE SINKING FAST";
    //string morse1 = ".... . .- -.. .. -. --. ..-. --- .-. -.-- --- ..-";
    Map<char,string>  Char2Morse;
    Map <string, char>  Morse2Char;
    initMaps(Char2Morse, Morse2Char);
    
    while(true)
    {
        cout << "> ";
        cout.flush();
        getline(cin, s);
        cout << core_conv(Char2Morse, Morse2Char, s) << endl;
    }
    //cout << core_conv(Char2Morse, Morse2Char, s1) << endl;
    //cout << core_conv(Char2Morse, Morse2Char, morse1) << endl;
}
int main(void)
{
    core_handle();

    return 0;
}

