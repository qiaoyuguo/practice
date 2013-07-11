/*******************************************************************
 * File: FleschKincaid.cpp
 *
 * A program that approximates the Flesch-Kincaid grade level of a
 * piece of text.
 */

#include <iostream>
#include <fstream>
#include "tokenscanner.h"

using namespace std;
int count_syllable(string word)
{
    int count = 0;
    bool is_first_vowel = true;
    for(int i = 0; i < word.length(); i++)
    {
        char c = word.at(i);
        if(c != 'a' && c != 'e' && c != 'i' 
           && c != 'o' && c != 'u' && c != 'y')
            continue;
        if(c == 'e' && i == word.length() - 1)
            continue;
        if(is_first_vowel)
        {
            ++count;
            is_first_vowel = false;
        }
        else
            is_first_vowel = true;
    }
    return count;
}
double compute_grade(string file)
{
    int word_cnt = 0;
    int syllable_cnt = 0;
    int sentence_cnt = 1;
    bool is_first_sentence = true;
    ifstream ifn(file.c_str(), ifstream::in);
    TokenScanner scanner(ifn);

    scanner.ignoreWhitespace();
    while(scanner.hasMoreTokens())
    {
        string token = scanner.nextToken();
        if(scanner.getTokenType(token) == WORD)
        {
            ++word_cnt;
            syllable_cnt += count_syllable(token);
        }
        if(token == "." && !is_first_sentence)
        {
            ++sentence_cnt;
        }
        else
            is_first_sentence = false;

        //cout << token<<" " <<scanner.getTokenType(token)<< endl;
    }

    //cout << word_cnt <<" " << syllable_cnt <<" " << sentence_cnt << endl;
    return -15.59 + 0.39 * (word_cnt/sentence_cnt) + 11.8 *(syllable_cnt/word_cnt); 

}
int main() {
    cout << compute_grade("1984.txt") << endl;;
    cout << compute_grade("JaneEyre.txt") << endl;;
    cout << compute_grade("Hi.txt") << endl;

    return 0;
}

