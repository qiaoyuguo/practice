/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);
void print_result(string text, string subsequence);

int main() {
    print_result("good good study", "go");
    print_result("I love writing c++ programs.", "man");
    return 0;
}

void print_result(string text, string subsequence)
{
    string result = isSubsequence(text, subsequence) ? "is" : "isn't";
    cout <<"'" << subsequence << "' " << result << " substring of " << "'" << text << "'" << endl;
}
bool isSubsequence(string text, string subsequence)
{
    if(text[0] == '\0')
        return subsequence[0] == '\0';
    if(text[0] == subsequence[0])
        return isSubsequence(text.substr(1), subsequence.substr(1));
    return isSubsequence(text.substr(1), subsequence);
}
