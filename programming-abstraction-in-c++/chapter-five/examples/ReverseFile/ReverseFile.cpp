/*
 * =====================================================================================
 *
 *       Filename:  ReverseFile.cpp
 *
 *    Description:  This program displays the lines of an input file in inverse order
 *
 *
 * =====================================================================================
 */
#include <iostream>
#include <fstream>
#include <string>
//#include "filelib.h"
#include "vector.h"
using namespace std;

/* Function prototypes */
void readWholeFile(istream & is, Vector<string> & lines);

/* main program */

int main() {
    ifstream infile;
    Vector<string> lines;
    //promptUserForFile(infile, "Input file: ");
    string file_name;
    cout <<"Input file: ";
    getline(cin, file_name);
    infile.open(file_name.c_str());
    readWholeFile(infile, lines);
    infile.close();
    for(int i = lines.size() -1; i >= 0; i--)
    {
        cout << lines[i] << endl;
    }
    return 0;
}

/* 
 * Function readWholeFile
 * Usage: readWholeFile(is, lines)
 * ----------------------------------
 * Reads the entire contents of the specified input stream into the 
 * string vector lines. The client is responsible for opening and 
 * closing the stream
 * */

void readWholeFile(istream & is, Vector<string> & lines) {
    string line;
    while(getline(is, line)) {
        lines.add(line);
    }
}
