/*
 * =====================================================================================
 *
 *       Filename:  print-table-data.cpp
 *
 *    Description:  read table data and print out the formated table
 *
 * =====================================================================================
 */

#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

const int NUM_LINES = 4;
const int NUM_COLUMNS = 3;
const int COLUMN_WIDTH = 20;

void PrintTableHeader() ;
void PrintTableBody() ;

int main() {
    PrintTableHeader();
    PrintTableBody();
    
    return 0;
}

void PrintTableBody() {
    ifstream input("table-data.txt");

    int rowNumber = 0;
    while(true)
    {
      int intValue;
      double doubleValue;
      input >> intValue >> doubleValue;

      if(input.fail()) break;

      cout << setw(COLUMN_WIDTH) << (rowNumber+1) << " | ";
      cout << setw(COLUMN_WIDTH) << intValue << " | ";
      cout << setw(COLUMN_WIDTH) << doubleValue <<endl;
      rowNumber++;
    }
}

void PrintTableHeader() {
    for(int column = 0; column < NUM_COLUMNS - 1; column++){
        for(int k = 0; k < COLUMN_WIDTH; k++)
            cout << '-';
        cout << "-+-";
    }

    for(int k = 0; k < COLUMN_WIDTH; k++)
        cout << '-';
    cout << endl;
}
