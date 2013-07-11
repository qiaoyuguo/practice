/*
 * =====================================================================================
 *
 *       Filename:  LetterFrequency.cpp
 *
 *    Description:  This program counts the frequency of letters in a data file
 *
 *
 * =====================================================================================
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
//#include "filelib.h"
#include "vector.h"
using namespace std;

/* Constants */
static const int COLUMNS = 7;
/* Main program */

void myPromptUserForFile(ifstream &infile, string prompt)
{
    cout <<prompt;
    string file_name;
    getline(cin, file_name);
    infile.open(file_name.c_str());
}
int main() {
    Vector<int> letterCounts(26);
    ifstream infile;
    myPromptUserForFile(infile, "input file: ");
    char ch;
    while(infile.get(ch)) {
        if(isalpha(ch)) {
            letterCounts[toupper(ch) - 'A']++;
        }
    }
    infile.close();
    for(char ch = 'A'; ch <= 'Z'; ch++)
        cout << setw(COLUMNS) <<letterCounts[ch - 'A'] << " " << ch << endl;
    return 0;
}
